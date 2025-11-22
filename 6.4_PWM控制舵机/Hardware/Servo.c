#include "stm32f10x.h"
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();

}

void Servo_SetAngle(int8_t angle)
{
    // 舵机的PWM周期为20ms
    // 角度值范围为-90到+90度
    // 对应的PWM脉宽范围为0.5ms到2.5ms
    int8_t compareValue = 1500 + angle* 2000 / 180 ; // 1ms + (angle/180)*1ms
    PWM_SetCompare2(compareValue);
}
