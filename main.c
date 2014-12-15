#include "LED.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Init Structure definition */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_Config(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	static volatile unsigned int i=0;

	LED_Config();
	LED_Set_Off();
	printf("Hello world\r\n");

    while(1)
    {
    	printf("Blue\r\n");
    	LED_Toggle_Start(LED_Color_Blue, 1);
    	for(i=0;i<10000000;i++);
    	LED_Toggle_Stop();
    	printf("Green\r\n");
    	LED_Toggle_Start(LED_Color_Green, 10);
    	for(i=0;i<10000000;i++);
    	LED_Toggle_Stop();
    	printf("Red\r\n");
    	LED_Toggle_Start(LED_Color_Red, 10);
    	for(i=0;i<10000000;i++);
    	LED_Toggle_Stop();
    }
    return 0;
}

