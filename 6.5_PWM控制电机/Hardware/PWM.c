#include "stm32f10x.h"



void PWM_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable clock for TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable clock for GPIOA

    TIM_InternalClockConfig(TIM2);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //72000000
    TIM_TimeBaseStructure.TIM_Prescaler = 18 - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    //OC初始化方法一
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //关闭互补输出（只有TIM1和TIM8才有）
    TIM_OCInitStructure.TIM_Pulse = 0; //设置CCR寄存器的值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //输出极性为低电平有效
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //互补输出随便填，TIM2没有互补输出
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //普通项目一般不用，保持默认
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; //普通项目一般不用，保持默认
    TIM_OC3Init(TIM2, &TIM_OCInitStructure); //初始化TIM2通道1

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2

    //OC初始化方法二，使用结构体默认值之后对要使用的值进行修改即可
    /*
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); //用默认值初始化结构体
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出
    TIM_OCInitStructure.TIM_Pulse = TIM_OCMode_PWM1; //设置CCR寄存器的值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  //输出极性为低电平有效
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); //初始化TIM2通道1
    */
}

void PWM_SetCompare3(uint16_t i)
{

    TIM_SetCompare3(TIM2, i); // 设置比较寄存器的值，占空比50%

}

