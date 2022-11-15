#include "ch32v20x.h"

/* Peripheral declaration */
#define GPIOA_CFGHR (0x40010800 + 1*4) 
#define GPIOA_BSHR  (0x40010800 + 4*4)
#define GPIOA_BCR   (0x40010800 + 5*4)
#define RCC_APB2PCENR  (0x40021000 + 6*4)

int main(void)
{
    //-- Habilitar APB2: Puerto A
    *(uint32_t *)RCC_APB2PCENR = 0x4;

    //-- Configurar pin A15
    *(uint32_t *)GPIOA_CFGHR = 0x30000000;  

    //-- Turn LED on
    *(uint32_t *)GPIOA_BCR = 0x8000;

    //-- Turn LED off
    //*(uint32_t *)GPIOA_BSHR = 0x8000;
   

    while (1);
}
