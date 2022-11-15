#include "ch32v20x_rcc.h"

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    RCC->APB2PCENR |= RCC_APB2Periph;
}

