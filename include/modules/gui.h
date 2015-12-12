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
/**
 * @brief GUI Display Options
 */
typedef enum s_GUI_DISPLAY_OPTIONS_ENUM {
	s_GUI_DISPLAY_OPT__NOTHING = 0,
	s_GUI_DISPLAY_OPT__CLEAR,
	s_GUI_DISPLAY_OPT__CLEAR_DISPLAY,
	s_GUI_DISPLAY_OPT__DISPLAY
} GuiDisplayOpt_t;

/**
 * @brief GUI Button Prompt
 */
typedef enum s_GUI_BUTTONS_ENUM {
	s_GUI_BUTTONS__TOP = 0,
	s_GUI_BUTTONS__MID,
	s_GUI_BUTTONS__BOT
} GuiButtons_t;

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void Gui_Init(void);
void Gui_Deinit(void);

void Gui_UpdateValues(GraphicsObj_t *GraphicsObj, uint8_t Refresh, uint8_t Pulse, uint8_t Percentage, uint8_t SpO2);

void Gui_DisplayMenu(GraphicsObj_t *GraphicsObj, uint32_t Battery, uint8_t ChargingStatus);
void Gui_DisplayCenterString(GraphicsObj_t *GraphicsObj, const uint8_t *String, uint8_t Lines, uint8_t Line, GuiDisplayOpt_t Opt);
void Gui_DisplayButtonPrompt(GraphicsObj_t *GraphicsObj, const uint8_t *String, GuiButtons_t Button, GuiDisplayOpt_t Opt);

#endif /* __GUI_H */
