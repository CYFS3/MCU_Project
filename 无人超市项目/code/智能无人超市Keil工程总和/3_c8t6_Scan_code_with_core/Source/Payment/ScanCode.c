#include "ScanCode.h"
char ScanCode[128];
bool is_CodePage=false;//是否在扫码界面
void setScanCode(char *scan_code)//扫码触发
{
	strcpy(ScanCode,scan_code);
	if(is_CodePage)CalculateIndent();
}

char* getScanCode(void)
{
	return ScanCode;
}
/*设置界面状态*/
void setCodePage(bool isDispose)
{
	is_CodePage=isDispose;
}

bool getCodePage(void)
{
	return is_CodePage;
}

/*判断是商品条形码还是付款码*/
bool is_CodeType(void)
{
	int i=strlen(ScanCode);
	if(i>15)
		return 0;
	return 1;
}
Indent indent;
/*初始化订单*/
void init_indent(int user_id)
{
	indent.UserID=user_id;
	indent.add_price=0;
	indent.pay_price=0;
	indent.discount=0.95;
	indent.scanNum=0;
}
/*计算订单*/
void CalculateIndent(void)
{
	if(is_CodeType())//商品条形码
	{
		for(int i=0;i<Goodsnum;i++)
		{
			if(!strcmp((char *)(goods[i].BarCodeID),ScanCode))
			{
				int k=0;
				//printf("scode:%s\n",ScanCode);
				for(k=0;k<indent.scanNum;k++)
				{
					//printf("new:%s\n",indent.GoodList[k].goods.BarCodeID);
					if(0==strcmp((char*)(indent.GoodList[k].goods.BarCodeID),ScanCode))
					{
						indent.GoodList[k].number++;

						break;
					}
				}
				if(k==indent.scanNum)
				{
					indent.GoodList[k].goods=goods[i];
					indent.GoodList[k].number=1;
					indent.scanNum++;

				}
			}
		}
		UpdateIndent();
	}else
	{
		/*--------------发送订单信息------------------------*/
		//<indent.start>[user_id]123456[data_num]3[GoodsIdList->]1,3,4[GoodsNumberList->]10,12,5[discount]0.75<indent.end>
		char indent_data_str[512];//1024位数据
		snprintf(indent_data_str, sizeof(indent_data_str),"<indent.start>[user_id]%d[data_num]%d[GoodsIdList->]",indent.UserID,indent.scanNum);
		char GoodsIDi[8];

		for(int i=0;i<indent.scanNum;i++)
		{
			
			snprintf(GoodsIDi, sizeof(GoodsIDi),"%d",indent.GoodList[i].goods.Num);
			strcat(indent_data_str,GoodsIDi);
			if(i!=indent.scanNum-1)strcat(indent_data_str,",");
		}	

		strcat(indent_data_str,"[GoodsNumberList->]");
		char GoodsSumI[8];
		for(int i=0;i<indent.scanNum;i++)
		{
			
			snprintf(GoodsSumI, sizeof(GoodsSumI),"%d",indent.GoodList[i].number);
			strcat(indent_data_str,GoodsSumI);
			if(i!=indent.scanNum-1)strcat(indent_data_str,",");
		}
		char end_str[32];
		snprintf(end_str, sizeof(end_str),"[discount]%.2f<indent.end>\r\n",indent.discount);
		strcat(indent_data_str,end_str);
		usart_send_string(UART4,(u8 *)indent_data_str);//发送
		/*-------------------------------------------------*/
		printf("page page3%s",END);//付款成功界面
		is_door=true;
		is_CodePage=false;
		printf("page page0%s",END);//开始界面
	}
	
}

/*更新订单信息*/
void UpdateIndent(void)
{
	indent.add_price=0;
	for(int i=0;i<indent.scanNum;i++)
	{
		indent.GoodList[i].total_price=(indent.GoodList[i].number)*(indent.GoodList[i].goods.Price);
		indent.add_price+=indent.GoodList[i].total_price;
	}
	indent.pay_price=(indent.discount)*indent.add_price;
	
	send_indent(&indent);
	
	
}
/*开始付款界面*/
void Startbill(int user_id)
{
	init_indent(user_id);
	UpdateIndent();
	printf("page2.t2.txt+=\"%d\"%s",indent.UserID,END);

}
void change_discount(float nowdiscount)
{
	indent.discount=nowdiscount;
}
