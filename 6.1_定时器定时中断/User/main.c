#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint8_t Key_Num;

int main(void){

	OLED_Init();
	OLED_ShowString(1,3,"Hello, World!");
	
while (1)
{
	
}



}
