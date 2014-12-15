#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include <misc.h>
#include "LED.h"

/* Private variables ---------------------------------------------------------*/
static LED_Color Current_LED_Color = LED_Color_Red;

/* Private functions ---------------------------------------------------------*/
void LED_Config(void)
{
	/* Init Structure definition */
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable GPIOC clock */
	RCC_APB2PeriphClockCmd(LED_GPIO_Clk, ENABLE);
	/* PCLK1 = HCLK */
	RCC_PCLK1Config(RCC_HCLK_Div1);
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIO Configurtion */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

}
/* Toggle_Period in tenths of seconds: 1s <=> Toggle_Period = 10
   Toggle_Period min = 1 and max = 131                                */
void LED_Toggle_Start(LED_Color Color, uint16_t Toggle_Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	Current_LED_Color = Color;

	TIM_TimeBaseStructure.TIM_Period = (Toggle_Period * 500) - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 10000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	TIM_Cmd(TIM2,ENABLE);
}

void LED_Toggle_Stop(void)
{
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM2,DISABLE);
	LED_Set_Off();
}

inline void LED_Set_Color(LED_Color Color)
{
	/* All the colors are switched off ie LED switched off       */
	/* All bits set to 1                                         */
	LED_GPIO_PORT->BSRR = LED_GPIO_Pin_All;
	/* The corresponding color bits of Color are set to 0        */
	/* (inverted: 0 = color switched on, 1 = color switched off) */
	LED_GPIO_PORT->BRR = Color;
}

inline void LED_Set_Off(void)
{
	/* All the colors are switched off ie LED switched off       */
	/* All bits set to 1                                         */
	LED_GPIO_PORT->BSRR = LED_GPIO_Pin_All;
}

inline void LED_Toggle(LED_Color Color)
{
	LED_GPIO_PORT->ODR ^= Color;
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		LED_Toggle(Current_LED_Color);
	}

}
