/**
 * @file	wifi.c
 * @author  Eriks Zaharans
 * @date    27 Nov 2015
 *
 * @section DESCRIPTION
 *
 * WiFi library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Constants -- */
const uint8_t *const s_WIFI__CMD_LIST[] = {
		"AT+CIPMODE=1\r\n",
		"AT+CIPSTART=\"TCP\",\"192.168.4.2\",2222\r\n",
		"AT+CIPSEND\r\n"
};
const uint8_t s_WIFI__CMD_LENGTH[] = {
		sizeof("AT+CIPMODE=1\r\n")-1,
		sizeof("AT+CIPSTART=\"TCP\",\"192.168.4.2\",2222\r\n")-1,
		sizeof("AT+CIPSEND\r\n")-1
};

const WifiAtAnswer_t s_WIFI__CMD_ANSWER[] = {
		s_WIFI_AT_ANSWER__OK,
		s_WIFI_AT_ANSWER__CONNECTED,
		s_WIFI_AT_ANSWER__OK
};

const WifiEvent_t s_WIFI__CMD_EVENT[] = {
		s_WIFI_EVENT__NONE,
		s_WIFI_EVENT__NONE,
		s_WIFI_EVENT__NONE
};





const uint8_t *const s_WIFI__WAIT_LIST[] = {
		"AT\r\n",
		"AT+CWLIF\r\n",
};
const uint8_t s_WIFI__WAIT_LENGTH[] = {
		sizeof("AT\r\n")-1,
		sizeof("AT+CWLIF\r\n")-1,
};

const WifiAtAnswer_t s_WIFI__WAIT_ANSWER[] = {
		s_WIFI_AT_ANSWER__OK,
		s_WIFI_AT_ANSWER__OK,
};

const WifiEvent_t s_WIFI__WAIT_EVENT[] = {
		s_WIFI_EVENT__NONE,
		s_WIFI_EVENT__STATION_CONNECTED,
};



/* -- Variables -- */
uint8_t				g_Wifi_UartTxReady = 1;
CircularBuffer_t	g_Wifi_UartRxBuffer;
WifiAtAnswer_t		g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__NULL;
WifiEvent_t			g_Wifi_Event = s_WIFI_EVENT__NULL;
uint8_t				g_Wifi_Ready = 0;

volatile uint8_t 	g_Wifi_RxBuffer[256];
volatile uint8_t 	g_Wifi_RxBuffer2[256];
uint8_t 			*g_Wifi_RxBufferPtr;
uint8_t				g_Wifi_RxBufferSwitch = 0;

UART_HandleTypeDef g_Wifi_UartHandle;

/* -- Functions -- */

/**
 * Initialize WiFi
 * @param void No arguments
 * @return void No return
 */
void Wifi_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// Enable clocks
	__USART1_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();


	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// Configure GPIO
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Peripheral interrupt init
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	// Configure UART
	g_Wifi_UartHandle.Instance = USART1;
	g_Wifi_UartHandle.Init.BaudRate = 115200;
	g_Wifi_UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	g_Wifi_UartHandle.Init.StopBits = UART_STOPBITS_1;
	g_Wifi_UartHandle.Init.Parity = UART_PARITY_NONE;
	g_Wifi_UartHandle.Init.Mode = UART_MODE_TX_RX;
	g_Wifi_UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	g_Wifi_UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&g_Wifi_UartHandle);

	// Enable RX interrupt
	__HAL_UART_ENABLE_IT(&g_Wifi_UartHandle, UART_IT_RXNE);

	// Set normal boot
	s_WIFI__BOOT_SET();
}


void Wifi_InitExt(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// Enable clocks
	__USART1_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();


	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// Configure GPIO
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Set normal boot
	s_WIFI__BOOT_RESET();
}

/**
 * Deinitialize WiFi
 * @param void No arguments
 * @return void No return
 */
void Wifi_Deinit(void)
{
	__USART1_CLK_DISABLE();

	// USART6 GPIO Configuration
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

	// Peripheral interrupt Deinit
	HAL_NVIC_DisableIRQ(USART1_IRQn);
}

