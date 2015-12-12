/**
 * @file	buttons.c
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Buttons library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */
uint8_t g_Buttons_Event = 0;



uint8_t g_Buttons_TopPressEvent = 0;
uint8_t g_Buttons_MidPressEvent = 0;
uint8_t g_Buttons_BotPressEvent = 0;

/* -- Functions -- */

/**
 * Initialize Buttons
 * @param void No arguments
 * @return void No return
 */
void Buttons_Init(void)
{
	// Local variables
	GPIO_InitTypeDef GPIO_InitStruct;

	// Init GPIO
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	// Button Pins
	GPIO_InitStruct.Pin = s_BUTTONS__BTN1 | s_BUTTONS__BTN4;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_BUTTONS__BTN_A_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = s_BUTTONS__BTN3;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_BUTTONS__BTN_B_PORT, &GPIO_InitStruct);

	// EXTI interrupt init
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * Deinitialize buttons
 * @param void No arguments
 * @return void No return
 */
void Buttons_Deinit(void)
{

}


void Buttons_ClearAllEvents(void)
{
	// Debounce delay
	HAL_Delay(300);
	g_Buttons_TopPressEvent = 0;
	g_Buttons_MidPressEvent = 0;
	g_Buttons_BotPressEvent = 0;
}

