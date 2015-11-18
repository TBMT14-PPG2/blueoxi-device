/**
 * @file	ble.h
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * BLE library header file.
 */

#ifndef __BLE_H
#define __BLE_H

/* -- Includes -- */

/* -- Defines -- */

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumerations -- */

/* -- Types -- */

/* -- Extern -- */
extern uint8_t				g_Ble_UartTxReady;
extern CircularBuffer_t		g_Ble_UartRxBuffer;
extern UART_HandleTypeDef 	g_Ble_UartHandle;

/* -- Function Prototypes -- */

void Ble_Init(void);
void Ble_Deinit(void);

void Ble_ProcessRx(uint8_t Byte);
void Ble_Process(void);



#endif /* __POWER_H */
