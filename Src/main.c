//--------------------------------
// Final Project - Main
//--------------------------------
//
//
#include "main.h"
#include "init.h"
#include "stm32f7xx_hal.h"
#include "uart.h"
#include "usb.h"
#include "audio.h"
#include "filter.h"
#include "bsp_override.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include <string.h>
#include "ui.h"
#include "fft.h"
#include "complex.h"

//
//
// -- Global --
//
/* Timer */
TIM_HandleTypeDef htim;
int TIM_TICK = 0;
/* UI */
int fx_state = FX_STATE_NONE;
int sv_state = SV_STATE_SCOPE;
int usb_state = USB_STATE_OFF;
/* Audio */
double audio_ft_buffer_real[RECORD_BUFFER_SIZE];
double audio_ft_buffer_imag[RECORD_BUFFER_SIZE];
int16_t audio_ft_out_buffer[RECORD_BUFFER_SIZE];

//
//
// -- Function Prototypes --
//
void Timer_Init();

//
//
// -- Main Function -----
//
int main(void) {
	/* Initialization */
	Sys_Init(); // Initialize STM32 System
	Timer_Init(); // Initialize Program Timer
	UI_Init(); // Initialize SD Card, LCD, JPEG Peripheral, and Pushbutton
	Line_Audio_Init(); // Initialize Audio Functionality
	//USB_Audio_Init();
	//usb_state = USB_STATE_ON;
	//ui_data.usb_selection_state = USB_STATE_ON;

	/* Main Loop */
	while (1) {
		/* Handle UI Updates */
		if (TIM_TICK == 1) {
			/* Time Domain Visualization */
			if (sv_state == SV_STATE_SCOPE) {
				ui_data = UI_Handler((int16_t*)&audio_out_buffer, fx_state, usb_state, sv_state);
			}
			/* Frequency Domain Visualization */
			else {
				for (int i = 0; i < RECORD_BUFFER_SIZE; i++) {
					audio_ft_buffer_real[i] = (double)audio_in_buffer[i];
					audio_ft_buffer_imag[i] = 0;
				}
				FFT(-1, 12, (double*)&audio_ft_buffer_real, (double*)&audio_ft_buffer_imag);
				for (int i = 0; i < RECORD_BUFFER_SIZE; i++) {
					audio_ft_out_buffer[i] = (int16_t)audio_ft_buffer_real[i]/2;
				}
				ui_data = UI_Handler((int16_t*)&audio_ft_out_buffer, fx_state, usb_state, sv_state);
			}
			fx_state = ui_data.fx_selection_state;
			usb_state = ui_data.usb_selection_state;
			sv_state = ui_data.sv_selection_state;
			TIM_TICK = 0;
		}


		/* 1st or 2nd half of the record buffer ready for being copied to the Playback buffer */
		if (audio_line_in_buffer_state != BUFFER_OFFSET_NONE)
		{
			/* Copy half of the record buffer to the playback buffer */
			if (audio_line_in_buffer_state == BUFFER_OFFSET_HALF)
			{
				/* Select Sound FX */
				if (fx_state == FX_STATE_1) {
					FX1((int16_t*)&audio_out_buffer, (int16_t*)&audio_in_buffer, RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_2) {
					FX2((int16_t*)&audio_out_buffer, (int16_t*)&audio_in_buffer, RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_3) {
					FX3((int16_t*)&audio_out_buffer, (int16_t*)&audio_in_buffer, RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_4) {
					FX4((int16_t*)&audio_out_buffer, (int16_t*)&audio_in_buffer, RECORD_BUFFER_SIZE);
				} else { // No FX
					memcpy((int16_t*)&audio_out_buffer[0], (int16_t*)&audio_in_buffer[0], RECORD_BUFFER_SIZE);
				}
			}
			else
			{
				/* Select Sound FX */
				if (fx_state == FX_STATE_1) {
					FX1((int16_t*)&audio_out_buffer[RECORD_BUFFER_SIZE/2],
					    (int16_t*)&audio_in_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_2) {
					FX2((int16_t*)&audio_out_buffer[RECORD_BUFFER_SIZE/2],
					    (int16_t*)&audio_in_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_3) {
					FX3((int16_t*)&audio_out_buffer[RECORD_BUFFER_SIZE/2],
					    (int16_t*)&audio_in_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE);
				} else if (fx_state == FX_STATE_4) {
					FX4((int16_t*)&audio_out_buffer[RECORD_BUFFER_SIZE/2],
						(int16_t*)&audio_in_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE);
				} else { // No FX
					memcpy((int16_t*)&audio_out_buffer[RECORD_BUFFER_SIZE/2],
						   (int16_t*)&audio_in_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE);
				}
			}
			/* Wait for next data */
			audio_line_in_buffer_state = BUFFER_OFFSET_NONE;
		}

		if(audio_usb_in_buffer_state != BUFFER_OFFSET_NONE){
			printf("we got some data\r\n");
			fflush(stdout);
		}

		/* Reset audio flag */
		if (audio_line_out_buffer_state)
		{
			audio_line_out_buffer_state = 0;
		}
	}
}

//
//
// -- Timer Initialization and Callbacks --
//
void Timer_Init() {
	__HAL_RCC_TIM7_CLK_ENABLE(); // Clock Enable
	htim.Instance = TIM7;
	htim.Init.Prescaler = 1079U; //108MHz/1080 = 100000Hz
	htim.Init.Period = 3333U; //100000Hz/3334 = 30Hz
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
	HAL_TIM_Base_Init(&htim);
	HAL_TIM_Base_Start_IT(&htim);
}

void TIM7_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM7) {
		TIM_TICK = 1;
	}
}
