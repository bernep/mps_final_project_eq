//--------------------------------
// Final Project - User Interface
//--------------------------------
//
#include <ui.h>

//
// -- Globals -----
//
/* SD Card Parameters */
SD_HandleTypeDef hsd;
FATFS fs;
DIR dir;
FILINFO fno;
FIL file;
UINT br;
char* path = "0:/";
int SD_CARD_ENABLED = 0;

/* JPEG Parameters */
JPEG_YCbCrToRGB_Convert_Function pConvert_Function;
JPEG_HandleTypeDef hjpeg;
JPEG_ConfTypeDef jpeg_info;
DMA2D_HandleTypeDef hdma2d;
uint32_t MCU_TotalNb = 0;
uint32_t jpeg_input_buffer[JPEG_BUFFER_SIZE];
uint32_t* jpeg_output_buffer = (uint32_t*)JPEG_OUTPUT_DATA_BUFFER;
uint32_t OutputBufferAddress = JPEG_OUTPUT_DATA_BUFFER;
int JPEG_DECODE_COMPLETE = 0;

/* UI Parameters */
TS_StateTypeDef TS_State;
GPIO_InitTypeDef hgpio;
uint32_t xSize_LCD, ySize_LCD, iconSize, iconPosX_FX, iconPosY_FX,
		 iconPosX_SV, iconPosY_SV, iconPosX_FX1, iconPosY_FX1,
		 iconPosX_FX2, iconPosY_FX2, iconPosX_FX3, iconPosY_FX3,
		 iconPosX_FX4, iconPosY_FX4, axisPosX_StartLeft, axisPosY_StartTop,
		 axisScaleX, axisScaleY;
char* iconName_FX = "note.jpg";
char* iconName_SV = "sine.jpg";
char* iconName_FX1 = "note.jpg";
char* iconName_FX2 = "note.jpg";
char* iconName_FX3 = "note.jpg";
char* iconName_FX4 = "note.jpg";
int menu_state = 0;
int user_button_pushed = 0;

//
//
// -- Initialization -----
//
void UI_Init() {
	// Link, Mount, & Open SD Card
	if (FATFS_LinkDriver(&SD_Driver, path) == 0) {
		if (f_mount(&fs, path, 1) == FR_OK) {
			if (f_opendir(&dir, path) == FR_OK) {
				SD_CARD_ENABLED = 1;
			}
		}
	}

    // LCD Initialization
    BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font24);

	// LCD Parameters
	xSize_LCD = BSP_LCD_GetXSize(); // 800 pixels
	ySize_LCD = BSP_LCD_GetYSize(); // 480 pixels
	iconSize = xSize_LCD/8; // 100 pixels
	/* Main Menu */
	iconPosX_FX = xSize_LCD/4;
	iconPosY_FX = ySize_LCD/2-iconSize/2;
	iconPosX_SV = 5*xSize_LCD/8;
	iconPosY_SV = ySize_LCD/2-iconSize/2;
	/* FX Menu */
	iconPosX_FX1 = xSize_LCD/4;
	iconPosY_FX1 = ySize_LCD/4-iconSize/4;
	iconPosX_FX2 = 5*xSize_LCD/8;
	iconPosY_FX2 = iconPosY_FX1;
	iconPosX_FX3 = iconPosX_FX1;
	iconPosY_FX3 = 3*ySize_LCD/4-3*iconSize/4;
	iconPosX_FX4 = iconPosX_FX2;
	iconPosY_FX4 = iconPosY_FX3;
	/* SV Menu */
	axisPosX_StartLeft = 59;
	axisPosY_StartTop = 59;
	axisScaleX = 684;
	axisScaleY = 362;

	// Initialize JPEG Peripheral
	__HAL_RCC_JPEG_CLK_ENABLE(); // Enable CLK
	hjpeg.Instance = JPEG;
	HAL_JPEG_Init(&hjpeg); // Initialize
	HAL_NVIC_SetPriority(JPEG_IRQn, 7, 15); // Enable Interrupts
	HAL_NVIC_EnableIRQ(JPEG_IRQn);

	// Start Up Main Menu
	UI_Config_Main();

	// Touch Screen Initialization
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	// User Pushbutton Initialization
	__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable CLK
	hgpio.Pin = GPIO_PIN_0;
	hgpio.Mode = GPIO_MODE_INPUT;
	hgpio.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &hgpio); // Initialize

	// Reset Terminal (for Debugging)
	printf("\033[2J\033[;H\033c");
	fflush(stdout);
}

