/**
 * @file	motor.h
 * @author  Eriks Zaharans
 * @date    6 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Vibration motor library header file.
 */

#ifndef __MOTOR_H
#define __MOTOR_H

/* -- Includes -- */

/* -- Defines -- */

// Display pinout
#define s_MOTOR__DRIVE_PORT			GPIOB
#define s_MOTOR__DRIVE				GPIO_PIN_4

#define s_MOTOR__DRIVE_SET()		s_MOTOR__DRIVE_PORT->BSRR = s_MOTOR__DRIVE
#define s_MOTOR__DRIVE_RESET()		s_MOTOR__DRIVE_PORT->BSRR = s_MOTOR__DRIVE << 16

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumurations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void Motor_Init(void);
void Motor_Deinit(void);



#endif /* __MOTOR_H */
