#include "Openmv.h"
void strart_face(void)
{
	usart_send_string(USART3,(u8*)"A");//向openmv发送开始识别人脸的指令
}
unsigned char Get_num(void)
{
	return USART3_RecProcess();
	
}

/*处理openmv返回的数据*/
void DisposeReturnData(u8 *str)
{
	//printf("处理数据");
	setReturnOpenmv(str);
}

