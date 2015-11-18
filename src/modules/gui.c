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


/*
	// Second, write in the age.
	Graphics_ClearBuffer(&graphObj, s_GRAPHICS_COLOR__WHITE);
	Graphics_FillRect(&graphObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 0, 7, (uint8_t *)"blueoxi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
	Graphics_DrawText(&graphObj, 0, 50.5, (uint8_t *)"Your Age", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 0, 97, (uint8_t *)"23", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	SharpLcd_DisplayBuffer(graphObj.pBuf);
	HAL_Delay(5000);

	// Third, recording
	Graphics_ClearBuffer(&graphObj, s_GRAPHICS_COLOR__WHITE);
	Graphics_FillRect(&graphObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 0, 7, (uint8_t *)"blueoxi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
	Graphics_DrawText(&graphObj, 90, 51, (uint8_t *)"60", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 90, 90, (uint8_t *)"130", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 90, 129, (uint8_t *)"98", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__RIGHT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, s_GRAPHICS__LCD_WIDTH-75, 53, (uint8_t *)"% HR", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, s_GRAPHICS__LCD_WIDTH-75, 92, (uint8_t *)"BPM", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, s_GRAPHICS__LCD_WIDTH-75, 131, (uint8_t *)"% SpO2", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	SharpLcd_DisplayBuffer(graphObj.pBuf);
	HAL_Delay(5000);

	// Fourth, after record
	Graphics_ClearBuffer(&graphObj, s_GRAPHICS_COLOR__WHITE);
	Graphics_FillRect(&graphObj, 0, 0, s_GRAPHICS__LCD_WIDTH, 30, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 0, 7, (uint8_t *)"blueoxi", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__WHITE);
	Graphics_DrawText(&graphObj, 0, 50, (uint8_t *)"Mean HR", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 0, 106, (uint8_t *)"Mean O2-sat", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 90, 73, (uint8_t *)"120 BMP", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	Graphics_DrawText(&graphObj, 90, 129, (uint8_t *)"98 %", appleLiGothic_22ptFontInfo, s_GRAPHICS_TEXT_ALIGN__CENTER, s_GRAPHICS_COLOR__BLACK);
	//Graphics_DrawText(&graphObj, s_GRAPHICS__LCD_WIDTH-75, 75, (uint8_t *)"BMP", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	//Graphics_DrawText(&graphObj, s_GRAPHICS__LCD_WIDTH-75, 136, (uint8_t *)"%", appleLiGothic_16ptFontInfo, s_GRAPHICS_TEXT_ALIGN__LEFT, s_GRAPHICS_COLOR__BLACK);
	SharpLcd_DisplayBuffer(graphObj.pBuf);
*/
