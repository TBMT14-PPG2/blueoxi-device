/**
 * @file	comm.c
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Communication library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */
#define s_COMM__DATA_SAMPLES		16
#define s_COMM__BYTES_PER_SAMPLE	2
#define s_COMM__DATA_BYTES			(s_COMM__DATA_SAMPLES * s_COMM__BYTES_PER_SAMPLE)

/* -- Variables -- */
volatile uint8_t g_Comm_RxBuffer[64];

/* -- Functions -- */

/**
 * Initialize Communication
 * @param void No arguments
 * @return void No return
 */
void Comm_Init(void)
{
	// Prepare header
	g_Comm_RxBuffer[0] = 0xA5;
	g_Comm_RxBuffer[1] = 0x21;
	g_Comm_RxBuffer[2] = 0x00;
	g_Comm_RxBuffer[3] = s_COMM__DATA_BYTES;
	g_Comm_RxBuffer[4] = ((g_Comm_RxBuffer[0]+g_Comm_RxBuffer[1]+g_Comm_RxBuffer[2]+g_Comm_RxBuffer[3])^0xFF)+1;
}

/**
 * Deinitialize Communication
 * @param void No arguments
 * @return void No return
 */
void Comm_Deinit(void)
{

}


void Comm_TxPacket(void)
{
	static uint16_t cnt = 0;
	uint8_t i, byteCnt, lrc = 0;
	uint8_t packet[s_COMM__MAX_PACKET_SIZE];

	// Prepare header
	packet[0] = 0xA5;
	packet[1] = 0x21;
	packet[2] = 0x00;
	packet[3] = 32;
	packet[4] = ((packet[0]+packet[1]+packet[2]+packet[3])^0xFF)+1;

	byteCnt = 5;
	for(i = 0; i < 29; i++)
	{
		packet[byteCnt] = cnt & 0xFF;
		lrc += packet[byteCnt++];
		packet[byteCnt] = (cnt >> 8) & 0xFF;
		lrc += packet[byteCnt++];
		cnt++;
	}

	packet[byteCnt++] = (lrc^0xFF)+1;

	// USB Transmit
	CDC_Transmit_FS(packet, byteCnt);

}



void Comm_TxData(uint8_t *Data, uint8_t Size)
{
	static uint8_t lrc = 0;
	static uint8_t cnt = 5;
	uint8_t i;

	for (i = 0; i < Size; i++) {
		lrc += Data[i];
		g_Comm_RxBuffer[cnt++] = Data[i];
	}

	if(cnt == (s_COMM__DATA_BYTES+5)) {
		lrc = (lrc^0xFF)+1;
		g_Comm_RxBuffer[cnt++] = lrc;
		CDC_Transmit_FS(g_Comm_RxBuffer, cnt);

		lrc = 0;
		cnt = 5;
	}
}



