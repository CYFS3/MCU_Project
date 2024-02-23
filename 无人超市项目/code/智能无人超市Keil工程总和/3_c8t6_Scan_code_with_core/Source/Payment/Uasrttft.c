#include "Usarttft.h"
#include "ctype.h"
void send_indent(const Indent *indent)
{
	//发送数据到串口屏
	printf("%spage2.slt0.txt=\"\"%s",END,END);
	for(int i=0;i<indent->scanNum;i++)
	{
		printf("page2.slt0.txt+=\" %d%8s  %12.2f %d  %.2f\r\n\"%s",
		i+1,
		indent->GoodList[i].goods.Name,
		indent->GoodList[i].goods.Price,
		indent->GoodList[i].number,
		indent->GoodList[i].total_price,
		END	
		);
	}
	printf("page2.t3.txt=\"%.2f%%\"%s",100*(indent->discount),END);
	printf("page2.t1.txt=\"%.2f\"%s",indent->pay_price,END);
	printf("page2.t0.txt=\"%.2f\"%s",indent->add_price,END);	

	
}

bool is_facing=false;
bool is_return_openmv=true;
bool is_return_page=false;
char OpenmvReturnData[32];

/*openmv返回ID了*/
void setReturnOpenmv(u8 *return_data)
{
	strcpy(OpenmvReturnData,(char *)return_data);
	is_return_openmv=true;//人脸识别成功
	is_return_page=false;//不强制推出界面
}
/*点击开始识别 处理串口屏发送过来的数据*/
void DisposeUsartTTFT(u8 *str)
{
	// 开始识别 指令AA  

	if(!strcmp((const char *)str,(const char *)"\xAA"))
	{
		is_return_openmv=false;//设定标志位为未返回
		strart_face();//开始人脸识别
		while(!is_return_openmv)
		{

			USART3_RecProcess();//等待人脸识别完成
			memset(str,0,256);
			usart1_pos=0;
			USART1_RecProcess();//是否强制退出界面
			DelayMs(200);
		}
		if(!is_return_page)
		{
			printf("%s",END);//发送串口屏结束指令
			printf("vis t0,1%s",END);//切换到人脸识别完成界面
			DelayMs(1000);//延迟1秒
			printf("page page2%s",END);//切换到付款界面
			setCodePage(true);//设置在付款界面
			Startbill((u8)*OpenmvReturnData);//字符串转int用户id 开始结算
		}
	}
	//如果接收到 BB 强制返回开始界面
	if(!strcmp((const char *)str,(const char *)"\xBB"))
	{
		is_return_openmv=true;//取消人脸识别
		is_return_page=true;//设置强制推出界面为真
	}
	
	
}



