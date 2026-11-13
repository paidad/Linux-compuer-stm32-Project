#include "stm32f10x.h"

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable TIM2 clock

    TIM_InternalClockConfig(TIM2); // Configure TIM2 to use internal clock


    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // Count up
    timerInitStructure.TIM_Period = 1000 - 1; // Set the period
    timerInitStructure.TIM_Prescaler = 7200 - 1; // Set the prescaler
    timerInitStructure.TIM_RepetitionCounter = 0; // No repetition
    TIM_TimeBaseInit(TIM2, &timerInitStructure); // Initialize TIM2 with

    TIM_ClearFlag(TIM2, TIM_FLAG_Update); // Clear the update flag
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Enable update interrupt

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority grouping

    NVIC_InitTypeDef nvicInitStructure;
    nvicInitStructure.NVIC_IRQChannel = TIM2_IRQn; // Set the IRQ channel for TIM2
    nvicInitStructure.NVIC_IRQChannelPreemptionPriority = 2; // Set preemption priority
    nvicInitStructure.NVIC_IRQChannelSubPriority = 1; // Set subpriority
    nvicInitStructure.NVIC_IRQChannelCmd = ENABLE; // Enable the IRQ channel
    NVIC_Init(&nvicInitStructure);

    TIM_Cmd(TIM2, ENABLE); // Start TIM2

}



