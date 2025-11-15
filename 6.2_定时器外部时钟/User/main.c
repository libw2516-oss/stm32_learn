#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint8_t Num;//可以使用extern在其他文件声明这个变量即可跨文件使用

int main(void){

	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Num:"); 
	OLED_ShowString(2,1,"CNT:"); 

while (1)
{
	OLED_ShowNum(1, 5, Num, 5);
	OLED_ShowNum(2, 5, Timer_GetCount(), 5);
}

}

void TIM2_IRQHandler(void){
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){//定时器获取中断标志，IT为interrupt，这里获取的是更新中断
        
        Num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除定时器中断标志
}


}
