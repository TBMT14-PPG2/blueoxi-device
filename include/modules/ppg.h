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
extern uint16_t g_Ppg_SpO2;


/* -- Function Prototypes -- */

void Ppg_Init(void);
void Ppg_Deinit(void);
void Ppg_Filter(uint16_t *Input, uint16_t *Output);
uint16_t Ppg_DetectPeak(uint16_t Input);
void Ppg_CalcPulse(uint16_t Time);
void Ppg_CalcSat(void);
void Ppg_BufferSignal(uint16_t RedData, uint16_t IrData);



#endif /* __PPG_H */
