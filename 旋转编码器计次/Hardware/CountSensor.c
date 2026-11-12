#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <stdint.h>

uint16_t CountSensor_Count;     // global Count value

void CountSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // Enable GPIOB clock
    // Additional initialization code for the count sensor can be added here
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // Enable AFIO
    
    // Configure GPIO for count sensor input
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; // Assuming the count sensor is connected to PB14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-up
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Configure EXTI line for PB14
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Adjust trigger as needed
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}

uint16_t CountSensor_GetCount(void)
{
    return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 1)
        {
            CountSensor_Count++; // Increment count on interrupt
        }
        EXTI_ClearITPendingBit(EXTI_Line14); // Clear the interrupt flag
    }
}
