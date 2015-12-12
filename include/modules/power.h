/**
 * @file	power.h
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Power Supply library header file.
 */

#ifndef __POWER_H
#define __POWER_H

/* -- Includes -- */

/* -- Defines -- */

#define s_POWER__PORTB					GPIOB
#define s_POWER__PORTC					GPIOC

#define s_POWER__LCD_EN_PORT			GPIOB
#define s_POWER__LCD_EN					GPIO_PIN_3
#define s_POWER__LCD_EN_SET()			s_POWER__LCD_EN_PORT->BSRR = s_POWER__LCD_EN
#define s_POWER__LCD_EN_RESET()			s_POWER__LCD_EN_PORT->BSRR = s_POWER__LCD_EN << 16

#define s_POWER__BLE_MEMS_EN_PORT		GPIOB
#define s_POWER__BLE_MEMS_EN			GPIO_PIN_6
#define s_POWER__BLE_MEMS_EN_SET()		s_POWER__BLE_MEMS_EN_PORT->BSRR = s_POWER__BLE_MEMS_EN
#define s_POWER__BLE_MEMS_EN_RESET()	s_POWER__BLE_MEMS_EN_PORT->BSRR = s_POWER__BLE_MEMS_EN << 16

#define s_POWER__WIFI_EN_PORT			GPIOC
#define s_POWER__WIFI_EN				GPIO_PIN_9
#define s_POWER__WIFI_EN_SET()			s_POWER__WIFI_EN_PORT->BSRR = s_POWER__WIFI_EN
#define s_POWER__WIFI_EN_RESET()		s_POWER__WIFI_EN_PORT->BSRR = s_POWER__WIFI_EN << 16

#define s_POWER__GPS_EN_PORT			GPIOC
#define s_POWER__GPS_EN					GPIO_PIN_3
#define s_POWER__GPS_EN_SET()			s_POWER__GPS_EN_PORT->BSRR = s_POWER__GPS_EN
#define s_POWER__GPS_EN_RESET()			s_POWER__GPS_EN_PORT->BSRR = s_POWER__GPS_EN << 16

#define s_POWER__PPG_EN_PORT			GPIOB
#define s_POWER__PPG_EN					GPIO_PIN_1
#define s_POWER__PPG_EN_SET()			s_POWER__PPG_EN_PORT->BSRR = s_POWER__PPG_EN
#define s_POWER__PPG_EN_RESET()			s_POWER__PPG_EN_PORT->BSRR = s_POWER__PPG_EN << 16

#define s_POWER__BAT_LVL_EN_PORT		GPIOC
#define s_POWER__BAT_LVL_EN				GPIO_PIN_13
#define s_POWER__BAT_LVL_EN_SET()		s_POWER__BAT_LVL_EN_PORT->BSRR = s_POWER__BAT_LVL_EN
#define s_POWER__BAT_LVL_EN_RESET()		s_POWER__BAT_LVL_EN_PORT->BSRR = s_POWER__BAT_LVL_EN << 16

#define s_POWER__BAT_LVL_PORT			GPIOC
#define s_POWER__BAT_LVL				GPIO_PIN_0

#define s_POWER__CHARGE_STAT_PORT		GPIOB
#define s_POWER__CHARGE_STAT			GPIO_PIN_7
#define s_POWER__CHARGE_STAT_ISSET()	((s_POWER__CHARGE_STAT_PORT->IDR & s_POWER__CHARGE_STAT) != (uint32_t)GPIO_PIN_RESET)

/* -- Constants -- */

/* -- Enumerations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void Power_Init(void);
void Power_Deinit(void);

uint32_t Power_BateryLevel(void);



#endif /* __POWER_H */
