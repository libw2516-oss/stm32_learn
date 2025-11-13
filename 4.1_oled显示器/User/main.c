#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint8_t Key_Num;

int main(void){

	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"Hello, World!");
	OLED_ShowNum(2,1,1234,5);
	OLED_ShowBinNum(3,1,0xAA55,16);
	OLED_Clear();

while (1)
{
	
}



}
