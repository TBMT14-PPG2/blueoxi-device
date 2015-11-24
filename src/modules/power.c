/**
 * @file	power.c
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Power Supply library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */

/* -- Functions -- */

/**
 * Initialize Power Supply
 * @param void No arguments
 * @return void No return
 */
void Power_Init(void)
{
	// Local variables
	GPIO_InitTypeDef GPIO_InitStruct;

	// Init GPIO
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	// Power EN Pins (PORTB)
	GPIO_InitStruct.Pin = s_POWER__LCD_EN | s_POWER__BLE_MEMS_EN | s_POWER__PPG_EN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_POWER__PORTB, &GPIO_InitStruct);

	// Power EN Pins (PORTC)
	GPIO_InitStruct.Pin = s_POWER__WIFI_EN | s_POWER__GPS_EN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_POWER__PORTC, &GPIO_InitStruct);
}

/**
 * Deinitialize Power Supply
 * @param void No arguments
 * @return void No return
 */
void Power_Deinit(void)
{

}


