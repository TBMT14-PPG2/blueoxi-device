/**
 * @file	afe44xx.h
 * @author  Eriks & Janis Zaharans
 * @date    25 Nov 2015
 *
 * @section DESCRIPTION
 *
 * AFE44XX PPG Front-End library header file.
 */

#ifndef __AFE44XX_H
#define __AFE44XX_H

/* -- Includes -- */

/* -- Defines -- */

// STE
#define s_AFE44XX__STE_PORT			GPIOA
#define s_AFE44XX__STE				GPIO_PIN_4
#define s_AFE44XX__STE_SET()		s_AFE44XX__STE_PORT->BSRR = s_AFE44XX__STE
#define s_AFE44XX__STE_RESET()		s_AFE44XX__STE_PORT->BSRR = s_AFE44XX__STE << 16

#define s_AFE44XX__DESELECT()		s_AFE44XX__STE_SET()
#define s_AFE44XX__SELECT()			s_AFE44XX__STE_RESET()

// PDN
#define s_AFE44XX__PDN_PORT			GPIOC
#define s_AFE44XX__PDN				GPIO_PIN_5
#define s_AFE44XX__PDN_SET()		s_AFE44XX__PDN_PORT->BSRR = s_AFE44XX__PDN
#define s_AFE44XX__PDN_RESET()		s_AFE44XX__PDN_PORT->BSRR = s_AFE44XX__PDN << 16

#define s_AFE44XX__ON()				s_AFE44XX__PDN_SET()
#define s_AFE44XX__OFF()			s_AFE44XX__PDN_RESET()

// RST
#define s_AFE44XX__RST_PORT			GPIOB
#define s_AFE44XX__RST				GPIO_PIN_0
#define s_AFE44XX__RST_SET()		s_AFE44XX__RST_PORT->BSRR = s_AFE44XX__RST
#define s_AFE44XX__RST_RESET()		s_AFE44XX__RST_PORT->BSRR = s_AFE44XX__RST << 16

#define s_AFE44XX__RST_OFF()		s_AFE44XX__RST_SET()
#define s_AFE44XX__RST_ACTIVE()		s_AFE44XX__RST_RESET()

// ADC_RDY
#define s_AFE44XX__ADC_RDY_PORT			GPIOC
#define s_AFE44XX__ADC_RDY				GPIO_PIN_4



// Registers
#define s_AFE44XX__CONTROL0			0x00		// Control Register 0
#define s_AFE44XX__LED2STC			0x01		// Sample LED2 Start Count Register
#define s_AFE44XX__LED2ENDC			0x02		// Sample LED2 End Count Register
#define s_AFE44XX__LED2LEDSTC		0x03		// LED2 LED Start Count Register
#define s_AFE44XX__LED2LEDENDC		0x04		// LED2 LED End Count Register
#define s_AFE44XX__ALED2STC			0x05		// Sample Ambient LED2 Start Count Register
#define s_AFE44XX__ALED2ENDC		0x06		// Sample Ambient LED2 End Count Register
#define s_AFE44XX__LED1STC			0x07		// Sample LED1 Start Count Register
#define s_AFE44XX__LED1ENDC			0x08		// Sample LED1 End Count Register
#define s_AFE44XX__LED1LEDSTC		0x09		// LED1 LED Start Count Register
#define s_AFE44XX__LED1LEDENDC		0x0A		// LED1 LED End Count Register
#define s_AFE44XX__ALED1STC			0x0B		// Sample Ambient LED1 Start Count Register
#define s_AFE44XX__ALED1ENDC		0x0C		// Sample Ambient LED1 End Coutn Register
#define s_AFE44XX__LED2CONVST		0x0D		// LED2 Convert Start Count Register
#define s_AFE44XX__LED2CONVEND		0x0E		// LED2 Convert End Count Register
#define s_AFE44XX__ALED2CONVST		0x0F		// LED2 Ambient Convert Start Count Register
#define s_AFE44XX__ALED2CONVEND		0x10		// LED2 Ambient Convert End Count Register
#define s_AFE44XX__LED1CONVST		0x11		// LED1 Convert Start Count Register
#define s_AFE44XX__LED1CONVEND		0x12		// LED1 Convert End Count Register
#define s_AFE44XX__ALED1CONVST		0x13		// LED1 Ambient Convert Start Count Register
#define s_AFE44XX__ALED1CONVEND		0x14		// LED1 Ambient Convert End Count Register
#define s_AFE44XX__ADCRSTSTCT0		0x15		// ADC Reset 0 Start Count Register
#define s_AFE44XX__ADCRSTENDCT0		0x16		// ADC Reset 0 End Count Register
#define s_AFE44XX__ADCRSTSTCT1		0x17		// ADC Reset 1 Start Count Register
#define s_AFE44XX__ADCRSTENDCT1		0x18		// ADC Reset 1 End Count Register
#define s_AFE44XX__ADCRSTSTCT2		0x19		// ADC Reset 2 Start Count Register
#define s_AFE44XX__ADCRSTENDCT2		0x1A		// ADC Reset 2 End Count Register
#define s_AFE44XX__ADCRSTSTCT3		0x1B		// ADC Reset 3 Start Count Register
#define s_AFE44XX__ADCRSTENDCT3		0x1C		// ADC Reset 3 End Count Register
#define s_AFE44XX__PRPCOUNT			0x1D		// Pulse Repetition Period Count Register
#define s_AFE44XX__CONTROL1			0x1E		// Control Register 1
#define s_AFE44XX__SPARE1			0x1F		// SPARE1 Register (Reserved)
#define s_AFE44XX__TIAGAIN			0x20		// Transimpedance Amplifier Gain Setting Register
#define s_AFE44XX__TIA_AMB_GAIN		0x21		// Transimpedance Amplifier and Ambient Cancellation Stage Gain Register
#define s_AFE44XX__LEDCNTRL			0x22		// LED Control Register
#define s_AFE44XX__CONTROL2			0x23		// Control Register 2
#define s_AFE44XX__SPARE2			0x24		// SPARE2 Register (Reserved)
#define s_AFE44XX__SPARE3			0x25		// SPARE3 Register (Reserved)
#define s_AFE44XX__SPARE4			0x26		// SPARE4 Register (Reserved)
#define s_AFE44XX__RESERVED1		0x27		// RESERVED1 Register (Reserved)
#define s_AFE44XX__RESERVED2		0x28		// RESERVED2 Register (Reserved)
#define s_AFE44XX__ALARM			0x29		// Alarm Register
#define s_AFE44XX__LED2VAL			0x2A		// LED2 Digital Sample Value Register
#define s_AFE44XX__ALED2VAL			0x2B		// Ambient LED2 Digital Sample Value Register
#define s_AFE44XX__LED1VAL			0x2C		// LED1 Digital Sample Value Register
#define s_AFE44XX__ALED1VAL			0x2D		// Ambient LED1 Digital Sample Value Register
#define s_AFE44XX__LED2_ALED2VAL	0x2E		// LED2-Ambient LED2 Digital Sample Value Register
#define s_AFE44XX__LED1_ALED1VAL	0x2F		// LED1-Ambient LED1 Digital Sample Value Register
#define s_AFE44XX__DIAG				0x30		// Diagnostics Flag Register


/* --- Externs --- */
extern volatile uint8_t g_Afe44xx_AdcRdy;


/* --- Function Prototypes --- */
void Afe44xx_ConfigHw(void);
void Afe44xx_Init(void);
void Afe44xx_Reset(void);

uint32_t Afe44xx_ReadRegister(uint8_t Addr);
void Afe44xx_WriteRegister(uint8_t Addr, uint32_t Data);


#endif
