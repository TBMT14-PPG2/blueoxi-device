/**
 * @file	afe44xx.c
 * @author  Eriks & Janis Zaharans
 * @date    25 Nov 2015
 *
 * @section DESCRIPTION
 *
 * AFE44XX PPG Front-End library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"
#include "afe44xx_config.h"

/* -- Defines -- */

/* -- Variables -- */
SPI_HandleTypeDef	g_Afe44xx_SpiHandle;
volatile uint8_t 	g_Afe44xx_AdcRdy = 0;

/* -- Functions -- */

void Afe44xx_ConfigHw(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// Enable Clocks
	__SPI1_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	// Configure SPI
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure Other GPIO
	// STE
	GPIO_InitStruct.Pin = s_AFE44XX__STE;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_AFE44XX__STE_PORT, &GPIO_InitStruct);

	// ADC_RDY
	GPIO_InitStruct.Pin = s_AFE44XX__ADC_RDY;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(s_AFE44XX__ADC_RDY_PORT, &GPIO_InitStruct);

	// PDN
	GPIO_InitStruct.Pin = s_AFE44XX__PDN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_AFE44XX__PDN_PORT, &GPIO_InitStruct);

	// RESET
	GPIO_InitStruct.Pin = s_AFE44XX__RST;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_AFE44XX__RST_PORT, &GPIO_InitStruct);

	// Configure GPIO interrupt
	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	// Configure SPI
	g_Afe44xx_SpiHandle.Instance = SPI1;
	g_Afe44xx_SpiHandle.Init.Mode = SPI_MODE_MASTER;
	g_Afe44xx_SpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
	g_Afe44xx_SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	g_Afe44xx_SpiHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
	g_Afe44xx_SpiHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	g_Afe44xx_SpiHandle.Init.NSS = SPI_NSS_SOFT;
	g_Afe44xx_SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	g_Afe44xx_SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	g_Afe44xx_SpiHandle.Init.TIMode = SPI_TIMODE_DISABLED;
	g_Afe44xx_SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	g_Afe44xx_SpiHandle.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&g_Afe44xx_SpiHandle);


	// Reset off
	s_AFE44XX__RST_OFF();
	// Deselect
	s_AFE44XX__DESELECT();
	// Turn on
	s_AFE44XX__ON();
}



void Afe44xx_Init(void)
{
	// Configure hardware
	//Afe44xx_ConfigHw();

	// Configure registers

	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x00000000);

	Afe44xx_WriteRegister(s_AFE44XX__LED2STC, s_AFE44XX_CFG__LED2STC);
	Afe44xx_WriteRegister(s_AFE44XX__LED2ENDC, s_AFE44XX_CFG__LED2ENDC);
	Afe44xx_WriteRegister(s_AFE44XX__LED2LEDSTC, s_AFE44XX_CFG__LED2LEDSTC);
	Afe44xx_WriteRegister(s_AFE44XX__LED2LEDENDC, s_AFE44XX_CFG__LED2LEDENDC);
	Afe44xx_WriteRegister(s_AFE44XX__ALED2STC, s_AFE44XX_CFG__ALED2STC);
	Afe44xx_WriteRegister(s_AFE44XX__ALED2ENDC, s_AFE44XX_CFG__ALED2ENDC);
	Afe44xx_WriteRegister(s_AFE44XX__LED1STC, s_AFE44XX_CFG__LED1STC);
	Afe44xx_WriteRegister(s_AFE44XX__LED1ENDC, s_AFE44XX_CFG__LED1ENDC);
	Afe44xx_WriteRegister(s_AFE44XX__LED1LEDSTC, s_AFE44XX_CFG__LED1LEDSTC);
	Afe44xx_WriteRegister(s_AFE44XX__LED1LEDENDC, s_AFE44XX_CFG__LED1LEDENDC);
	Afe44xx_WriteRegister(s_AFE44XX__ALED1STC, s_AFE44XX_CFG__ALED1STC);
	Afe44xx_WriteRegister(s_AFE44XX__ALED1ENDC, s_AFE44XX_CFG__ALED1ENDC);
	Afe44xx_WriteRegister(s_AFE44XX__LED2CONVST, s_AFE44XX_CFG__LED2CONVST);
	Afe44xx_WriteRegister(s_AFE44XX__LED2CONVEND, s_AFE44XX_CFG__LED2CONVEND);
	Afe44xx_WriteRegister(s_AFE44XX__ALED2CONVST, s_AFE44XX_CFG__ALED2CONVST);
	Afe44xx_WriteRegister(s_AFE44XX__ALED2CONVEND, s_AFE44XX_CFG__ALED2CONVEND);
	Afe44xx_WriteRegister(s_AFE44XX__LED1CONVST, s_AFE44XX_CFG__LED1CONVST);
	Afe44xx_WriteRegister(s_AFE44XX__LED1CONVEND, s_AFE44XX_CFG__LED1CONVEND);
	Afe44xx_WriteRegister(s_AFE44XX__ALED1CONVST, s_AFE44XX_CFG__ALED1CONVST);
	Afe44xx_WriteRegister(s_AFE44XX__ALED1CONVEND, s_AFE44XX_CFG__ALED1CONVEND);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTSTCT0, s_AFE44XX_CFG__ADCRSTSTCT0);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTENDCT0, s_AFE44XX_CFG__ADCRSTENDCT0);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTSTCT1, s_AFE44XX_CFG__ADCRSTSTCT1);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTENDCT1, s_AFE44XX_CFG__ADCRSTENDCT1);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTSTCT2, s_AFE44XX_CFG__ADCRSTSTCT2);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTENDCT2, s_AFE44XX_CFG__ADCRSTENDCT2);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTSTCT3, s_AFE44XX_CFG__ADCRSTSTCT3);
	Afe44xx_WriteRegister(s_AFE44XX__ADCRSTENDCT3, s_AFE44XX_CFG__ADCRSTENDCT3);
	Afe44xx_WriteRegister(s_AFE44XX__PRPCOUNT, s_AFE44XX_CFG__PRPCOUNT);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL1, s_AFE44XX_CFG__CONTROL1);
	Afe44xx_WriteRegister(s_AFE44XX__TIAGAIN, s_AFE44XX_CFG__TIAGAIN);
	Afe44xx_WriteRegister(s_AFE44XX__TIA_AMB_GAIN, s_AFE44XX_CFG__TIA_AMB_GAIN);
	Afe44xx_WriteRegister(s_AFE44XX__LEDCNTRL, s_AFE44XX_CFG__LEDCNTRL);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL2, s_AFE44XX_CFG__CONTROL2);
	Afe44xx_WriteRegister(s_AFE44XX__ALARM, s_AFE44XX_CFG__ALARM);

}


