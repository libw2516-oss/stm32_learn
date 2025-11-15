#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint16_t CountSensor_count = 0;

void CountSensor_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式或者事件模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; //开启中断
    EXTI_Init(&EXTI_InitStructure);


    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

}

uint16_t CountSensor_Get(void){

	return CountSensor_count;
	
}

void EXTI15_10_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line14) == SET){
        Delay_ms(50);
       if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET){
            CountSensor_count ++ ;
        EXTI_ClearITPendingBit(EXTI_Line14); //清除中断标志位
        }
    }
}
