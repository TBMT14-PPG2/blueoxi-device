/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 *
 * COPYRIGHT(c) 2015 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */

#include "main.h"

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	SharpLcd_VcomHandle();

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/**
 * @brief This function handles USB On The Go FS global interrupt.
 */
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

/**
 * @brief  This function handles External line 0 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI0_IRQHandler(void)
{
	WS2812B_SendColor(128,0,0);
	HAL_GPIO_EXTI_IRQHandler(s_BUTTONS__BTN1);

	g_Buttons_Event = 1;
}

/**
 * @brief  This function handles External line 1 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI1_IRQHandler(void)
{
	WS2812B_SendColor(0,128,0);
	HAL_GPIO_EXTI_IRQHandler(s_BUTTONS__BTN4);
}

/**
 * @brief This function handles EXTI Line4 interrupt.
 */
void EXTI4_IRQHandler(void)
{

	g_Afe44xx_AdcRdy = 1;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

/**
 * @brief  This function handles External line 0 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI15_10_IRQHandler(void)
{
	WS2812B_SendColor(0,0,128);
	HAL_GPIO_EXTI_IRQHandler(s_BUTTONS__BTN3);
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void)
{
	uint32_t tmp1 = 0, tmp2 = 0;
	uint8_t byte;

	tmp1 = __HAL_UART_GET_FLAG(&g_Wifi_UartHandle, UART_FLAG_TC);
	tmp2 = __HAL_UART_GET_IT_SOURCE(&g_Wifi_UartHandle, UART_IT_TC);
	// UART in mode Transmitter end
	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		g_Wifi_UartTxReady = 1;
	}

	tmp1 = __HAL_UART_GET_FLAG(&g_Wifi_UartHandle, UART_FLAG_RXNE);
	tmp2 = __HAL_UART_GET_IT_SOURCE(&g_Wifi_UartHandle, UART_IT_RXNE);
	/* UART in mode Receiver ---------------------------------------------------*/
	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		byte = (uint16_t)((&g_Wifi_UartHandle)->Instance->DR & (uint16_t)0x00FF);
		Wifi_ProcessRx(byte);
	}

	HAL_UART_IRQHandler(&g_Wifi_UartHandle);
}

/**
 * @brief This function handles USART6 global interrupt.
 */
void USART6_IRQHandler(void)
{
	uint32_t tmp1 = 0, tmp2 = 0;
	uint8_t byte;

	tmp1 = __HAL_UART_GET_FLAG(&g_Ble_UartHandle, UART_FLAG_TC);
	tmp2 = __HAL_UART_GET_IT_SOURCE(&g_Ble_UartHandle, UART_IT_TC);
	// UART in mode Transmitter end
	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		g_Ble_UartTxReady = 1;
	}

	tmp1 = __HAL_UART_GET_FLAG(&g_Ble_UartHandle, UART_FLAG_RXNE);
	tmp2 = __HAL_UART_GET_IT_SOURCE(&g_Ble_UartHandle, UART_IT_RXNE);
	/* UART in mode Receiver ---------------------------------------------------*/
	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		byte = (uint16_t)((&g_Ble_UartHandle)->Instance->DR & (uint16_t)0x00FF);
		Ble_ProcessRx(byte);
	}

	HAL_UART_IRQHandler(&g_Ble_UartHandle);
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
