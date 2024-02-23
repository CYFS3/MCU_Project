#include "Encoder.h"

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Encoder_Left_Front_TIM2Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * TIM2编码器
	* A    B
  * CH1 CH2
  * PA15 PB3(重映射)
 **/
/* -------------------------------- end -------------------------------- */
void Encoder_Left_Front_TIM2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 			//	引脚初始化的结构体  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//	定时器初始化的结构体
	TIM_ICInitTypeDef TIM_ICInitStructure; 			//	定时器编码器模式初始化的结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	//	使能TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//	使能GPIOA时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//	使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //禁用JTAG
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//部分重映像
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//	浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//	根据GPIO_InitStructure的参数初始化GPIOA
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//	根据GPIO_InitStructure的参数初始化GPIOB
	
	
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 60000; 				//	设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 						//	预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//	选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//	TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 				//	根据TIM_TimeBaseInitStruct的参数初始化定时器TIM2
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3：CH1、CH2同时计数，四分频
	
	//初始化TIM2输入捕获参数
	TIM_ICStructInit(&TIM_ICInitStructure); 							//	把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICInitStructure.TIM_ICFilter = 0x03;  							// 	IC1F=0011 配置输入滤波器（连续采样八次）
	TIM_ICInit(TIM2, &TIM_ICInitStructure); 							//	根TIM_ICInitStructure参数初始化定时器TIM2编码器模式

	TIM2->CNT = ENCODER_STARTER;
	TIM_Cmd(TIM2, ENABLE); 							
}	

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Encoder_Left_Back_TIM3Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * TIM3编码器
	*  A		B
  * CH1  CH2
  * PB4  PB5
 **/
/* -------------------------------- end -------------------------------- */
void Encoder_Left_Back_TIM3Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 			//	引脚初始化的结构体  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//	定时器初始化的结构体
	TIM_ICInitTypeDef TIM_ICInitStructure; 			//	定时器编码器模式初始化的结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	//	使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//	使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能AFIO时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);//重映射
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//	PB4、PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//	浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//	根据GPIO_InitStructure的参数初始化GPIOA

	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 60000; 				//	设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 						//	预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//	选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//	TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 				//	根据TIM_TimeBaseInitStruct的参数初始化定时器TIM4

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3：CH1、CH2同时计数，四分频

	//初始化TIM3输入捕获参数
	TIM_ICStructInit(&TIM_ICInitStructure); 							//	把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICInitStructure.TIM_ICFilter = 0x03;  							// 	IC1F=0011 配置输入滤波器（连续采样八次）
	TIM_ICInit(TIM3, &TIM_ICInitStructure); 							//	根TIM_ICInitStructure参数初始化定时器TIM3编码器模式

	TIM3->CNT = ENCODER_STARTER;
	TIM_Cmd(TIM3, ENABLE); 							
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Encoder_Right_Front_TIM4Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
	* TIM4编码器
	*  B	 A
	* CH1 CH2
	* PB6 PB7
 **/
/* -------------------------------- end -------------------------------- */
void Encoder_Right_Front_TIM4Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 			//	引脚初始化的结构体  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//	定时器初始化的结构体
	TIM_ICInitTypeDef TIM_ICInitStructure; 			//	定时器编码器模式初始化的结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 	//	使能TIM4时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//	使能GPIOB时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//	PB6、PB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//	浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//	根据GPIO_InitStructure的参数初始化GPIOB
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 60000; 				//	设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 						//	预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//	选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//	TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//	根据TIM_TimeBaseInitStruct的参数初始化定时器TIM4
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3：CH1、CH2同时计数，四分频
	
	//初始化TIM4输入捕获参数
	TIM_ICStructInit(&TIM_ICInitStructure); 							//	把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICInitStructure.TIM_ICFilter = 0x03;  							// 	IC1F=0011 配置输入滤波器（连续采样八次）
	TIM_ICInit(TIM4, &TIM_ICInitStructure); 							//	根TIM_ICInitStructure参数初始化定时器TIM4编码器模式

	TIM4->CNT = ENCODER_STARTER;
	TIM_Cmd(TIM4, ENABLE); 							

}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Encoder_Right_Back_TIM5Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * TIM5编码器
	*  B   A
  * CH1 CH2
  * PA0 PA1
 **/