//
//
// -- Helper Functions -----
//
/* Bundle UI Interaction Functions */
int UI_Handler(uint16_t* pData, uint16_t fx_state_current) {
	Button_Handler();
	SV_Handler(pData); // pData must have 4096 entries
	return TouchScreen_Handler(fx_state_current);
}

/* Display Main UI Screen */
void UI_Config_Main() {
	// Clear LCD
	BSP_LCD_Clear(LCD_COLOR_LIGHTGRAY);
	// Icons
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(iconPosX_FX, iconPosY_SV, iconSize, iconSize);
	BSP_LCD_FillRect(iconPosX_SV, iconPosY_SV, iconSize, iconSize);
	// Text
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(650, ySize_LCD/2 + 3*iconSize/4,
							(uint8_t *)"Sound Effects", CENTER_MODE);
	BSP_LCD_DisplayStringAt(150, ySize_LCD/2 + 3*iconSize/4,
							(uint8_t *)"Signal Viewer", CENTER_MODE);
	// Display JPEGs (if files are present)
	if (SD_CARD_ENABLED == 1) {
		displayJPEG(iconName_SV, iconPosX_SV, iconPosY_SV); // Signal Viewer
		displayJPEG(iconName_FX, iconPosX_FX, iconPosY_FX); // Sound Effects
	}
}

/* Display FX UI Screen */
void UI_Config_FX() {
	// Clear LCD
	BSP_LCD_Clear(LCD_COLOR_LIGHTGRAY);
	// Icons
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(iconPosX_FX1, iconPosY_FX1, iconSize, iconSize);
	BSP_LCD_FillRect(iconPosX_FX2, iconPosY_FX2, iconSize, iconSize);
	BSP_LCD_FillRect(iconPosX_FX3, iconPosY_FX3, iconSize, iconSize);
	BSP_LCD_FillRect(iconPosX_FX4, iconPosY_FX4, iconSize, iconSize);
	// Text
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(650, iconPosY_FX1+iconSize+20, (uint8_t *)"FX1", CENTER_MODE);
	BSP_LCD_DisplayStringAt(150, iconPosY_FX2+iconSize+20, (uint8_t *)"FX2", CENTER_MODE);
	BSP_LCD_DisplayStringAt(650, iconPosY_FX3+iconSize+20, (uint8_t *)"FX3", CENTER_MODE);
	BSP_LCD_DisplayStringAt(150, iconPosY_FX4+iconSize+20, (uint8_t *)"FX4", CENTER_MODE);
	// Display JPEGs (if files are present)
	if (SD_CARD_ENABLED == 1) {
		displayJPEG(iconName_FX1, iconPosX_FX1, iconPosY_FX1);
		displayJPEG(iconName_FX2, iconPosX_FX2, iconPosY_FX2);
		displayJPEG(iconName_FX3, iconPosX_FX3, iconPosY_FX3);
		displayJPEG(iconName_FX4, iconPosX_FX4, iconPosY_FX4);
	}
}

/* Display Signal Viewer Screen */
void UI_Config_SV() {
	// Clear LCD
	BSP_LCD_Clear(LCD_COLOR_LIGHTGRAY);
	// Major Axes
	for (int i = 1; i < 4; i++) BSP_LCD_DrawHLine(59, 419+i, axisScaleX);
	for (int i = 1; i < 4; i++) BSP_LCD_DrawVLine(57+i, 49, axisScaleY+10);
	// Axes Subdivision Lines
	for (int i = 1; i < 12; i++) BSP_LCD_DrawVLine(60+62*i, 410, 25);
	for (int i = 0; i < 10; i++) BSP_LCD_DrawHLine(48, 49+37*i, 25);
}


/* Handle User Button Interaction for Each Menu */
void Button_Handler() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1 && menu_state != MAIN_MENU_STATE) {
		UI_Config_Main(); // Return to Main Menu on Button Press (if outside of main menu)
		menu_state = MAIN_MENU_STATE;
	}
}

