/*
 * audio.c
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#include "audio.h"
#include "filter.h"
#include "usb.h"



void USB_Audio_Init(void){


}


/*
 * Line Audio Initalizaionts
 */


void Line_Audio_Init(void) {

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

	 /* Play the Recorded buffer */
	 if (_BSP_AUDIO_OUT_Play((uint16_t *) &audio_out_buffer[0], RECORD_BUFFER_SIZE) == AUDIO_OK)
	 {
		 printf("Audio output OK\r\n");
	 } else {
		 printf("Audio output error\r\n");
	 }
	 printf("\r\n");

	 audio_line_in_buffer_state = BUFFER_OFFSET_NONE;

 }


/*
 * Line Audio Callbacks
 */

 void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
 {
	 audio_line_out_buffer_state = 1;
 }


 /**
   * @brief Manages the DMA Transfer complete interrupt.
   * @param None
   * @retval None
   */
 void BSP_AUDIO_IN_TransferComplete_CallBack(void)
 {
	 audio_line_in_buffer_state = BUFFER_OFFSET_FULL;
 }


 /**
   * @brief  Manages the DMA Half Transfer complete interrupt.
   * @param  None
   * @retval None
   */
 void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
 {
	 audio_line_in_buffer_state = BUFFER_OFFSET_HALF;
 }


 /**
   * @brief  Audio IN Error callback function.
   * @param  None
   * @retval None
   */
void BSP_AUDIO_IN_Error_CallBack(void){
	/* handle errors */
 }