/* -------------------------------- end -------------------------------- */
void Encoder_Right_Back_TIM5Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 			//	引脚初始化的结构体  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//	定时器初始化的结构体
	TIM_ICInitTypeDef TIM_ICInitStructure; 			//	定时器编码器模式初始化的结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 	//	使能TIM5时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//	使能GPIOA时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//	PA0、PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//	浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//	根据GPIO_InitStructure的参数初始化GPIOA
	
	TIM_DeInit(TIM5);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 60000; 				//	设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 						//	预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//	选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//	TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 				//	根据TIM_TimeBaseInitStruct的参数初始化定时器TIM5
	
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3：CH1、CH2同时计数，四分频
	
	//初始化TIM5输入捕获参数
	TIM_ICStructInit(&TIM_ICInitStructure); 							//	把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICInitStructure.TIM_ICFilter = 0x03;  							// 	IC1F=0011 配置输入滤波器（连续采样八次）
	TIM_ICInit(TIM5, &TIM_ICInitStructure); 							//	根TIM_ICInitStructure参数初始化定时器TIM5编码器模式

	TIM5->CNT = ENCODER_STARTER;
	
	TIM_Cmd(TIM5, ENABLE); 							
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Encoder_All_TIMInit
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  *初始化所有编码器
 **/
/* -------------------------------- end -------------------------------- */
void Init_Encoder(void)
{
	Encoder_Left_Front_TIM2Init();
	Encoder_Left_Back_TIM3Init();
	Encoder_Right_Front_TIM4Init();
	Encoder_Right_Back_TIM5Init();
}
/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Read_Encoder
  * @brief  
  * @param   编码器计数
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * 读取编码器计数
 **/
/* -------------------------------- end -------------------------------- */
int Read_Encoder(u8 TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:
		 {
			 Encoder_TIM= (short)TIM2 -> CNT;
			 TIM2 -> CNT=ENCODER_STARTER;//防止超出范围
			 break;
		 }
		 case 3:
		 {
			 Encoder_TIM= (short)TIM3 -> CNT;
			 TIM3 -> CNT=ENCODER_STARTER;//防止超出范围
			 break;
		 }
		 case 4:
		 {
			 Encoder_TIM= (short)TIM4 -> CNT;
			 TIM4 -> CNT=ENCODER_STARTER;//防止超出范围
			 break;
		 }
		 case 5:
		 {
			 Encoder_TIM= (short)TIM5 -> CNT;
			 TIM5 -> CNT=ENCODER_STARTER;//防止超出范围
			 break;
		 }		 
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Get_Car_Wheel_Speed
  * @brief  
  * @param   单位时间的速度，单位m/s
  * @retval
  * @author  CYFS
  * @Data    2023-07-25
	* 使用减速比是1：20的减速箱。
	* 轮子转一圈相当于转子转20圈，而13线霍尔编码器也接在转子上，一圈产生13个脉冲，
	* 所以轮子一圈产生20*13个脉冲，然后硬件4倍频后就产生13*4*20个脉
	* 轮子的半径24mm
  * 注意要在单位时间内调用此函数，才是正确的速度，此函数的单位时间为0.1s
 **/
/* -------------------------------- end -------------------------------- */
int Encoder_Val=0;  //编码器脉冲数
float CarSpeed=0;//单位时间内小车的速度
float Distance=0;//单位时间内的距离

float GetCarSpeed(WheelNumber WHEEL)
{
		Encoder_Val=Read_Encoder(WHEEL)-ENCODER_STARTER;                   //读取编码器脉冲个数
		Distance = (float)Encoder_Val/1040*2*3.1415*0.24;//计算距离
		CarSpeed = Distance/0.1;//计算速度，单位m/s
		return CarSpeed;
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    get_Car_All_Speed
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-25
	* 测四轮的速度，已经平均速度和平均路程
 **/
/* -------------------------------- end -------------------------------- */
float Car_Wheel_Speed[4];//单位时间内小车轮子的速度
float oneDistanceSum=0;//单位时间内四轮的路程总和
float DistanceSum=0;//行使的总路程
float Car_Speed=0;//小车的平均速度
void get_Car_All_Speed(void)
{
	Car_Speed=0;
	oneDistanceSum=0;
	for(int i=0;i<4;i++)
	{
		Encoder_Val=Read_Encoder(i+2) - ENCODER_STARTER;					 //读取编码器脉冲个数
		Distance = (float)Encoder_Val/1040*2*3.1415*0.24;//计算距离
		Car_Wheel_Speed[i]=Distance/0.1;
		oneDistanceSum+=Distance>0?Distance:-Distance;
		Car_Speed+=Car_Wheel_Speed[i];
	}
	DistanceSum+=(oneDistanceSum / 4);
	Car_Speed=Car_Speed / 4;
}
	

