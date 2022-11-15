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


/* Peripheral memory map */
#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */

#define APB2PERIPH_BASE                         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE                          (PERIPH_BASE + 0x20000)
#define GPIOA_BASE                              (APB2PERIPH_BASE + 0x0800)
#define RCC_BASE                                (AHBPERIPH_BASE + 0x1000)

/* Peripheral declaration */
#define GPIOA                                   ((GPIO_TypeDef *)GPIOA_BASE)
#define RCC                                     ((RCC_TypeDef *)RCC_BASE)

#define RCC_APB2Periph_GPIOA           ((uint32_t)0x00000004)  
#define My_GPIO_Pin_15                     ((uint16_t)0x8000) /* Pin 15 selected */

#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */

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
} My_RCC_TypeDef;

/* Output Maximum frequency selection */
typedef enum
{
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz,
    GPIO_Speed_50MHz
} GPIOSpeed_TypeDef;

/* Configuration Mode enumeration */
typedef enum
{
    GPIO_Mode_AIN = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD = 0x28,
    GPIO_Mode_IPU = 0x48,
    GPIO_Mode_Out_OD = 0x14,
    GPIO_Mode_Out_PP = 0x10,
    GPIO_Mode_AF_OD = 0x1C,
    GPIO_Mode_AF_PP = 0x18
} GPIOMode_TypeDef;

/* GPIO Init structure definition */
typedef struct
{
    uint16_t GPIO_Pin; /* Specifies the GPIO pins to be configured.
                          This parameter can be any value of @ref GPIO_pins_define */

    GPIOSpeed_TypeDef GPIO_Speed; /* Specifies the speed for the selected pins.
                                     This parameter can be a value of @ref GPIOSpeed_TypeDef */

    GPIOMode_TypeDef GPIO_Mode; /* Specifies the operating mode for the selected pins.
                                   This parameter can be a value of @ref GPIOMode_TypeDef */
} GPIO_InitTypeDef;

/*********************************************************************
 * @fn      GPIO_Init
 *
 * @brief   GPIOx - where x can be (A..G) to select the GPIO peripheral.
 *
 * @param   GPIO_InitStruct - pointer to a GPIO_InitTypeDef structure that
 *        contains the configuration information for the specified GPIO peripheral.
 *
 * @return  none
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;

    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

    if((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
    {
        currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
    }

    if(((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        tmpreg = GPIOx->CFGLR;

        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = ((uint32_t)0x01) << pinpos;
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

            if(currentpin == pos)
            {
                pos = pinpos << 2;
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                tmpreg |= (currentmode << pos);

                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->BCR = (((uint32_t)0x01) << pinpos);
                }
                else
                {
                    if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        GPIOx->BSHR = (((uint32_t)0x01) << pinpos);
                    }
                }
            }
        }
        GPIOx->CFGLR = tmpreg;
    }

    if(GPIO_InitStruct->GPIO_Pin > 0x00FF)
    {
        tmpreg = GPIOx->CFGHR;

        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((uint32_t)0x01) << (pinpos + 0x08));
            currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);

            if(currentpin == pos)
            {
                pos = pinpos << 2;
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                tmpreg |= (currentmode << pos);

                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->BCR = (((uint32_t)0x01) << (pinpos + 0x08));
                }

                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    GPIOx->BSHR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        GPIOx->CFGHR = tmpreg;
    }
}




int main(void)
{
    //-- Habilitar APB2
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;

    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.GPIO_Pin = My_GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-- Turn LED on
    GPIOA->BCR = My_GPIO_Pin_15;

    //-- Turn LED off
    //GPIOA->BSHR = My_GPIO_Pin_15;

    while (1);
}
