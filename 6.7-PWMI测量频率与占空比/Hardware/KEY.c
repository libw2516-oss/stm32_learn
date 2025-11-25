#include "stm32f10x.h"
#include "Delay.h"


void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20); //消除按键按下时的抖动
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0); //检测按键释放
        Delay_ms(20); //消除按键释放时的抖动
        KeyNum = 1;
    }
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20); //消除按键按下时的抖动
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0); //检测按键释放
        Delay_ms(20); //消除按键释放时的抖动
        KeyNum = 2;
    }

    return KeyNum;
}

