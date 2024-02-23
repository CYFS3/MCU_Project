#include "Pid.h"

PID TrackPid;//循迹PID控制器

/*PID初始化*/
void PID_Init(PID *pid, float setpoint, float kp, float ki, float kd) 
{
	pid->setpoint = setpoint;//设定值
	pid->kp = kp<0?-kp:kp;//P
	pid->ki = ki<0?-ki:ki;//I
	pid->kd = kd<0?-kd:kd;//D
	pid->pre_error = 0;//误差值
	pid->integral = 0;//积分值
}

/*PID计算*/
float PID_Compute(PID *pid, float input) 
{
	float error = pid->setpoint - input;  //计算误差
	pid->integral += error;  // 计算积分值
	float derivative = error - pid->pre_error;  // 计算微分值
	pid->pre_error = error;  // 保存当前误差为下一次计算的上一次误差
	float output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;  // 计算 PID 输出
	return output;
}

float PID_channels[5]={0,0,0,0,0};
/*PID调参*/
void PID_Adjust(PID *pid, float kp, float ki, float kd) 
{
	pid->kp = kp<0?-kp:kp;//P
	pid->ki = ki<0?-ki:ki;//I
	pid->kd = kd<0?-kd:kd;//D
}

void PID_Adjust_P(PID *pid, float kp) 
{
	pid->kp = kp<0?-kp:kp;//P
}
void PID_Adjust_I(PID *pid, float ki) 
{
	pid->ki = ki<0?-ki:ki;//I
}
void PID_Adjust_D(PID *pid, float kd) 
{
	pid->kd = kd<0?-kd:kd;//D
}
/*PID调参向上位机上传数据*/
void usart_senddatas(USART_TypeDef* USARTx,u8* addr,int size)
{
  while(size--) //判断数据发送完没有
  {
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);//等待上一个byte的数据发送结束。
    USART_SendData(USARTx,*addr);//调用STM32标准库函数发送数据
    addr++; //地址偏移
  }
}

/*发送数据到调参上位机 Mode:0为循迹PID 1为速度PID*/
void Send_PID(PID *pid,u8 Mode)
{
  u8 frameNameHead[] = "AABBCC";//定义通道名帧头帧尾
  u8 frameNameEnd[] = "CCBBAA";//定义数据帧头帧尾
  u8 frameDataHead[] = "DDEEFF";
  u8 frameDataEnd[] = "FFEEDD";
	if(Mode==0)
	{
		u8 name[] = {"P,I,D,PID_Error,Pulse_Offset"};//通道名
		PID_channels[0] = (*pid).kp;
		PID_channels[1] = (*pid).ki;
		PID_channels[2] = (*pid).kd;
		usart_senddatas(UART5,frameNameHead,sizeof(frameNameHead)-1);
		usart_senddatas(UART5,name,sizeof(name)-1);
		usart_senddatas(UART5,frameNameEnd,sizeof(frameNameEnd)-1);
		usart_senddatas(UART5,frameDataHead,sizeof(frameDataHead)-1);
		usart_senddatas(UART5,(u8*)PID_channels,sizeof(PID_channels));
		usart_senddatas(UART5,frameDataEnd,sizeof(frameDataEnd)-1);
	}
}
/*设置循迹PID反馈值到通道*/
void Set_Track_PID(float PID_Error,float Pulse_Offset)
{
	PID_channels[3]=PID_Error;
	PID_channels[4]=Pulse_Offset;
}
