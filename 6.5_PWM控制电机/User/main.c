#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Motor.h"
#include "KEY.h"


int main(void){

	OLED_Init();
	Motor_Init();
	KEY_Init();
	Motor_SetSpeed(0);
	
while (1)
{	

}



}
