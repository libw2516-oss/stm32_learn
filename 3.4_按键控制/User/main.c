#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

uint8_t Key_Num;

int main(void){
	LED_Init();
	KEY_Init();

while (1)
{
	Key_Num = Key_GetNum();
	if (Key_Num == 1)
	{
		LED1_Turn();
	}

	if (Key_Num == 2)
	{
		LED2_Turn();
	}
}



}