/* Handle Signal Viewer Display */
void SV_Handler(uint16_t* pData) {
	if (menu_state == SV_MENU_STATE) {
		// Clear Graph
		UI_Config_SV();
		// Set Variables
		int avg = 0;
		int prev_y = 0;
		int inverse_scale_factor = 88;
		// Display plot lines for data array
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTRED);
		for (int i = 0; i < 4096; i++) {
			// Average every 6 samples and draw
			avg += *pData/inverse_scale_factor; // Scale to fit on plot
			pData++;
			if (i % 6 == 0) {
				avg /= 6;
				if (i > 0) BSP_LCD_DrawLine(axisPosX_StartLeft+i/6, axisPosY_StartTop+prev_y,
								 axisPosX_StartLeft+i/6+1, axisPosY_StartTop+(axisScaleY-avg));
				prev_y = axisScaleY-avg;
				avg = 0;
			}
		}
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	}
}

/* Handle Touch Screen Interaction for Each Menu */
int TouchScreen_Handler(uint16_t fx_state_current) {
	int menu_selection_state = 0;
	int fx_selection_state = fx_state_current;
	/* Check for Initial Touch */
	BSP_TS_GetState(&TS_State);
	if (TS_State.touchDetected == 1) {
		/* Wait for touch released */
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_TS_GetState(&TS_State);
		/* Main Menu */
		if (menu_state == MAIN_MENU_STATE) {
			/* Detect Icon Touches and Indicate with Rectangle Highlight */
			if ((TS_State.touchX[0] > iconPosX_FX) && (TS_State.touchX[0] < iconPosX_FX+iconSize) &&
				(TS_State.touchY[0] > iconPosY_FX) && (TS_State.touchY[0] < iconPosY_FX+iconSize))
			{
				menu_selection_state = 1;
			}
			else if ((TS_State.touchX[0] > iconPosX_SV) && (TS_State.touchX[0] < iconPosX_SV+iconSize) &&
				(TS_State.touchY[0] > iconPosY_SV) && (TS_State.touchY[0] < iconPosY_SV+iconSize))
			{
				menu_selection_state = 2;
			}
			else
			{
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX - 10, iconPosY_FX - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_SV - 10, iconPosY_SV - 10, iconSize + 20, iconSize + 20);
				menu_selection_state = 0;
			}
		}
		/* FX Menu */
		else if (menu_state == FX_MENU_STATE) {
			/* Detect Icon Touches and Indicate with Rectangle Highlight */
			if ((TS_State.touchX[0] > iconPosX_FX1) && (TS_State.touchX[0] < iconPosX_FX1+iconSize) &&
				(TS_State.touchY[0] > iconPosY_FX1) && (TS_State.touchY[0] < iconPosY_FX1+iconSize))
			{
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
				fx_selection_state = FX_STATE_1;
			}
			else if ((TS_State.touchX[0] > iconPosX_FX2) && (TS_State.touchX[0] < iconPosX_FX2+iconSize) &&
					(TS_State.touchY[0] > iconPosY_FX2) && (TS_State.touchY[0] < iconPosY_FX2+iconSize))
			{
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
				fx_selection_state = FX_STATE_2;
			}
			else if ((TS_State.touchX[0] > iconPosX_FX3) && (TS_State.touchX[0] < iconPosX_FX3+iconSize) &&
					(TS_State.touchY[0] > iconPosY_FX3) && (TS_State.touchY[0] < iconPosY_FX3+iconSize))
			{
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
				fx_selection_state = FX_STATE_3;
			}
			else if ((TS_State.touchX[0] > iconPosX_FX4) && (TS_State.touchX[0] < iconPosX_FX4+iconSize) &&
					(TS_State.touchY[0] > iconPosY_FX4) && (TS_State.touchY[0] < iconPosY_FX4+iconSize))
			{
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
				fx_selection_state = FX_STATE_4;
			}
			else
			{
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
				fx_selection_state = FX_STATE_NONE;
			}
		}
		/* Open New Menu if Option was Selected */
		if (menu_selection_state == 1) { // FX Menu
			UI_Config_FX();
			menu_state = FX_MENU_STATE;
			fx_selection_state = fx_state_current;
			/* Show Selection Rectangle Again */
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			if (fx_selection_state == FX_STATE_1) {
				BSP_LCD_DrawRect(iconPosX_FX1 - 10, iconPosY_FX1 - 10, iconSize + 20, iconSize + 20);
			} else if (fx_selection_state == FX_STATE_2) {
				BSP_LCD_DrawRect(iconPosX_FX2 - 10, iconPosY_FX2 - 10, iconSize + 20, iconSize + 20);
			} else if (fx_selection_state == FX_STATE_3) {
				BSP_LCD_DrawRect(iconPosX_FX3 - 10, iconPosY_FX3 - 10, iconSize + 20, iconSize + 20);
			} else if (fx_selection_state == FX_STATE_4) {
				BSP_LCD_DrawRect(iconPosX_FX4 - 10, iconPosY_FX4 - 10, iconSize + 20, iconSize + 20);
			}
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
		} else if (menu_selection_state == 2) { // Signal Viewer
			UI_Config_SV();
			menu_state = SV_MENU_STATE;
			fx_selection_state = fx_state_current;
		}
	}
	/* Return FX State */
	return fx_selection_state;
}

