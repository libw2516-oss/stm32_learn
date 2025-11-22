#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Servo.h"
#include "KEY.h"

uint8_t KeyNum;//可以使用extern在其他文件声明这个变量即可跨文件使用
int16_t angle = -90;

int main(void){

	OLED_Init();
	Servo_Init();
	KEY_Init();
	Servo_SetAngle(angle);
	
while (1)
{	
	KeyNum = Key_GetNum();
	if (KeyNum == 2)
	{
		angle += 30;
		if (angle > 90)
		{
			angle = -90;
		}
		
	}
	Servo_SetAngle(angle);
}



}
