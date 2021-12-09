/*
 * audio.h
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "bsp_override.h"
#include "audio_mic_node.h"
#include "audio_speaker_node.h"

volatile uint32_t  audio_usb_in_buffer_state;
volatile uint32_t  audio_usb_out_buffer_state;

volatile uint32_t  audio_line_in_buffer_state;
volatile uint32_t  audio_line_out_buffer_state;

extern AUDIO_MicNode_t RecordingMicrophoneNode;
extern AUDIO_SpeakerNode_t *current_speaker;

void USB_Audio_Init(void);
void Line_Audio_Init(void);


void BSP_AUDIO_OUT_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_TransferComplete_CallBack(void);
void BSP_AUDIO_IN_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_Error_CallBack(void);

void Error_Handler(void);

#endif /* AUDIO_H_ */