/* Display JPEG at Specified Location */
void displayJPEG(char* fileName, uint32_t xPos, uint32_t yPos) {
	f_opendir(&dir, path);
	if (f_open(&file, (TCHAR*)fileName, FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
		f_read(&file, jpeg_input_buffer, JPEG_BUFFER_SIZE, &br);
	}
	// Decode JPEG
	HAL_JPEG_Decode_IT(&hjpeg, (uint8_t*)jpeg_input_buffer, JPEG_BUFFER_SIZE,
					   (uint8_t*)jpeg_output_buffer, JPEG_BUFFER_SIZE);
	while (JPEG_DECODE_COMPLETE == 0); // Wait for Decode Completion
	JPEG_DECODE_COMPLETE = 0;
	// Get JPEG Info
	HAL_JPEG_GetInfo(&hjpeg, &jpeg_info);
	uint8_t *raw_output = colorConversion((uint8_t *)jpeg_output_buffer, JPEG_BUFFER_SIZE);
	// Print Image on LCD
	DMA2D_CopyBuffer((uint32_t *)raw_output, (uint32_t *)LCD_FRAME_BUFFER,
					 xPos, yPos, &jpeg_info);
}

//
//
// -- JPEG Functions -----
//
uint8_t *colorConversion(uint8_t *jpeg_addr, uint32_t num_bytes) {
	uint8_t *raw_out_buf = jpeg_addr + num_bytes;
	uint32_t total_raw_data;
	pConvert_Function(jpeg_addr, raw_out_buf, 0, num_bytes, &total_raw_data);

	return raw_out_buf;
}

void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info)
{
	uint32_t destination = (uint32_t)pDst;
	uint32_t source = (uint32_t)pSrc;

	// DMA2D Clock Enable
	__HAL_RCC_DMA2D_CLK_ENABLE();

	// Width offset calculation (from STM32 examples)
	uint32_t width_offset = 0;
	if(jpeg_info->ChromaSubsampling == JPEG_420_SUBSAMPLING) {
		if((jpeg_info->ImageWidth % 16) != 0)
			width_offset = 16 - (jpeg_info->ImageWidth % 16);
	}

	if(jpeg_info->ChromaSubsampling == JPEG_422_SUBSAMPLING) {
		if((jpeg_info->ImageWidth % 16) != 0)
			width_offset = 16 - (jpeg_info->ImageWidth % 16);
	}

	if(jpeg_info->ChromaSubsampling == JPEG_444_SUBSAMPLING) {
		if((jpeg_info->ImageWidth % 8) != 0)
			width_offset = 8 - (jpeg_info->ImageWidth % 8);
	}

	/*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
	hdma2d.Instance 		  = DMA2D;
	hdma2d.Init.Mode          = DMA2D_M2M_PFC;
	hdma2d.Init.ColorMode     = DMA2D_OUTPUT_ARGB8888;
	hdma2d.Init.OutputOffset  = BSP_LCD_GetXSize() - jpeg_info->ImageWidth;

	/*##-2- Foreground Configuration ###########################################*/
	hdma2d.LayerCfg[1].AlphaMode 		= DMA2D_REPLACE_ALPHA;
	hdma2d.LayerCfg[1].InputAlpha 		= 0xFF;
	hdma2d.LayerCfg[1].InputColorMode 	= DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[1].InputOffset 		= width_offset;

	/* DMA2D Initialization */
	HAL_DMA2D_Init(&hdma2d);

	/* DMA2D Config Layer */
	HAL_DMA2D_ConfigLayer(&hdma2d, 1);

	/* DMA2D Start */
	HAL_DMA2D_Start(&hdma2d, source, destination + ((y * BSP_LCD_GetXSize() + x) * 4),
					jpeg_info->ImageWidth, jpeg_info->ImageHeight);

	/* DMA2D Poll for Transfer */
	HAL_DMA2D_PollForTransfer(&hdma2d, 10);
}