void Wifi_ProcessRx(uint8_t Byte)
{
	g_Wifi_UartRxBuffer.lock = 1;
	g_Wifi_UartRxBuffer.data[g_Wifi_UartRxBuffer.wrI] = Byte;
	g_Wifi_UartRxBuffer.wrI = (g_Wifi_UartRxBuffer.wrI + 1) % s_UTILITIES__BUFFER_SIZE;
	g_Wifi_UartRxBuffer.pendingBytes++;

	// Flag buffer overflow
	if (g_Wifi_UartRxBuffer.pendingBytes > s_UTILITIES__BUFFER_SIZE)
	{
		g_Wifi_UartRxBuffer.overflow = 1;
	}
	g_Wifi_UartRxBuffer.lock = 0;
}

void Wifi_Process(void)
{
	uint8_t byte;
	static uint8_t buffer[64], iBuf = 0;

	// Check for pending data
	if(g_Wifi_UartRxBuffer.lock == 0)
	{
		while(g_Wifi_UartRxBuffer.pendingBytes)
		{
			// Read byte
			byte = g_Wifi_UartRxBuffer.data[g_Wifi_UartRxBuffer.rdI];
			g_Wifi_UartRxBuffer.rdI = (g_Wifi_UartRxBuffer.rdI + 1) % s_UTILITIES__BUFFER_SIZE;
			g_Wifi_UartRxBuffer.pendingBytes--;

			// Save read bytes
			buffer[iBuf++] = byte;
			// Check if msg received
			if(byte == '\r') {

				// Answers
				if(strstr(buffer, "OK") != NULL) {
					g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__OK;
				}
				//				else if(strstr(buffer, "ERROR") != NULL) {
				//					g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__ERROR;
				//				}
				else if(strstr(buffer, "CONNECTED") != NULL) {
					g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__CONNECTED;
				}
				else {

				}


				// Events
				if(strstr(buffer, "192.168.4.2") != NULL) {
					g_Wifi_Event = s_WIFI_EVENT__STATION_CONNECTED;
				}
				else if(strstr(buffer, ">") != NULL) {
					g_Wifi_Event = s_WIFI_EVENT__WAITING_DATA;
				}
				else {

				}

				iBuf = 0;
			}
		}
	}


}



uint8_t Wifi_ProcessConnect(const uint8_t *const List[], const uint8_t Length[], const WifiAtAnswer_t Answer[],  const WifiEvent_t Event[], uint8_t Count)
{
	static uint8_t cnt = 0, waitAnswer = 0;
	static uint8_t buf[64];

	// Can send/packet sent
	if(cnt < Count)
	{
		if(g_Wifi_UartTxReady == 1)
		{
			// Waiting for answer?
			if(waitAnswer == 1)
			{
				// Check awaited answer
				if(g_Wifi_AtAnswer == Answer[cnt]) {
					// Check awaited event
					if(g_Wifi_Event == Event[cnt]) {
						g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__NULL;	// Reset
						g_Wifi_Event = s_WIFI_EVENT__NULL;
						waitAnswer = 0;
						cnt++;
					}
					// Check if event is required
					else if(Event[cnt] == s_WIFI_EVENT__NONE) {
						g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__NULL;	// Reset
						g_Wifi_Event = s_WIFI_EVENT__NULL;
						waitAnswer = 0;
						cnt++;
					}
					// If no-event received although required -> re-send
					else {
						HAL_Delay(1000);
						g_Wifi_AtAnswer = s_WIFI_AT_ANSWER__NULL;	// Reset
						g_Wifi_Event = s_WIFI_EVENT__NULL;
						waitAnswer = 0;
					}
				}
				// Check if answer is required
				else if(Answer[cnt] == s_WIFI_AT_ANSWER__NONE) {
					HAL_Delay(1000);
					waitAnswer = 0;
					cnt++;
				}
				// If non-null answer was received, probably error
				else if(g_Wifi_AtAnswer != s_WIFI_AT_ANSWER__NULL) {
					// Re-send
					HAL_Delay(1000);
					waitAnswer = 0;
				}
			}
			else
			{
				// Send
				g_Wifi_UartTxReady = 0;
				memcpy(buf, List[cnt], Length[cnt]);
				HAL_UART_Transmit_IT(&g_Wifi_UartHandle, buf, Length[cnt]);
				waitAnswer = 1;
			}
		}

		return 1;
	}
	else {
		cnt = 0;
		waitAnswer = 0;

		return 0;
	}
}


