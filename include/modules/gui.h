/**
 * @file	gui.h
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * GUI header file.
 */

#ifndef __GUI_H
#define __GUI_H

/* -- Includes -- */

/* -- Defines -- */

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumerations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void Gui_Init(void);
void Gui_Deinit(void);

void Gui_UpdateValues(GraphicsObj_t *GraphicsObj, uint8_t Refresh, uint8_t Pulse, uint8_t Percentage, uint8_t SpO2);



#endif /* __GUI_H */
