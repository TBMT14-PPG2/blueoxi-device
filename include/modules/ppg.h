/**
 * @file	ppg.h
 * @author  Eriks Zaharans
 * @date    27 Nov 2015
 *
 * @section DESCRIPTION
 *
 * PPG library header file.
 */

#ifndef __PPG_H
#define __PPG_H

/* -- Includes -- */

/* -- Defines -- */

/* -- Constants -- */

/* -- Enumerations -- */

/* -- Types -- */

/* -- Extern -- */
extern uint16_t g_Ppg_Pulse;
extern uint8_t g_Ppg_MaxPulsePercent;


/* -- Function Prototypes -- */

void Ppg_Init(void);
void Ppg_Deinit(void);
void PPG_Filter(uint16_t *Input, uint16_t *Output);
void PPG_CalcPulse(uint16_t Time);

void PPG_BufferSignal(uint16_t RedData, uint16_t IrData);



#endif /* __PPG_H */
