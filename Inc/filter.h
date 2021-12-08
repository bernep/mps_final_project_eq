//--------------------------------
// Final Project - Filtering
//--------------------------------
/* Includes */
#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"
#include "init.h"
#include "bsp_override.h"
#include <stdlib.h>

/* Function Prototypes */
void FX1(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size);
void FX2(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size);
void FX3(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size);
void FX4(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size);
