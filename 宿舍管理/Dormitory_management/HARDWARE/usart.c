#include "usart.h"
#include "config.h"

u8 usart1_rx_buf[256];//存放接收的数据
u16 usart1_pos=0;//最后一个字符位置
u8 usart2_rx_buf[256];//存放接收的数据
u16 usart2_pos=0;//最后一个字符位置


/*初始化串口1*/
void init_usart1(u32 USART1_BaudRate)
{
    /*结构体声明*/
    GPIO_InitTypeDef GPIO_struct_TX;//串口发送的GPIO载入的配置
    GPIO_InitTypeDef GPIO_struct_RX;//串口接收的GPIO载入的配置
    USART_InitTypeDef USART1_struct;//串口1的配置
    NVIC_InitTypeDef NVIC_InitStruct;//接收中断配置
    /*串口1------------------------------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//对PA口与串口1时钟总线使能
    /*PA9 TX发送GPIO 串口1 初始化*/
    GPIO_struct_TX.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_struct_TX.GPIO_Pin=GPIO_Pin_9;
    GPIO_struct_TX.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_struct_TX);
    /*PA10 RX接收GPIO 串口1*/
    GPIO_struct_RX.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_struct_RX.GPIO_Pin=GPIO_Pin_10;
    GPIO_struct_RX.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_struct_RX);
    /*初始化并加载串口1配置*/
    USART1_struct.USART_BaudRate=USART1_BaudRate;//通信波特率
    USART1_struct.USART_WordLength=USART_WordLength_8b;//指定帧中传输或接收的数据位数
    USART1_struct.USART_StopBits=USART_StopBits_1;//指定传输的停止位数
    USART1_struct.USART_Parity=USART_Parity_No;//指定校验模式.
    USART1_struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//指定是否启用或禁用接收或发送模式
    USART1_struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控模式启用或关闭
    USART_Init(USART1,&USART1_struct);
    /*初始化串口1接收中断*/
    NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&NVIC_InitStruct);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启串口1接收中断
    USART_Cmd(USART1,ENABLE);//串口1使能
    USART_ClearFlag(USART1,USART_FLAG_TC);//清除标志位
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

/*printf重定向到串口1*/
int fputc(int ch,FILE *f)
{
    USART_SendData(USART1,(u16)ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
    return (ch);
}

/*串口1接收中断函数 在启动文件找*/
void USART1_IRQHandler(void)
{
    u8 RecCh;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
    {
        USART1RecTimer=10;
        RecCh=(u8)(USART_ReceiveData(USART1));
        usart1_rx_buf[usart1_pos++]=RecCh;
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
/*串口1数据接收触发(10ms)*/


unsigned char USART1_RecProcess(void)
{
    if(USART1RecTimer)return false;
    if(!usart1_pos)return false;
    usart1_rx_buf[usart1_pos]='\0';
    /*清空接收字符存储区*/
    if(strcmp((char*)usart1_rx_buf,(char*)"open") == 0)
    {
        MQTT_Send_Door_Open();
    }
    else
    {
        usart_send_string(USART2,usart1_rx_buf);

    }

    memset(usart1_rx_buf,0,256);
    usart1_pos=0;
    return true;
}
/*串口2接收中断函数*/
void USART2_IRQHandler(void)
{
    u8 RecCh;
    if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
    {
        USART2RecTimer=10;
        RecCh=(u8)USART_ReceiveData(USART2);
        usart2_rx_buf[usart2_pos++]=RecCh;
    }
    USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}
unsigned char USART2_RecProcess(void)
{
    if(USART2RecTimer)return false;
    if(!usart2_pos)return false;
    usart2_rx_buf[usart2_pos]='\0';
    /*清空接收字符存储区*/

    Esp_Read((char*)usart2_rx_buf);
    memset(usart2_rx_buf,0,256);
    usart2_pos=0;
    return true;
}




