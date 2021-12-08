/*
 * bsp_override.h
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#ifndef BSP_OVERRIDE_H_
#define BSP_OVERRIDE_H_

#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include "main.h"
#include "stm32f7xx_hal.h"

typedef enum
{
    BUFFER_OFFSET_NONE = 0,
    BUFFER_OFFSET_HALF = 1,
    BUFFER_OFFSET_FULL = 2,
} BUFFER_StateTypeDef;


#define RECORD_BUFFER_SIZE  4096

SAI_HandleTypeDef haudio_out_sai, haudio_in_sai;


/* Buffer containing the PCM samples coming from the microphone */
int16_t audio_in_buffer[RECORD_BUFFER_SIZE];

/* Buffer used to stream the recorded PCM samples towards the audio codec. */
int16_t audio_out_buffer[RECORD_BUFFER_SIZE];

static AUDIO_DrvTypeDef  *audio_drv;


uint8_t BSP_AUDIO_IN_OUT_Init(uint32_t AudioFreq);
uint8_t _BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);
static void SAI_AUDIO_IN_MspInit(SAI_HandleTypeDef *hsai, void *Params);
static void SAIx_In_Init(uint32_t AudioFreq);
static void SAIx_In_DeInit(void);



#endif /* BSP_OVERRIDE_H_ */
