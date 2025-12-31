#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "Encoder.h"

int16_t i;//可以使用extern在其他文件声明这个变量即可跨文件使用

int main(void){

	OLED_Init();
	ENCODER_Init();
	OLED_ShowString(1, 1, "CNT:");

while (1)
{	
	OLED_ShowSignedNum(1, 5, ENCODER_Get(), 5);
	Delay_ms(1000);
}



}
