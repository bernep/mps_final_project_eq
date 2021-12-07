//--------------------------------
// Final Project - Filtering
//--------------------------------
/* Includes */
#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"
#include "init.h"
#include <stdlib.h>

/* Function Prototypes */
void FX1(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size);
void FX2(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size);
void FX3(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size);
void FX4(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size);
