/**
 * @file	ble.c
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * BLE library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */
uint8_t				g_Ble_UartTxReady = 0;
CircularBuffer_t	g_Ble_UartRxBuffer;

UART_HandleTypeDef	g_Ble_UartHandle;

/* -- Functions -- */

/**
 * Initialize Power Supply
 * @param void No arguments
 * @return void No return
 */
void Ble_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__USART6_CLK_ENABLE();

	// Configure UART pins
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Peripheral interrupt init
	HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART6_IRQn);

	g_Ble_UartHandle.Instance = USART6;
	g_Ble_UartHandle.Init.BaudRate = 38400;
	g_Ble_UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	g_Ble_UartHandle.Init.StopBits = UART_STOPBITS_1;
	g_Ble_UartHandle.Init.Parity = UART_PARITY_NONE;
	g_Ble_UartHandle.Init.Mode = UART_MODE_TX_RX;
	g_Ble_UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	g_Ble_UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&g_Ble_UartHandle);


	__HAL_UART_ENABLE_IT(&g_Ble_UartHandle, UART_IT_RXNE);
}

/**
 * Deinitialize Power Supply
 * @param void No arguments
 * @return void No return
 */
void Ble_Deinit(void)
{
	__USART6_CLK_DISABLE();

	// USART6 GPIO Configuration
	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

	// Peripheral interrupt Deinit
	HAL_NVIC_DisableIRQ(USART6_IRQn);
}


void Ble_ProcessRx(uint8_t Byte)
{
	g_Ble_UartRxBuffer.lock = 1;
	g_Ble_UartRxBuffer.data[g_Ble_UartRxBuffer.wrI] = Byte;
	g_Ble_UartRxBuffer.wrI = (g_Ble_UartRxBuffer.wrI + 1) % s_UTILITIES__BUFFER_SIZE;
	g_Ble_UartRxBuffer.pendingBytes++;

	// Flag buffer overflow
	if (g_Ble_UartRxBuffer.pendingBytes > s_UTILITIES__BUFFER_SIZE)
	{
		g_Ble_UartRxBuffer.overflow = 1;
	}
	g_Ble_UartRxBuffer.lock = 0;
}

void Ble_Process(void)
{
	uint8_t byte;

	// Check for pending data
	if(g_Ble_UartRxBuffer.lock == 0)
	{
		while(g_Ble_UartRxBuffer.pendingBytes)
		{
			// Read byte
			byte = g_Ble_UartRxBuffer.data[g_Ble_UartRxBuffer.rdI];
			g_Ble_UartRxBuffer.rdI = (g_Ble_UartRxBuffer.rdI + 1) % s_UTILITIES__BUFFER_SIZE;
			g_Ble_UartRxBuffer.pendingBytes--;


			// Process
			switch(byte)
			{
			case 'r' :
				WS2812B_SendColor(128,0,0);
				break;
			case 'g' :
				WS2812B_SendColor(0,128,0);
				break;
			case 'b' :
				WS2812B_SendColor(0,0,128);
				break;
			default :
				WS2812B_SendColor(0,0,0);
				break;
			}
		}
	}
}




