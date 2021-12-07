/*
 * audio.h
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "bsp_override.h"

volatile uint32_t  audio_usb_in_buffer_state = BUFFER_OFFSET_NONE;
volatile uint32_t  audio_usb_out_buffer_state = BUFFER_OFFSET_NONE;

volatile uint32_t  audio_line_in_buffer_state = BUFFER_OFFSET_NONE;
volatile uint32_t  audio_line_out_buffer_state = BUFFER_OFFSET_NONE;

void USB_Audio_Init(void);
void Line_Audio_Init(void);

void BSP_AUDIO_OUT_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_TransferComplete_CallBack(void);
void BSP_AUDIO_IN_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_Error_CallBack(void);


#endif /* AUDIO_H_ */
