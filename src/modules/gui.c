/**
 * @file	gui.c
 * @author  Eriks Zaharans
 * @date    13 Nov 2015
 *
 * @section DESCRIPTION
 *
 * GUI library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */

/* -- Functions -- */

/**
 * Initialize GUI
 * @param void No arguments
 * @return void No return
 */
void Gui_Init(void)
{

}

/**
 * Deinitialize GUI
 * @param void No arguments
 * @return void No return
 */
void Gui_Deinit(void)
{

}

void Gui_SetAge(GraphicsObj_t *GraphicsObj, uint8_t age)
{
	uint8_t str[32];
	sprintf(str, "%d", (int)age);
	Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);
	Graphics_FillRect(GraphicsObj, 0, 97, s_GRAPHICS__LCD_WIDTH, 50, s_GRAPHICS_COLOR__WHITE);
	Graphics_DrawText(GraphicsObj, 0, 97, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
}

void Gui_UpdateValues(GraphicsObj_t *GraphicsObj, uint8_t Refresh, uint8_t Pulse, uint8_t Percentage, uint8_t SpO2)
{
	uint8_t str[32];

	if(Refresh == 0)
	{
		Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);
		Graphics_FillRect(GraphicsObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);

		Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)"blueoxi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
		sprintf(str, "%d", (int)Pulse);
		Graphics_DrawText(GraphicsObj, 90, 51, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
		sprintf(str, "%d", (int)Percentage);
		Graphics_DrawText(GraphicsObj, 90, 90, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
		sprintf(str, "%d", (int)SpO2);
		Graphics_DrawText(GraphicsObj, 90, 129, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawText(GraphicsObj, s_GRAPHICS__LCD_WIDTH-75, 53, (uint8_t *)"% HR", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawText(GraphicsObj, s_GRAPHICS__LCD_WIDTH-75, 92, (uint8_t *)"BPM", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawText(GraphicsObj, s_GRAPHICS__LCD_WIDTH-75, 131, (uint8_t *)"% SpO2", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	}
	else
	{
		Graphics_FillRect(GraphicsObj, 0, 51, s_GRAPHICS__LCD_WIDTH-76, 100, s_GRAPHICS_COLOR__WHITE);
		sprintf(str, "%d", (int)Pulse);
		Graphics_DrawText(GraphicsObj, 90, 51, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
		sprintf(str, "%d", (int)Percentage);
		Graphics_DrawText(GraphicsObj, 90, 90, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
		sprintf(str, "%d", (int)SpO2);
		Graphics_DrawText(GraphicsObj, 90, 129, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	}
}

void Gui_EndScreen(GraphicsObj_t *GraphicsObj, uint8_t MeanPulse, uint8_t MeanSpO2)
{
	uint8_t str[32];

	Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);
	Graphics_FillRect(GraphicsObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);

	Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)"blueoxi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
	Graphics_DrawText(GraphicsObj, 0, 50, (uint8_t *)"Mean HR", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 0, 106, (uint8_t *)"Mean SpO2", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	sprintf(str, "%d", (int)MeanPulse);
	Graphics_DrawText(GraphicsObj, 80, 73, str, appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	sprintf(str, "%d", (int)MeanSpO2);
	Graphics_DrawText(GraphicsObj, 80, 129, str , appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, s_GRAPHICS__LCD_WIDTH-55, 75, (uint8_t *)"BPM", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, s_GRAPHICS__LCD_WIDTH-55, 136, (uint8_t *)"%", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);

}







void Gui_DisplayMenu(GraphicsObj_t *GraphicsObj, uint32_t Battery, uint8_t ChargingStatus)
{
	uint8_t str[32];

	Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);

	// Display Battery level
	if(ChargingStatus == 0) {
		sprintf(str, "%d%%", Battery);
	} else {
		sprintf(str, "C %d%%", Battery);
	}
	Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)str, appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);

	// Display menu
	Graphics_DrawText(GraphicsObj, 30, 34, (uint8_t *)"WiFi Stream", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 76, (uint8_t *)"USB Stream", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 118, (uint8_t *)"SpO2 + BLE", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);

	// Display underlines
	// Top
	Graphics_DrawLine(GraphicsObj, 0, 52, 118, 52, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 52, 143, 0, s_GRAPHICS_COLOR__BLACK);
	// Mid
	Graphics_DrawLine(GraphicsObj, 0, 94, 118, 94, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 94, 143, 94, s_GRAPHICS_COLOR__BLACK);
	// Bottom
	Graphics_DrawLine(GraphicsObj, 0, 136, 118, 136, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 136, 143, 167, s_GRAPHICS_COLOR__BLACK);

	SharpLcd_DisplayBuffer(GraphicsObj->pBuf);
}

void Gui_DisplayCenterString(GraphicsObj_t *GraphicsObj, const uint8_t *String, uint8_t Lines, uint8_t Line, GuiDisplayOpt_t Opt)
{
	uint8_t h;

	h = (20 * (Lines-1)) / 2;

	if(Opt == s_GUI_DISPLAY_OPT__CLEAR_DISPLAY || Opt == s_GUI_DISPLAY_OPT__CLEAR) {
		Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);
	}

	Graphics_DrawText(GraphicsObj, 0, 76-h+(20*(Line-1)), String, appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);

	if(Opt == s_GUI_DISPLAY_OPT__CLEAR_DISPLAY || Opt == s_GUI_DISPLAY_OPT__DISPLAY) {
		SharpLcd_DisplayBuffer(GraphicsObj->pBuf);
	}
}

void Gui_DisplayButtonPrompt(GraphicsObj_t *GraphicsObj, const uint8_t *String, GuiButtons_t Button, GuiDisplayOpt_t Opt)
{

	if(Opt == s_GUI_DISPLAY_OPT__CLEAR_DISPLAY || Opt == s_GUI_DISPLAY_OPT__CLEAR) {
		Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);
	}

	// Draw Text
	Graphics_DrawText(GraphicsObj, 0, 76, String, appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	// Draw Line
	switch(Button)
	{
	case s_GUI_BUTTONS__TOP :
		// Top
		Graphics_DrawLine(GraphicsObj, 0, 94, 118, 94, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawLine(GraphicsObj, 118, 94, 143, 0, s_GRAPHICS_COLOR__BLACK);
		break;
	case s_GUI_BUTTONS__MID :
		// Mid
		Graphics_DrawLine(GraphicsObj, 0, 94, 118, 94, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawLine(GraphicsObj, 118, 94, 143, 94, s_GRAPHICS_COLOR__BLACK);
		break;
	case s_GUI_BUTTONS__BOT :
		// Bottom
		Graphics_DrawLine(GraphicsObj, 0, 94, 118, 94, s_GRAPHICS_COLOR__BLACK);
		Graphics_DrawLine(GraphicsObj, 118, 94, 143, 167, s_GRAPHICS_COLOR__BLACK);
		break;
	default:
		break;
	}


	if(Opt == s_GUI_DISPLAY_OPT__CLEAR_DISPLAY || Opt == s_GUI_DISPLAY_OPT__DISPLAY) {
		SharpLcd_DisplayBuffer(GraphicsObj->pBuf);
	}
}




