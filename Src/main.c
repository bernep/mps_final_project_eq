//--------------------------------
// Final Project - Main
//--------------------------------
//
//
#include "main.h"
#include "init.h"
#include "stm32f7xx_hal.h"
#include "uart.h"
#include "audio.h"
#include "filter.h"
#include "bsp_override.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include <string.h>
#include <ui.h>

//
//
// -- Global --
//
TIM_HandleTypeDef htim;
int TIM_TICK = 0;
int fx_state = FX_STATE_NONE;

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

	/* Main Loop */
	while (1) {
		/* Handle UI Updates */
		if (TIM_TICK == 1) {
			fx_state = UI_Handler((uint16_t*)&audio_out_buffer, fx_state);
			TIM_TICK = 0;
		}
		/* 1st or 2nd half of the record buffer ready for being copied to the Playback buffer */
		if (audio_rec_buffer_state != BUFFER_OFFSET_NONE)
		{
			/* Copy half of the record buffer to the playback buffer */
			if (audio_rec_buffer_state == BUFFER_OFFSET_HALF)
			{
				/* Select Sound FX */
				if (fx_state == FX_STATE_1) {
					Calc_FX1_Buffer((uint16_t *)&audio_out_buffer[0], RECORD_BUFFER_SIZE/2);
				} else if (fx_state == FX_STATE_2) {
					// fx #2
				} else if (fx_state == FX_STATE_2) {
					// fx #3
				} else if (fx_state == FX_STATE_2) {
					// fx #4
				}
				/* Send to Output */
				memcpy(&audio_out_buffer[0], &audio_in_buffer[0], RECORD_BUFFER_SIZE);
			}
			else
			{
				/* Select Sound FX */
				if (fx_state == FX_STATE_1) {
					Calc_FX1_Buffer((uint16_t *)&audio_out_buffer[RECORD_BUFFER_SIZE/2], RECORD_BUFFER_SIZE/2);
				} else if (fx_state == FX_STATE_2) {
					// fx #2
				} else if (fx_state == FX_STATE_2) {
					// fx #3
				} else if (fx_state == FX_STATE_2) {
					// fx #4
				}
				/* Send to Output */
				memcpy(&audio_out_buffer[RECORD_BUFFER_SIZE / 2],
					   &audio_in_buffer[RECORD_BUFFER_SIZE / 2],
					   RECORD_BUFFER_SIZE);
			}
			/* Wait for next data */
			audio_rec_buffer_state = BUFFER_OFFSET_NONE;
		}
		/* Reset audio flag */
		if (audio_tx_buffer_state)
		{
			audio_tx_buffer_state = 0;
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