uint32_t Afe44xx_ReadRegister(uint8_t Addr)
{
	uint8_t data[3];
	uint32_t res = 0;

	s_AFE44XX__SELECT();

	// Transmit address
	HAL_SPI_Transmit(&g_Afe44xx_SpiHandle, &Addr, 1, 1000);

	// Read Data
	HAL_SPI_Receive(&g_Afe44xx_SpiHandle, data, 3, 1000);

	res |= data[0] << 16;
	res |= data[1] << 8;
	res |= data[2];

	s_AFE44XX__DESELECT();

	return res;
}

void Afe44xx_WriteRegister(uint8_t Addr, uint32_t Data)
{
	uint8_t data[4];

	data[0] = Addr;
	data[1] = (Data>>16) & 0xFF;
	data[2] = (Data>>8) & 0xFF;
	data[3] = (Data) & 0xFF;

	s_AFE44XX__SELECT();

	// Transmit address and data
	HAL_SPI_Transmit(&g_Afe44xx_SpiHandle, data, 4, 1000);

	s_AFE44XX__DESELECT();
}






Error_t Afe44xx_SetUp(void)
{
	Error_t error = s_ERROR;
	uint32_t temp = 0;

	// AFE44XX Test --------------------------------------------------
	Afe44xx_ConfigHw();
	HAL_Delay(500);

	// Testing
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__LED2STC, 0x0A5A);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);
	temp = Afe44xx_ReadRegister(s_AFE44XX__LED2STC);

	if(temp == 0x0A5A) {
		error = s_OK;
	} else {
		return s_ERROR;
	}

	Afe44xx_Init();
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	// Turn Off LEDs
	temp = Afe44xx_ReadRegister(s_AFE44XX__LEDCNTRL);
	temp &= ~(0x00FFFF);
	temp |= 0x005050;
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__LEDCNTRL, temp);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	// Set Gain
	temp = Afe44xx_ReadRegister(s_AFE44XX__TIA_AMB_GAIN);
	temp &= ~(0x000007);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__TIA_AMB_GAIN, temp | 5);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	// 2nd Stage (1 - on, 0 - off)
	temp = Afe44xx_ReadRegister(s_AFE44XX__TIA_AMB_GAIN);
	temp &= ~(0x004000);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__TIA_AMB_GAIN, temp | (1<<14));
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	// 2nd stage DAC
	temp = Afe44xx_ReadRegister(s_AFE44XX__TIA_AMB_GAIN);
	temp &= ~(0x0F0000);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__TIA_AMB_GAIN, temp | (2<<16));
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	// 2nd Stage Gain
	temp = Afe44xx_ReadRegister(s_AFE44XX__TIA_AMB_GAIN);
	temp &= ~(0x000700);
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0000);
	Afe44xx_WriteRegister(s_AFE44XX__TIA_AMB_GAIN, temp | (2<<8));
	Afe44xx_WriteRegister(s_AFE44XX__CONTROL0, 0x0001);

	return error;
}




