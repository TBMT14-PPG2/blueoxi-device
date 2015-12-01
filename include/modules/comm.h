/**
 * @file	comm.h
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Communication library header file.
 */

#ifndef __COMM_H
#define __COMM_H

/* -- Includes -- */

/* -- Defines -- */

#define s_COMM__MAX_PACKET_SIZE			64

/* -- Constants -- */


/* -- Enumerations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void Comm_Init(void);
void Comm_Deinit(void);

void Comm_TxPacket(void);
void Comm_TxData(uint8_t *Data, uint8_t Size);



#endif /* __COMM_H */
