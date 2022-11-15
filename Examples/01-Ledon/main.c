#include "ch32v20x.h"

/* General Purpose I/O */
typedef struct
{
    __IO uint32_t CFGLR;
    __IO uint32_t CFGHR;
    __IO uint32_t INDR;
    __IO uint32_t OUTDR;
    __IO uint32_t BSHR;
    __IO uint32_t BCR;
    __IO uint32_t LCKR;
} GPIO_TypeDef;

/* Reset and Clock Control */
typedef struct
{
    __IO uint32_t CTLR;
    __IO uint32_t CFGR0;
    __IO uint32_t INTR;
    __IO uint32_t APB2PRSTR;
    __IO uint32_t APB1PRSTR;
    __IO uint32_t AHBPCENR;
    __IO uint32_t APB2PCENR;
    __IO uint32_t APB1PCENR;
    __IO uint32_t BDCTLR;
    __IO uint32_t RSTSCKR;

    __IO uint32_t AHBRSTR;
    __IO uint32_t CFGR2;
} RCC_TypeDef;

/* Peripheral declaration */
#define GPIOA   ((GPIO_TypeDef *)0x40010800)
#define RCC     ((RCC_TypeDef *)0x40021000)

int main(void)
{
    //-- Habilitar APB2: Puerto A
    RCC->APB2PCENR = 0x4; 

    //-- Configurar pin A15
    GPIOA->CFGHR = 0x30000000;    

    //-- Turn LED on
    GPIOA->BCR = 0x8000; 

    //-- Turn LED off
    //GPIOA->BSHR = 0x8000;

    while (1);
}
