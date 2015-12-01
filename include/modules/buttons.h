/**
 * @file	buttons.h
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Buttons library header file.
 */

#ifndef __BUTTONS_H
#define __BUTTONS_H

/* -- Includes -- */

/* -- Defines -- */

// Display pinout
#define s_BUTTONS__BTN_A_PORT	GPIOA
#define s_BUTTONS__BTN1			GPIO_PIN_0
#define s_BUTTONS__BTN4			GPIO_PIN_1

#define s_BUTTONS__BTN_B_PORT	GPIOB
#define s_BUTTONS__BTN3			GPIO_PIN_10

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumurations -- */

/* -- Types -- */

/* -- Extern -- */
extern uint8_t g_Buttons_Event;


/* -- Function Prototypes -- */

void Buttons_Init(void);
void Buttons_Deinit(void);


#endif /* __BUTTONS_H */
