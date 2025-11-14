#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t Key_Num;

int main(void){
	Buzzer_Init();
	LightSensor_Init();
while (1)
{
	if (LightSensor_GetState() == 1)
	{
		Buzzer_On();
	}
	else
	{
		Buzzer_Off();
	}
}



}
