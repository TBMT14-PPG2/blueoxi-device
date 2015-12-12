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
ADC_HandleTypeDef g_Power_AdcHandle;

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
	ADC_ChannelConfTypeDef sConfig;

	// Init GPIO
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	// ADC Clock
	__ADC1_CLK_ENABLE();

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

	// Battery Level EN Pins (PORTC)
	GPIO_InitStruct.Pin = s_POWER__BAT_LVL_EN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_POWER__BAT_LVL_EN_PORT, &GPIO_InitStruct);

	// Charge status
	GPIO_InitStruct.Pin = s_POWER__CHARGE_STAT;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(s_POWER__CHARGE_STAT_PORT, &GPIO_InitStruct);

	// Battery Level Pin
	GPIO_InitStruct.Pin = s_POWER__BAT_LVL;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(s_POWER__BAT_LVL_PORT, &GPIO_InitStruct);


	// Configure ADC
	g_Power_AdcHandle.Instance = ADC1;
	g_Power_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
	g_Power_AdcHandle.Init.Resolution = ADC_RESOLUTION12b;
	g_Power_AdcHandle.Init.ScanConvMode = DISABLE;
	g_Power_AdcHandle.Init.ContinuousConvMode = DISABLE;
	g_Power_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	g_Power_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_Power_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_Power_AdcHandle.Init.NbrOfConversion = 1;
	g_Power_AdcHandle.Init.DMAContinuousRequests = DISABLE;
	g_Power_AdcHandle.Init.EOCSelection = EOC_SINGLE_CONV;
	HAL_ADC_Init(&g_Power_AdcHandle);

	// Configure ADC Channel
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&g_Power_AdcHandle, &sConfig);


	// Turn everything off
	s_POWER__LCD_EN_RESET();
	s_POWER__BLE_MEMS_EN_RESET();
	s_POWER__WIFI_EN_RESET();
	s_POWER__GPS_EN_RESET();
	s_POWER__PPG_EN_RESET();
}

/**
 * Deinitialize Power Supply
 * @param void No arguments
 * @return void No return
 */
void Power_Deinit(void)
{

}



uint32_t Power_BateryLevel(void)
{
	ADC_ChannelConfTypeDef sConfig;

	float32_t temp;
	uint32_t adcValue = 0;

	// Enable Bat Level
	s_POWER__BAT_LVL_EN_SET();

	// Start ADC
	HAL_ADC_Start(&g_Power_AdcHandle);
	if (HAL_ADC_PollForConversion(&g_Power_AdcHandle, 1000) == HAL_OK)
	{
		adcValue = HAL_ADC_GetValue(&g_Power_AdcHandle);
	}

	// Enable Bat Level
	s_POWER__BAT_LVL_EN_RESET();


	// Calculate battey
	temp = (3.30f / 4096.0f) * (adcValue * 2);

	return ((uint32_t)(temp * 1000) - 3500) / 7;
}




