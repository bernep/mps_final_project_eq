//--------------------------------
// Final Project - User Interface
//--------------------------------


#ifndef UI_H_
#define UI_H_

/* Includes */
#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery_ts.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "jpeg_utils.h"
#include "init.h"
#include <stdlib.h>

/* Definitions */
// -- Menu Selection -- //
#define MAIN_MENU_STATE			0
#define FX_MENU_STATE			1
#define SV_MENU_STATE			2
// -- FX Selection -- //
#define FX_STATE_NONE			0
#define FX_STATE_1 				1
#define FX_STATE_2 				2
#define FX_STATE_3 				3
#define FX_STATE_4 				4
// -- USB STATE -- //
#define USB_STATE_OFF			0
#define USB_STATE_ON			1
// -- SV STATE -- //
#define SV_STATE_SCOPE			0
#define SV_STATE_SPECTRUM		1
// -- JPEG Definitions -- //
#define LCD_FRAME_BUFFER        0xC0000000
#define JPEG_OUTPUT_DATA_BUFFER 0xC0200000
#define JPEG_BUFFER_SIZE 		((uint32_t)(64 * 1024))

/* Struct Definition */
struct ui_data_struct {
	int fx_selection_state, usb_selection_state, sv_selection_state;
};
typedef struct ui_data_struct Struct;

Struct ui_data;


/* Function Prototypes */
void UI_Init();
void UI_Config_Main();
void UI_Config_FX();
void UI_Config_SV(uint16_t sv_state);
Struct UI_Handler(uint16_t* pData, uint16_t fx_state_current, uint16_t usb_state_current, uint16_t sv_state_current);
void Button_Handler();
void SV_Handler(uint16_t* pData, uint16_t sv_state);
Struct TouchScreen_Handler(uint16_t fx_state_current, uint16_t usb_state_current, uint16_t sv_state_curren);
void displayJPEG(char* fileName, uint32_t xPos, uint32_t yPos);
uint8_t *colorConversion(uint8_t *jpeg_addr, uint32_t num_bytes);
void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info);


#endif
