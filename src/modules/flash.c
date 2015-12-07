/**
 * @file	flash.c
 * @author  Eriks & Janis Zaharans
 * @date    24 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Flash memory library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */
SPI_HandleTypeDef	g_Flash_SpiHandle;

/* -- Functions -- */

/**
 * Initialize Communication
 * @param void No arguments
 * @return void No return
 */
void Flash_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__SPI2_CLK_ENABLE();

	// Configure NSS
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// Configure SPI GPIO
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// Configure SPI
	g_Flash_SpiHandle.Instance = SPI2;
	g_Flash_SpiHandle.Init.Mode = SPI_MODE_MASTER;
	g_Flash_SpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
	g_Flash_SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	g_Flash_SpiHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
	g_Flash_SpiHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	g_Flash_SpiHandle.Init.NSS = SPI_NSS_SOFT;
	g_Flash_SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	g_Flash_SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	g_Flash_SpiHandle.Init.TIMode = SPI_TIMODE_DISABLED;
	g_Flash_SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	g_Flash_SpiHandle.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&g_Flash_SpiHandle);
}

/**
 * Deinitialize Communication
 * @param void No arguments
 * @return void No return
 */
void Flash_Deinit(void)
{

}



void Flash_Command(uint8_t Cmd)
{
	s_FLASH__SELECT();

	HAL_SPI_Transmit(&g_Flash_SpiHandle, &Cmd, 1, 100);

	s_FLASH__DESELECT();
}


void Flash_WaitBusy(void)
{
	uint8_t cmd, data;

	s_FLASH__SELECT();

	cmd = s_FLASH__CMD_RD_STATUS_REG1;

	HAL_SPI_Transmit(&g_Flash_SpiHandle, &cmd, 1, 1000);
	HAL_SPI_Receive(&g_Flash_SpiHandle, &data, 1, 1000);
	while(data & s_FLASH__STATUS_REG1_BUSY)
	{
		HAL_SPI_Receive(&g_Flash_SpiHandle, &data, 1, 1000);
	}

	s_FLASH__DESELECT();
}


void Flash_Program(uint32_t Addr, uint8_t *Data, uint16_t Size)
{
	uint8_t cmd[4];
	uint8_t i;

	//Check if Erase/Program in progress
	Flash_WaitBusy();

	// Enable write
	Flash_Command(s_FLASH__CMD_WR_ENABLE);

	s_FLASH__SELECT();

	// Prepare command
	cmd[0] = s_FLASH__CMD_PAGE_PROGRAM;
	cmd[1] = (uint8_t)((Addr>>16) & 0xFF);
	cmd[2] = (uint8_t)((Addr>>8) & 0xFF);
	cmd[3] = (uint8_t)(Addr & 0xFF);

	// Send 'Program Page' instruction and address
	HAL_SPI_Transmit(&g_Flash_SpiHandle, cmd, 4, 1000);

	// Send data
	HAL_SPI_Transmit(&g_Flash_SpiHandle, Data, Size, 1000);

	s_FLASH__DESELECT();
}


void Flash_Read(uint32_t Addr, uint8_t *Data, uint16_t Size)
{
	uint8_t cmd[4];
	uint8_t i;

	//Check if Erase/Program in progress
	Flash_WaitBusy();

	s_FLASH__SELECT();

	// Prepare command
	cmd[0] = s_FLASH__CMD_RD_DATA;
	cmd[1] = (uint8_t)((Addr>>16) & 0xFF);
	cmd[2] = (uint8_t)((Addr>>8) & 0xFF);
	cmd[3] = (uint8_t)(Addr & 0xFF);

	// Send 'Read Data' instruction and address
	HAL_SPI_Transmit(&g_Flash_SpiHandle, cmd, 4, 1000);

	// Read Data
	HAL_SPI_Receive(&g_Flash_SpiHandle, Data, Size, 1000);

	s_FLASH__DESELECT();
}


void Flash_EraseSector(uint16_t Sector)
{
	uint32_t addr;
	uint8_t cmd[4];

	//Check if Erase/Program in progress
	Flash_WaitBusy();

	// Enable write
	Flash_Command(s_FLASH__CMD_WR_ENABLE);

	s_FLASH__SELECT();

	if(Sector < 16) {	// 4 kB sector
		addr = Sector << 12;
		cmd[0] = s_FLASH__CMD_SECTOR_ERASE_4KB;
		cmd[1] = (uint8_t)((addr>>16) & 0xFF);
		cmd[2] = (uint8_t)((addr>>8) & 0xFF);
		cmd[3] = (uint8_t)(addr & 0xFF);
	}
	else {				// 64 kB sector
		addr = s_FLASH__PARAMETER_BLOCK_SIZE + ((Sector-16) << 16);
		cmd[0] = s_FLASH__CMD_SECTOR_ERASE_64KB;
		cmd[1] = (uint8_t)((addr>>16) & 0xFF);
		cmd[2] = (uint8_t)((addr>>8) & 0xFF);
		cmd[3] = (uint8_t)(addr & 0xFF);
	}

	// Send command
	HAL_SPI_Transmit(&g_Flash_SpiHandle, cmd, 4, 1000);

	s_FLASH__DESELECT();
}

void Flash_EraseChip(void)
{
	//Check if Erase/Program in progress
	Flash_WaitBusy();

	// Enable write
	Flash_Command(s_FLASH__CMD_WR_ENABLE);

	// Enable write
	Flash_Command(s_FLASH__CMD_CHIP_ERASE);
}


void Flash_ReadInfo(FlashInfo_t *Info)
{
	uint8_t i;
	uint8_t cmd[4];
	uint8_t data[2];

	// Read Manufacturer ID and Device ID
	s_FLASH__SELECT();

	cmd[0] = s_FLASH__CMD_MANUF_DEV_ID;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;

	HAL_SPI_Transmit(&g_Flash_SpiHandle, cmd, 4, 1000);
	HAL_SPI_Receive(&g_Flash_SpiHandle, data, 2, 1000);

	Info->manufacturer_id = data[0];
	Info->dev_id = data[1];

	s_FLASH__DESELECT();
}

