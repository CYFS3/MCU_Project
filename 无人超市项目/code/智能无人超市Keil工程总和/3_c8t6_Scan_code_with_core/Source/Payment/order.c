#include "order.h"

bool is_EIC=true;
bool is_door=false;
void receive_order(char *data)
{
	cJSON *root = cJSON_Parse((const char*)data);
	if(root!=NULL)
	{
		cJSON *scancode_EIC = cJSON_GetObjectItem(root, "scancode_EIC");//
		cJSON *scancode_door = cJSON_GetObjectItem(root, "scancode_door");//
		cJSON *goods_id = cJSON_GetObjectItem(root, "goods_id");//接收新增商品编号
		cJSON *goods_name = cJSON_GetObjectItem(root, "goods_name");//接收新增商品名字
        cJSON *goods_barcode = cJSON_GetObjectItem(root, "goods_barcode");//接收新增商品条形码
		cJSON *goods_price = cJSON_GetObjectItem(root, "goods_price");//接收新增商品价格
		cJSON *indent_discount=cJSON_GetObjectItem(root,"scancode_discount");//接收折扣信息
		if(scancode_EIC&&scancode_door&&indent_discount)//如果接收到就改变值
		{
			is_EIC=scancode_EIC->valueint;//是否开启逻辑
			is_door=scancode_door->valueint;//更新门的状态
			change_discount((float)(indent_discount->valuedouble));//更新折扣
			if(is_door)
			{
				Door_ON();
			}else
			{
				Door_OFF();
			}
		}else if(goods_id&&goods_name&&goods_barcode&&goods_price)//添加商品
		{
			goods[Goodsnum].Num=goods_id->valueint;
			goods[Goodsnum].Price=(float)(goods_id->valuedouble);
			strcpy(goods[Goodsnum].Name,goods_id->valuestring);
			strcpy((char*)(goods[Goodsnum].BarCodeID),goods_id->valuestring);
			Goodsnum++;
			Save_Goods_falsh();
		}
		cJSON_Delete(root);
	}
}
 void update_code(void)
 {
	 cJSON *root = cJSON_CreateObject();
	 if(root)
	 {
			cJSON_AddNumberToObject(root, "scancode_EIC",is_EIC );
			cJSON_AddNumberToObject(root, "scancode_door",is_door );
			char *str=cJSON_Print(root);
			usart_send_string(UART4,(u8*)str);
			cJSON_free(str);
	 }
	 cJSON_Delete(root); 
 }
 

