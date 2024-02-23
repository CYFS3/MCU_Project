#include "Track.h"

#define CONTROL_MIN -100
#define CONTROL_MAX 100
#define PULSE_MIN 0
#define PULSE_MAX 999
#define BASE_SPEED 500 //基础速度

void Init_Track(void)
{
	PID_Init(&TrackPid,0,0.1,0.01,0.5);//初始化PID
}

/*PID输出值转化为脉冲值*/
int control_value_to_pulse(float control_value) 
{
    if(control_value < CONTROL_MIN) control_value = CONTROL_MIN;
    if(control_value > CONTROL_MAX) control_value = CONTROL_MAX;
    float normalized_control_value = (control_value - CONTROL_MIN) / (CONTROL_MAX - CONTROL_MIN);
    int pulse = PULSE_MIN + normalized_control_value * (PULSE_MAX - PULSE_MIN);
    return pulse;
}
/*循迹*/
void Track(void)
{
	float target_position = 3.5;//定位3 4传感器为正中间取平均3.5
	float actual_position = 0;
	int weights[8] = {0, 1, 2, 3, 4, 5, 6, 7};//定义权重
	u8* R=Update_Grayscale();//读取灰度值
	int total_weight = 0;  //记录所有在黑线上的传感器的权重之和
	for(int i = 0; i < 8; i++) 
	{
		if(R[i] == 0)//传感器i检测到黑线
		{
			actual_position += weights[i];
			total_weight += 1;
		}
	}
	if(total_weight > 0) 
	{//至少有一个传感器检测到黑线
		actual_position /= total_weight;  // 计算在黑线上的传感器的平均位置
	}else actual_position = target_position; // 所有传感器都没有检测到黑线 保持上一次的控制输出不变
	float error = target_position - actual_position;//计算误差
	float control_value = PID_Compute(&TrackPid, (float)error);//传入反馈量
	int pulse = control_value_to_pulse(control_value);//控制量转脉冲值
	int pulse_offset = control_value_to_pulse(control_value) - BASE_SPEED;//转化为脉冲值偏移量
	Set_PWM_Compare1(BASE_SPEED + pulse_offset);  // 更新左轮速度
	Set_PWM_Compare2(BASE_SPEED + pulse_offset);  // 更新左轮速度
  Set_PWM_Compare3(BASE_SPEED - pulse_offset);  // 更新右轮速度
	Set_PWM_Compare4(BASE_SPEED - pulse_offset);  // 更新右轮速度
	Set_Track_PID(error,pulse_offset);//调参反馈
	Send_PID(&TrackPid,0);//上传PID参数
}
