#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"

int16_t i;//可以使用extern在其他文件声明这个变量即可跨文件使用

int main(void){

	OLED_Init();
	PWM_Init();

while (1)
{	
	for(i=0;i<=100;i=i+1)
	{
		PWM_SetComparel(i);
		Delay_ms(10);
	}
	for(i=100;i>=0;i=i-1)
	{
		PWM_SetComparel(i);
		Delay_ms(10);
	}

}



}
