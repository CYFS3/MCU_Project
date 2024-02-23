#include "USART.h"
#include <stdarg.h>
#include "Queue.h"

void USARTInit(void)
{
    //1.开启时钟GPIO、USART1、重映射要开启AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
    //2.初始化GPIO
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽复用输出//外设GPIO口的工作方式，找110（参考手册的P110页）
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitTypeDef  USART_InitStructure;
    USART_InitStructure.USART_BaudRate=USART1_BAUD;//波特率，通常1200的整数倍，9600,115200,57600
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控，无
    USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//工作方式：发送和接收
    USART_InitStructure.USART_Parity=USART_Parity_No;//无校验
    USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;//数据位8位
    USART_Init(USART1,&USART_InitStructure);
    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//中断通道号到stm32f10x.h里找IRQn
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//中断使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//主优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;				//次优先级

    NVIC_Init(&NVIC_InitStructure);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);


    USART_Cmd(USART1,ENABLE);
    USART_ClearFlag(USART1,USART_FLAG_TC);
}

void USARTSendByte(USART_TypeDef* USARTx,u8 ch)
{
    USART_SendData(USARTx,(u16)ch);
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET) {;}
}
void USARTSendString(USART_TypeDef* USARTx,u8 *str)
{
    u32 pos=0;

    while(*(str+pos)!='\0')
    {
        USARTSendByte(USARTx,*(str+pos));
        pos++;
    }

}


int fputc(int ch,FILE *f) 
{
    USART_SendData(USART1,(u16)ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET) {;}
    return ch;

}
/*初始化串口2*/
void init_usart2(u32 USART2_BaudRate)
{
	/*结构体声明*/
	GPIO_InitTypeDef GPIO_struct_TX;//串口发送的GPIO载入的配置
	GPIO_InitTypeDef GPIO_struct_RX;//串口接收的GPIO载入的配置
	USART_InitTypeDef USART2_struct;//串口2的配置
	NVIC_InitTypeDef NVIC_InitStruct;//接收中断配置
	/*串口2-------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	/*PA2 USART2_TX 串口2发送*/
	GPIO_struct_TX.GPIO_Pin=GPIO_Pin_2;
	GPIO_struct_TX.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_struct_TX.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_struct_TX);
	/*PA3 USART2_RX 串口2接收*/
	GPIO_struct_RX.GPIO_Pin=GPIO_Pin_3;
	GPIO_struct_RX.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_struct_RX.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_struct_RX);
	/*初始化并加载串口2配置*/
	USART2_struct.USART_BaudRate=USART2_BaudRate;
	USART2_struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART2_struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART2_struct.USART_Parity=USART_Parity_No;
	USART2_struct.USART_StopBits=USART_StopBits_1;
	USART2_struct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART2_struct);
	/*配置串口2中断接收*/
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启串口2的接收中断
	USART_Cmd(USART2,ENABLE);//串口2使能
	USART_ClearFlag(USART2,USART_FLAG_TC);//清除接收标志位
}

/*串口2接收中断函数*/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
         EnQueue(&queue,(u8)USART_ReceiveData(USART2));
        
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}


/*发送一个字符*/
void usart_send_byte(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx,(u16)ch); //发送一个字节
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//获取串口标志位
}
/*发送一个字符串*/
void usart_send_string(USART_TypeDef* USARTx,u8 str[])
{
	u32 pos=0;
	while(*(str+pos)!='\0')
	{
		usart_send_byte(USARTx,*(str+pos));
		pos++;
	}
}
char String[128];
void Serial_Printf(USART_TypeDef* USARTx,char *format, ...)
{

	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	usart_send_string(USARTx,(u8*)String);
}

u8 USART1_RxBUF[USART1_RXBUF_SIZE];
u16 USART1_RecPos=0;

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
    {
        USART1RecTimer=USART1RecTimerPeriod;//重置接收间隔时间
        USART1_RxBUF[USART1_RecPos++]=(u8)USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}

unsigned char USART1_RecProsess(void) 
{
    if(USART1RecTimer!=0)return false;
    if(USART1_RecPos==0)return false;
    USART1_RxBUF[USART1_RecPos]='\0';
    messageSetPID((char*)USART1_RxBUF);
    memset(USART1_RxBUF,0,USART1_RXBUF_SIZE);
    USART1_RecPos=0;
    return true;
}


