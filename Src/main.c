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
#include "filter.h"
#include "bsp_override.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include <string.h>

//
//
// -- Global --
//
TIM_HandleTypeDef htim;
int TIM_TICK = 0;

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
	Audio_Init(); // Initialize Audio Functionality

	/* Test Data */
	uint16_t* some_random_data[RECORD_BUFFER_SIZE];
	int fx_state = FX_STATE_NONE;

	/* Main Loop */
	while (1) {
		/* 1st or 2nd half of the record buffer ready for being copied
		to the Playback buffer */
		if (audio_rec_buffer_state != BUFFER_OFFSET_NONE)
		{
			/* Copy half of the record buffer to the playback buffer */
			if (audio_rec_buffer_state == BUFFER_OFFSET_HALF)
			{
				CopyBuffer(&audio_out_buffer[0], &audio_in_buffer[0], RECORD_BUFFER_SIZE / 2);
			}
			else
			{
				CopyBuffer(&audio_out_buffer[RECORD_BUFFER_SIZE / 2],
							&audio_in_buffer[RECORD_BUFFER_SIZE / 2],
											 RECORD_BUFFER_SIZE / 2);\
			}
			/* Wait for next data */
			audio_rec_buffer_state = BUFFER_OFFSET_NONE;
		}
		if (audio_tx_buffer_state)
		{
			audio_tx_buffer_state = 0;
		}
		// Handle UI Updates
		if (TIM_TICK == 1) {
			fx_state = UI_Handler(&audio_out_buffer);
			TIM_TICK = 0;
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
	htim.Init.Period = 4999U; //100000Hz/5000 = 20Hz
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
