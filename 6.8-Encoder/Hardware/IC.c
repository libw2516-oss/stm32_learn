#include "stm32f10x.h"

void IC_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    TIM_InternalClockConfig(TIM3);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //72000000
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;//计算频率，取大频率然后计数，基准频率除以计数值即为最终频率
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 65536 - 1; //尽量取大避免计数溢出
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1; //捕获预分频（隔几个边沿才算一次）
    TIM_ICInitStruct.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStruct);
    //方式一
    TIM_PWMIConfig(TIM3, &TIM_ICInitStruct); //两种方式等价
    /*方式二
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling; //上升沿捕获
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1; //捕获预分频（隔几个边沿才算一次）
    TIM_ICInitStruct.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStruct);*/

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1); //选择触发源
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); //设置为复位模式，输入捕获时复位计数器

    TIM_Cmd(TIM3, ENABLE); // 使能TIM3
}

uint32_t IC_Get_Freq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3) + 1); //返回计数值，结合预分频器和时基频率可以计算出输入信号的频率
}

uint32_t IC_Get_Duty(void)
{
    uint16_t capture1 = TIM_GetCapture1(TIM3) + 1;
    uint16_t capture2 = TIM_GetCapture2(TIM3) + 1;
    if(capture1 == 0) return 0;
    return (capture2 * 100) / capture1; //返回占空比，结合预分频器和时基频率可以计算出输入信号的频率
}
