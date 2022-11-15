#include "ch32v20x_gpio.h"
#include "ch32v20x_rcc.h"

void GPIO_Toggle_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


int main(void)
{
    GPIO_Toggle_init();
    GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_RESET);

    while (1);
}
