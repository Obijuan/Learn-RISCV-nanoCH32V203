#include "ch32v20x.h"

/* Peripheral memory map */
#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */
  #define APB2PERIPH_BASE                         (PERIPH_BASE + 0x10000)
    #define GPIOA_BASE                              (APB2PERIPH_BASE + 0x0800)

  #define AHBPERIPH_BASE                          (PERIPH_BASE + 0x20000)
    #define RCC_BASE                                (AHBPERIPH_BASE + 0x1000)

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
#define GPIOA                                   ((GPIO_TypeDef *)GPIOA_BASE)
#define RCC                                     ((RCC_TypeDef *)RCC_BASE)
#define RCC_APB2Periph_GPIOA           ((uint32_t)0x00000004)  
#define GPIO_Pin_15                     ((uint16_t)0x8000) /* Pin 15 selected */


int main(void)
{
    //-- Habilitar APB2
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;

    //-- Configurar pin A15
    GPIOA->CFGHR = 0x30000000;    

    //-- Turn LED on
    GPIOA->BCR = GPIO_Pin_15;

    //-- Turn LED off
    //GPIOA->BSHR = GPIO_Pin_15;

    while (1);
}
