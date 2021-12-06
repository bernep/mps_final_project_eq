//--------------------------------
// Final Project - Filtering
//--------------------------------
/* Includes */
#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"
#include "init.h"
#include <stdlib.h>

/* Function Prototypes */
void Calc_FX1_Buffer(uint16_t* pBuffer, uint16_t Buffer_Size);
int Calc_FX1_Sample(int inSample);
