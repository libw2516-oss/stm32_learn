#include "stm32f10x.h"

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1); // Turn off LEDs initially
};

void LED1_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_0); // Turn on LEDs
}

void LED1_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_0); 
}

void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0); 
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
    }
    
}

void LED2_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
}

void LED2_Off(void)
{
    GPIO_SetBits(GPIOA,  GPIO_Pin_1); 
}

void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1); 
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
    }

    
}
