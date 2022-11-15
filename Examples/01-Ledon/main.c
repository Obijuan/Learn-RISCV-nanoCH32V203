#include "ch32v20x_gpio.h"
#include "ch32v20x_rcc.h"

#define My_RCC_APB2Periph_GPIOA           ((uint32_t)0x00000004)  
#define My_GPIO_Pin_15                     ((uint16_t)0x8000) /* Pin 15 selected */


void GPIO_Toggle_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    //-- Habilitar APB2
    RCC->APB2PCENR |= My_RCC_APB2Periph_GPIOA;
    GPIO_InitStructure.GPIO_Pin = My_GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


int main(void)
{
    GPIO_Toggle_init();
    //GPIO_WriteBit(GPIOA, My_GPIO_Pin_15, Bit_RESET);
    GPIO_WriteBit(GPIOA, My_GPIO_Pin_15, 0);

    while (1);
}