void Wifi_TxPacket(void)
{
	static uint16_t cnt = 0;
	uint8_t i, byteCnt, lrc = 0;
	uint8_t packet[512+6];

	// Prepare header
	packet[0] = 0xA5;
	packet[1] = 0x21;
	packet[2] = 0x00;
	packet[3] = 200;
	packet[4] = ((packet[0]+packet[1]+packet[2]+packet[3])^0xFF)+1;

	byteCnt = 5;
	for(i = 0; i < (packet[3]/2); i++)
	{
		packet[byteCnt] = cnt & 0xFF;
		lrc += packet[byteCnt++];
		packet[byteCnt] = (cnt >> 8) & 0xFF;
		lrc += packet[byteCnt++];
		cnt++;
	}

	packet[byteCnt++] = (lrc^0xFF)+1;

	HAL_UART_Transmit_IT(&g_Wifi_UartHandle, packet, byteCnt);
}


void Wifi_TxInit(void)
{
	// Prepare header
	// Init first buffer
	g_Wifi_RxBuffer[0] = 0xA5;
	g_Wifi_RxBuffer[1] = 0x21;
	g_Wifi_RxBuffer[2] = 0x00;
	g_Wifi_RxBuffer[3] = 200;
	g_Wifi_RxBuffer[4] = ((g_Wifi_RxBuffer[0]+g_Wifi_RxBuffer[1]+g_Wifi_RxBuffer[2]+g_Wifi_RxBuffer[3])^0xFF)+1;

	// Init second buffer
	g_Wifi_RxBuffer2[0] = 0xA5;
	g_Wifi_RxBuffer2[1] = 0x21;
	g_Wifi_RxBuffer2[2] = 0x00;
	g_Wifi_RxBuffer2[3] = 200;
	g_Wifi_RxBuffer2[4] = ((g_Wifi_RxBuffer[0]+g_Wifi_RxBuffer[1]+g_Wifi_RxBuffer[2]+g_Wifi_RxBuffer[3])^0xFF)+1;

	// Set buffer
	g_Wifi_RxBufferPtr = g_Wifi_RxBuffer;
}

void Wifi_TxData(uint8_t *Data, uint8_t Size)
{
	static uint8_t lrc = 0;
	static uint8_t cnt = 5;
	uint8_t i;

	for (i = 0; i < Size; i++) {
		lrc += Data[i];
		g_Wifi_RxBufferPtr[cnt++] = Data[i];
	}

	if(cnt == (200+5)) {
		lrc = (lrc^0xFF)+1;
		g_Wifi_RxBufferPtr[cnt++] = lrc;
		HAL_UART_Transmit_IT(&g_Wifi_UartHandle, g_Wifi_RxBufferPtr, cnt);

		if(g_Wifi_RxBufferSwitch == 0) {
			g_Wifi_RxBufferPtr = g_Wifi_RxBuffer;
			g_Wifi_RxBufferSwitch = 1;
		}
		else {
			g_Wifi_RxBufferPtr = g_Wifi_RxBuffer2;
			g_Wifi_RxBufferSwitch = 0;
		}

		lrc = 0;
		cnt = 5;
	}
}


void Wifi_Simple(void)
{



}


uint8_t Wifi_Connect(void)
{
	return Wifi_ProcessConnect(s_WIFI__CMD_LIST, s_WIFI__CMD_LENGTH, s_WIFI__CMD_ANSWER, s_WIFI__CMD_EVENT, s_WIFI__CMD_COUNT);
}

uint8_t Wifi_Wait(void)
{
	return Wifi_ProcessConnect(s_WIFI__WAIT_LIST, s_WIFI__WAIT_LENGTH, s_WIFI__WAIT_ANSWER, s_WIFI__WAIT_EVENT, s_WIFI__WAIT_COUNT);
}






