/**
 * @file	motor.c
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Vibration motor library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */

/* -- Functions -- */

/**
 * Initialize Vibration Motor
 * @param void No arguments
 * @return void No return
 */
void Motor_Init(void)
{
	// Local variables
	GPIO_InitTypeDef GPIO_InitStruct;

	// Init GPIO
	__GPIOB_CLK_ENABLE();

	// Control Pins
	GPIO_InitStruct.Pin = s_MOTOR__DRIVE;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_MOTOR__DRIVE_PORT, &GPIO_InitStruct);

}

/**
 * Deinitialize Vibration Motor
 * @param void No arguments
 * @return void No return
 */
void Motor_Deinit(void)
{

}


