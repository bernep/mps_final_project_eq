/*
 * audio.h
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "bsp_override.h"


volatile uint32_t  audio_rec_buffer_state;
volatile uint32_t  audio_tx_buffer_state = 0;


void AUDIO_LOOPBACK(void);

void BSP_AUDIO_OUT_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_TransferComplete_CallBack(void);
void BSP_AUDIO_IN_HalfTransfer_CallBack(void);
void BSP_AUDIO_IN_Error_CallBack(void);


#endif /* AUDIO_H_ */