//
//
// -- Interrupt & Callback FUnctions -----
//
void JPEG_IRQHandler(void) {
	HAL_JPEG_IRQHandler(&hjpeg); // Pass to HAL
}

void HAL_JPEG_GetDataCallback(JPEG_HandleTypeDef *hjpeg, uint32_t NbDecodedData) {
	bzero(jpeg_input_buffer, JPEG_BUFFER_SIZE);
	HAL_JPEG_ConfigInputBuffer(hjpeg,(uint8_t *)jpeg_input_buffer, JPEG_BUFFER_SIZE);
}

void HAL_JPEG_DataReadyCallback(JPEG_HandleTypeDef *hjpeg, uint8_t *pDataOut, uint32_t OutDataLength) {
	OutputBufferAddress = JPEG_OUTPUT_DATA_BUFFER;
	HAL_JPEG_ConfigOutputBuffer(hjpeg, (uint8_t *)jpeg_output_buffer, OutputBufferAddress);
}

void HAL_JPEG_DecodeCpltCallback(JPEG_HandleTypeDef *hjpeg) {
	JPEG_DECODE_COMPLETE = 1;
}

void HAL_JPEG_ErrorCallback(JPEG_HandleTypeDef *hjpeg) {
	printf("\r\nJPEG Decoding Error");
	if (HAL_JPEG_GetError(hjpeg) == HAL_JPEG_ERROR_HUFF_TABLE)
		printf("\r\nError Code: HAL_JPEG_ERROR_HUFF_TABLE");
	else if (HAL_JPEG_GetError(hjpeg) == HAL_JPEG_ERROR_QUANT_TABLE)
		printf("\r\nError Code: HAL_JPEG_ERROR_QUANT_TABLE");
	else if (HAL_JPEG_GetError(hjpeg) == HAL_JPEG_ERROR_DMA)
		printf("\r\nError Code: HAL_JPEG_ERROR_DMA");
	else if (HAL_JPEG_GetError(hjpeg) == HAL_JPEG_ERROR_TIMEOUT)
		printf("\r\nError Code: HAL_JPEG_ERROR_TIMEOUT");
	else
		printf("\r\nError Code: Unknown");
	fflush(stdout);
}

/* Adjust the width to be a multiple of 8 or 16 when JPEG header has been parsed */
void HAL_JPEG_InfoReadyCallback(JPEG_HandleTypeDef *hjpeg, JPEG_ConfTypeDef *pInfo) {
	// Have to add padding for DMA2D
	if(pInfo->ChromaSubsampling == JPEG_420_SUBSAMPLING) {
		if((pInfo->ImageWidth % 16) != 0)
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));

		if((pInfo->ImageHeight % 16) != 0)
			pInfo->ImageHeight += (16 - (pInfo->ImageHeight % 16));
	}

	if(pInfo->ChromaSubsampling == JPEG_422_SUBSAMPLING) {
		if((pInfo->ImageWidth % 16) != 0)
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));

		if((pInfo->ImageHeight % 8) != 0)
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
	}

	if(pInfo->ChromaSubsampling == JPEG_444_SUBSAMPLING) {
		if((pInfo->ImageWidth % 8) != 0)
			pInfo->ImageWidth += (8 - (pInfo->ImageWidth % 8));

		if((pInfo->ImageHeight % 8) != 0)
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
	}

	if(JPEG_GetDecodeColorConvertFunc(pInfo, &pConvert_Function, &MCU_TotalNb) != HAL_OK) {
		printf("Error getting DecodeColorConvertFunct\r\n");
		while(1);
	}
}
