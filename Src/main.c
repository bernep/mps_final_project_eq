//--------------------------------
// Final Project - Main
//--------------------------------
//
//
#include "main.h"
#include "init.h"
#include "stm32f7xx_hal.h"
#include "uart.h"
#include "util.h"
#include "audio.h"
#include "eq_ui.h"
#include "bsp_override.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include <string.h>

//
//
// -- Main Function -----
//
int main(void) {
	/* Initialization */
	Sys_Init(); // Initialize STM32 System
	UI_Init(); // Initialize SD Card, LCD, JPEG Peripheral, and Pushbutton
	Audio_Init(); // Initialize Audio Functionality

	/* Test Data */
	uint16_t* some_random_data[4096];
	for (int i = 0; i < 4096; i++) {
		some_random_data[i] = 2*rand()/524288;
	}
	int fx_state = FX_STATE_NONE;

	/* Main Loop */
	while (1) {
		 // Handle UI Updates
		 fx_state = UI_Handler(&some_random_data);

		 /* 1st or 2nd half of the record buffer ready for being copied
		 to the Playback buffer */
		 if (audio_rec_buffer_state != BUFFER_OFFSET_NONE)
		 {
			 /* Copy half of the record buffer to the playback buffer */
			 if (audio_rec_buffer_state == BUFFER_OFFSET_HALF)
			 {
				 CopyBuffer(&audio_out_buffer[0], &audio_in_buffer[0], RECORD_BUFFER_SIZE / 2);
			 } else {
				 /* if(audio_rec_buffer_state == BUFFER_OFFSET_FULL)*/
				 CopyBuffer(&audio_out_buffer[RECORD_BUFFER_SIZE / 2],
							  &audio_in_buffer[RECORD_BUFFER_SIZE / 2],
											RECORD_BUFFER_SIZE / 2);
			 }
			 /* Wait for next data */
			 audio_rec_buffer_state = BUFFER_OFFSET_NONE;
		}
		if (audio_tx_buffer_state)
		{
			 audio_tx_buffer_state = 0;
		}
		fx_state = UI_Handler((uint16_t*)&some_random_data); // Handle UI Interaction
	}
}
