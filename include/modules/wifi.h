/**
 * @file	wifi.h
 * @author  Eriks Zaharans
 * @date    27 Nov 2015
 *
 * @section DESCRIPTION
 *
 * WiFi library header file.
 */

#ifndef __WIFI_H
#define __WIFI_H

/* -- Includes -- */

/* -- Defines -- */
#define s_WIFI__BOOT_PORT			GPIOB
#define s_WIFI__BOOT_EN				GPIO_PIN_2
#define s_WIFI__BOOT_SET()			s_WIFI__BOOT_PORT->BSRR = s_WIFI__BOOT_EN
#define s_WIFI__BOOT_RESET()		s_WIFI__BOOT_PORT->BSRR = s_WIFI__BOOT_EN << 16



#define s_WIFI__CMD_EXIT			"+++"
#define s_WIFI__CMD_AT				"AT\r\n"
#define s_WIFI__CMD_CWMODE_CUR		"AT+CWMODE_CUR=2\r\n"
#define s_WIFI__CMD_CWSAP_CUR		"AT+CWSAP_CUR=\"blueoxi_wifi\",\"\",1,0\r\n"
#define s_WIFI__CMD_CWLIF			"AT+CWLIF\r\n"
#define s_WIFI__CMD_CIPSTART		"AT+CIPSTART=\"TCP\",\"192.168.4.2\",2222\r\n"
#define s_WIFI__CMD_CIPMODE			"AT+CIPMODE=1\r\n"
#define s_WIFI__CMD_CIPSEND			"AT+CIPSEND\r\n"

#define s_WIFI__CONFIG_CIFSR		"AT+CIFSR\r\n"




#define s_WIFI__CMD_COUNT			6


/* -- Enumerations -- */

/**
 * @brief Answer
 */
typedef enum s_WIFI_AT_ANSWER_ENUM {
	s_WIFI_AT_ANSWER__NULL = 0,
	s_WIFI_AT_ANSWER__NONE,
	s_WIFI_AT_ANSWER__OK,
	s_WIFI_AT_ANSWER__ERROR,
	s_WIFI_AT_ANSWER__CONNECTED,
	s_WIFI_AT_ANSWER__DISCONNECT
} WifiAtAnswer_t;

typedef enum s_WIFI_EVENT_ENUM {
	s_WIFI_EVENT__NULL = 0,
	s_WIFI_EVENT__NONE,
	s_WIFI_EVENT__STATION_CONNECTED,
	s_WIFI_EVENT__WAITING_DATA
} WifiEvent_t;


/* -- Constants -- */


/* -- Types -- */


/* -- Extern -- */
extern uint8_t				g_Wifi_UartTxReady;
extern CircularBuffer_t		g_Wifi_UartRxBuffer;
extern WifiAtAnswer_t		g_Wifi_AtAnswer;
extern WifiEvent_t			g_Wifi_Event;
extern uint8_t				g_Wifi_Ready;
extern UART_HandleTypeDef 	g_Wifi_UartHandle;


/* -- Function Prototypes -- */

void Wifi_Init(void);
void Wifi_InitExt(void);
void Wifi_Deinit(void);
void Wifi_ProcessRx(uint8_t Byte);
void Wifi_Process(void);
void Wifi_TxPacket(void);
uint8_t Wifi_ProcessConnect(void);

void Wifi_TxInit(void);
void Wifi_TxData(uint8_t *Data, uint8_t Size);


#endif /* __WIFI_H */
