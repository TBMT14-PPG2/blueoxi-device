/**
 * @file	ws2812b.h
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * WS2812B library header file.
 */

#ifndef __WS2812B_H
#define __WS2812B_H

/* -- Includes -- */

/* -- Defines -- */

// Display pinout
#define s_WS2812B__DATA_PORT		GPIOC
#define s_WS2812B__DATA				GPIO_PIN_2

#define s_WS2812B__DATA_SET()		s_WS2812B__DATA_PORT->BSRR = s_WS2812B__DATA
#define s_WS2812B__DATA_RESET()		s_WS2812B__DATA_PORT->BSRR = s_WS2812B__DATA << 16



#define s_WS2812B__T1H  5    // Width of a 1 bit in ns
#define s_WS2812B__T1L  0    // Width of a 1 bit in ns

#define s_WS2812B__T0H  2    // Width of a 0 bit in ns
#define s_WS2812B__T0L  3    // Width of a 0 bit in ns

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumurations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void WS2812B_Init(void);
void WS2812B_Deinit(void);

void WS2812B_Delay(volatile uint32_t Count);
void WS2812B_SendBit(uint8_t Bit);
void WS2812B_SendByte(uint8_t Byte);
void WS2812B_SendColor(uint8_t Red, uint8_t Green, uint8_t Blue);



#endif /* __WS2812B_H */
