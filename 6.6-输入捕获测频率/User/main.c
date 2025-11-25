#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

int16_t i;//可以使用extern在其他文件声明这个变量即可跨文件使用

int main(void){

	OLED_Init();
	PWM_Init();
	IC_Init();
	OLED_ShowString(1, 1, "Freq:00000Hz");
	PWM_SetPrescaler(720 - 1); // 设置预分频器，使计数器时钟为72MHz/720=100kHz
	PWM_SetCompare1(50);

while (1)
{	
	OLED_ShowNum(1, 6, IC_Get_Freq(), 5); // 显示频率值

}



}
