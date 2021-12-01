/*
 * audio.c
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#include "audio.h"


void AUDIO_LOOPBACK(void)
     {

	 /* Initialize Audio Recorder with 4 channels to be used */
	 if (BSP_AUDIO_IN_OUT_Init(BSP_AUDIO_FREQUENCY_48K) == AUDIO_OK)
	 {
		 printf("Audio I/O initialization OK\r\n");
	 } else {
		 printf("Audio I/O initialization failed.\r\n");
	 }

	 /* Start Recording */
	 HAL_StatusTypeDef res = HAL_SAI_Receive_DMA(&haudio_in_sai, (uint8_t*)audio_in_buffer, RECORD_BUFFER_SIZE);
	 if (HAL_OK == res)
	 {
		 printf("SAI receive begin OK\r\n");
	 } else {
		 printf("SAI receive error: %d\r\n", res);
	 }

	 printf("Copying Record buffer to Playback buffer\r\n");

	 /* Play the recorded buffer */
	 if (_BSP_AUDIO_OUT_Play((uint16_t *) &audio_out_buffer[0], RECORD_BUFFER_SIZE) == AUDIO_OK)
	 {
		 printf("Audio output OK\r\n");
	 } else {
		 printf("Audio output error\r\n");
	 }
	 printf("\r\n");

	 audio_rec_buffer_state = BUFFER_OFFSET_NONE;
	 while (1)
	 {
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
	 } // end while(1)
 } // end AUDIO_LOOPBACK



 void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
 {
	 audio_tx_buffer_state = 1;
 }


 /**
   * @brief Manages the DMA Transfer complete interrupt.
   * @param None
   * @retval None
   */
 void BSP_AUDIO_IN_TransferComplete_CallBack(void)
 {
	 audio_rec_buffer_state = BUFFER_OFFSET_FULL;
 }


 /**
   * @brief  Manages the DMA Half Transfer complete interrupt.
   * @param  None
   * @retval None
   */
 void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
 {
	 audio_rec_buffer_state = BUFFER_OFFSET_HALF;
 }


 /**
   * @brief  Audio IN Error callback function.
   * @param  None
   * @retval None
   */
 void BSP_AUDIO_IN_Error_CallBack(void)
 {
	 /* This function is called when an Interrupt due to transfer error on or peripheral
		error occurs. */
	 /* Display message on the LCD screen */
	 //BSP_LCD_SetBackColor(LCD_COLOR_RED);
	 //BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"       DMA  ERROR     ", CENTER_MODE);


	 /* Stop the program with an infinite loop */

	 /*
	 while (BSP_PB_GetState(BUTTON_WAKEUP) != RESET)
	 {
		 return;
	 }
	 */

	 /* could also generate a system reset to recover from the error */
	 /* .... */
 }
