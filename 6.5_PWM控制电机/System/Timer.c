#include "stm32f10x.h"

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//第一步开启定时器2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x06);//数来自这个引脚的脉冲
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频系数为1（滤波器采样频率，对定时器基本无影响）
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上向下以及中央对齐计数，一般选向上
	TIM_TimeBaseStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//高级计数器，一般不用
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//时基单元初始化时会自动执行一次中断（TimeBaseInit中）以加载某些值，会导致初始化时直接执行一次中断
//因此建议在执行初始化时进行一次标志位清楚
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//允许定时器中断，这里是更新中断

	//NVIC中断设置，设置中断优先级、是否中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级组,即两个抢占优先级，两个响应优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//选择定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 02;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
	NVIC_Init(&NVIC_InitStructure);

	//启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

uint16_t Timer_GetCount(void)
{
    return TIM_GetCounter(TIM2);
}
//定时器中断服务函数(需要自己定义),可以直接放在main函数中
/*
void TIM2_IRQHandler(void){
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){//定时器获取中断标志，IT为interrupt，这里获取的是更新中断
        
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除定时器中断标志
}


}*/
