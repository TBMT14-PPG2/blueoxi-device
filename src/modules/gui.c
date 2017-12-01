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
#define s_GUI__MAIN_MENU_ITEM_COUNT		5

/* -- Constants -- */
const uint8_t *const s_GUI__MAIN_MENU_ITEMS[] = {
		"WiFi Stream",
		"USB Stream",
		"SpO2 + BLE",
		"Record",
		"Stream Rec."
};

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
		sprintf(str, "%d%%", (int)Battery);
	} else {
		sprintf(str, "C %d%%", (int)Battery);
	}
	Graphics_FillRect(GraphicsObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)str, appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);

	// Display menu
	Graphics_DrawText(GraphicsObj, 30, 54, (uint8_t *)"WiFi Stream", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 96, (uint8_t *)"USB Stream", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 138, (uint8_t *)"SpO2 + BLE", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);

	// Display underlines
	// Top
	Graphics_DrawLine(GraphicsObj, 0, 72, 118, 72, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 72, 143, 30, s_GRAPHICS_COLOR__BLACK);
	// Mid
	Graphics_DrawLine(GraphicsObj, 0, 114, 118, 114, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 114, 143, 114, s_GRAPHICS_COLOR__BLACK);
	// Bottom
	Graphics_DrawLine(GraphicsObj, 0, 156, 118, 156, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 156, 143, 167, s_GRAPHICS_COLOR__BLACK);

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












void Gui_InitWifi(GraphicsObj_t *GraphicsObj)
{
	uint8_t exit;

	// Turn on Wifi
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Booting WiFi...", 1, 1, s_GUI_DISPLAY_OPT__CLEAR_DISPLAY);
	s_POWER__WIFI_EN_SET();
	HAL_Delay(3000);
	Wifi_Init();
	Wifi_TxInit();
	HAL_Delay(1000);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Connect to:", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"\"blueoxi_wifi\"", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);

	// Wait for Client
	exit = 1;
	while(exit)
	{
		exit = Wifi_Wait();
		Wifi_Process();
	}
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Client", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Connected.", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
	HAL_Delay(2000);
}

void Gui_ConnectWifi(GraphicsObj_t *GraphicsObj)
{
	uint8_t exit;

	// Connect to Server
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Connecting", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"to server...", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
	exit = 1;
	while(exit)
	{
		exit = Wifi_Connect();
		Wifi_Process();
	}

	// Connected
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Connected", 1, 1, s_GUI_DISPLAY_OPT__CLEAR_DISPLAY);
	HAL_Delay(1000);
}

void Gui_InitUsb(GraphicsObj_t *GraphicsObj)
{
	// Config USB
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Configuring", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"USB port...", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
	MX_USB_DEVICE_Init();
	Comm_Init();
	HAL_Delay(2000);
}

void Gui_InitBle(GraphicsObj_t *GraphicsObj)
{
	// Config BLE
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Configuring", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Bluetooth...", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
	Ble_Init();
	HAL_Delay(2000);
}


Error_t Gui_InitPpg(GraphicsObj_t *GraphicsObj)
{
	// Setup PPG
	Buttons_ClearAllEvents();
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"Setting up", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
	Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"PPG sensor...", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
	s_POWER__PPG_EN_SET();
	HAL_Delay(1000);
	if(Afe44xx_SetUp() == s_ERROR) {
		Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"PPG sensor", 2, 1, s_GUI_DISPLAY_OPT__CLEAR);
		Gui_DisplayCenterString(GraphicsObj, (uint8_t *)"has error :(", 2, 2, s_GUI_DISPLAY_OPT__DISPLAY);
		HAL_Delay(2000);

		return s_ERROR;
	}
	HAL_Delay(1000);

	return s_OK;
}

