/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

#include <stm32f10x_gpio.h>

/* Private define ------------------------------------------------------------*/
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_Clk RCC_APB2Periph_GPIOC
#define LED_GPIO_Pin_Red GPIO_Pin_2
#define LED_GPIO_Pin_Green GPIO_Pin_1
#define LED_GPIO_Pin_Blue GPIO_Pin_0
#define LED_GPIO_Pin_All LED_GPIO_Pin_Blue|LED_GPIO_Pin_Green|LED_GPIO_Pin_Red /* the 3 Pins connected to the 3 bits LED giving 8 LED states */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum
{	LED_Color_White = LED_GPIO_Pin_Blue|LED_GPIO_Pin_Green|LED_GPIO_Pin_Red ,
	LED_Color_Yellow = LED_GPIO_Pin_Green|LED_GPIO_Pin_Red ,
	LED_Color_Purple = LED_GPIO_Pin_Blue|LED_GPIO_Pin_Red ,
	LED_Color_Red = LED_GPIO_Pin_Red,
	LED_Color_Turquoise = LED_GPIO_Pin_Blue|LED_GPIO_Pin_Green,
	LED_Color_Green = LED_GPIO_Pin_Green,
	LED_Color_Blue = LED_GPIO_Pin_Blue
}LED_Color;

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void LED_Config(void);
void LED_Toggle_Start(LED_Color Color, uint16_t Toggle_Period);
void LED_Toggle_Stop(void);
void LED_Set_Color(LED_Color Color);
void LED_Set_Off(void);

#endif
