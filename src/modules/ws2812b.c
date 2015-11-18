/**
 * @file	ws2812b.c
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * WS2812B library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */

/* -- Functions -- */

/**
 * Initialize WS2812B
 * @param void No arguments
 * @return void No return
 */
void WS2812B_Init(void)
{
	// Local variables
	GPIO_InitTypeDef GPIO_InitStruct;

	// Init GPIO
	__GPIOC_CLK_ENABLE();

	// Control Pins
	GPIO_InitStruct.Pin = s_WS2812B__DATA;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_WS2812B__DATA_PORT, &GPIO_InitStruct);

}

/**
 * Deinitialize WS2812B
 * @param void No arguments
 * @return void No return
 */
void WS2812B_Deinit(void)
{

}

/**
 * Simple delay for WS2812B
 * @param Count Number of cycles for delay
 * @return void No return
 */
void WS2812B_Delay(volatile uint32_t Count)
{
  for(; Count != 0; Count--);
}

/**
 * Send one bit to WS2812B
 * @param Bit Bit to send, zero for zero, else for one
 * @return void No return
 */
void WS2812B_SendBit(uint8_t Bit)
{
	if(Bit == 0) {
		s_WS2812B__DATA_SET();
		WS2812B_Delay(s_WS2812B__T0H);
		s_WS2812B__DATA_RESET();
		WS2812B_Delay(s_WS2812B__T0L);
	}
	else {
		s_WS2812B__DATA_SET();
		WS2812B_Delay(s_WS2812B__T1H);
		s_WS2812B__DATA_RESET();
		WS2812B_Delay(s_WS2812B__T1L);
	}
}

/**
 * Send one byte to WS2812B
 * @param Byte Byte to send to WS2812B
 * @return void No return
 */
void WS2812B_SendByte(uint8_t Byte)
{
	int8_t i;

	for(i = 7; i >= 0; i--) {
		WS2812B_SendBit(Byte & (1 << i));
	}
}

/**
 * Set color of WS2812B LEDs
 * @param Red Intensity value for the red LED
 * @param Green Intensity value for the green LED
 * @param Blue Intensity value for the blue LED
 * @return void No return
 */
void WS2812B_SendColor(uint8_t Red, uint8_t Green, uint8_t Blue)
{
	WS2812B_SendByte(Green);
	WS2812B_SendByte(Red);
	WS2812B_SendByte(Blue);
}