uint8_t Gui_DisplayStreamMenu(GraphicsObj_t *GraphicsObj)
{
	uint8_t exit = 1, ret = 0;

	Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);

	// Question
	Graphics_FillRect(GraphicsObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)"Stream?", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);

	// Display menu
	Graphics_DrawText(GraphicsObj, 30, 54, (uint8_t *)"WiFi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 96, (uint8_t *)"USB", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(GraphicsObj, 30, 138, (uint8_t *)"No", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);

	// Display underlines
	// Top
	Graphics_DrawLine(GraphicsObj, 0, 72, 118, 72, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 72, 143, 30, s_GRAPHICS_COLOR__BLACK);
	// Mid
	Graphics_DrawLine(GraphicsObj, 0, 114, 118, 114, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 114, 143, 114, s_GRAPHICS_COLOR__BLACK);
	// Bottom
	Graphics_DrawLine(GraphicsObj, 0, 156, 118, 156, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawLine(GraphicsObj, 118, 156, 143, 167, s_GRAPHICS_COLOR__BLACK);

	SharpLcd_DisplayBuffer(GraphicsObj->pBuf);

	while(exit)
	{
		// Check all the buttons
		if(g_Buttons_TopPressEvent == 1) {
			ret = 1;
			exit = 0;
		}
		else if(g_Buttons_MidPressEvent == 1) {
			ret = 2;
			exit = 0;
		}
		else if(g_Buttons_BotPressEvent == 1) {
			ret = 0;
			exit = 0;
		}
	}

	// Clear event
	Buttons_ClearAllEvents();

	return ret;
}


uint8_t Gui_DisplayMainMenu(GraphicsObj_t *GraphicsObj)
{
	uint32_t updateTimer = 0;
	uint8_t exit = 1, ret = 0, update = 1;
	uint8_t str[32];

	// Menu variables
	uint8_t item = 0;

	// Clear graphics buffer
	Graphics_ClearBuffer(GraphicsObj, s_GRAPHICS_COLOR__WHITE);

	while(exit)
	{
		// Update battery level
		if((HAL_GetTick() - updateTimer) > 10000 || update == 1) {
			updateTimer = HAL_GetTick();

			// Check charging
			if(s_POWER__CHARGE_STAT_ISSET()) {
				sprintf(str, "%d%%", (int)Power_BateryLevel());
			}
			else {
				sprintf(str, "C %d%%", (int)Power_BateryLevel());
			}

			// Update menu
			Graphics_FillRect(GraphicsObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
			Graphics_DrawText(GraphicsObj, 0, 7, (uint8_t *)str, appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
			SharpLcd_DisplayBuffer(GraphicsObj->pBuf);
		}

		if(update == 1) {


			// Clear
			Graphics_FillRect(GraphicsObj, 0, 30, s_GRAPHICS__LCD_WIDTH, s_GRAPHICS__LCD_HEIGHT-1, s_GRAPHICS_COLOR__WHITE);

			// Draw arrows
			if(item > 0) {
				// Up
				Graphics_DrawLine(GraphicsObj, 62, 66, 82, 66, s_GRAPHICS_COLOR__BLACK);
				Graphics_DrawLine(GraphicsObj, 62, 66, 72, 50, s_GRAPHICS_COLOR__BLACK);
				Graphics_DrawLine(GraphicsObj, 82, 66, 72, 50, s_GRAPHICS_COLOR__BLACK);
			}

			if(item < (s_GUI__MAIN_MENU_ITEM_COUNT-1)) {
				// Down
				Graphics_DrawLine(GraphicsObj, 62, 129, 82, 129, s_GRAPHICS_COLOR__BLACK);
				Graphics_DrawLine(GraphicsObj, 62, 129, 72, 145, s_GRAPHICS_COLOR__BLACK);
				Graphics_DrawLine(GraphicsObj, 82, 129, 72, 145, s_GRAPHICS_COLOR__BLACK);
			}

			Graphics_DrawText(GraphicsObj, 30, 86, s_GUI__MAIN_MENU_ITEMS[item], appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);

			// Display underlines
			// Mid
			Graphics_DrawLine(GraphicsObj, 0, 104, 118, 104, s_GRAPHICS_COLOR__BLACK);
			Graphics_DrawLine(GraphicsObj, 118, 104, 143, 104, s_GRAPHICS_COLOR__BLACK);
			SharpLcd_DisplayBuffer(GraphicsObj->pBuf);

			update = 0;
		}

		// Check all the buttons
		if(g_Buttons_TopPressEvent == 1) {
			// Clear event
			Buttons_ClearAllEvents();

			if(item > 0) {
				item--;
				update = 1;
			}

		}
		else if(g_Buttons_MidPressEvent == 1) {
			// Clear event
			Buttons_ClearAllEvents();
			exit = 0;
			ret = item;
		}
		else if(g_Buttons_BotPressEvent == 1) {
			// Clear event
			Buttons_ClearAllEvents();

			if(item < (s_GUI__MAIN_MENU_ITEM_COUNT-1)) {
				item++;
				update = 1;
			}
		}

	}

	return ret;
}

