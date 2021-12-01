/*
 * util.c
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#include "util.h"

void CopyBuffer(int16_t *pbuffer1, int16_t *pbuffer2, uint16_t BufferSize){
	 uint32_t i = 0;
	 for (i = 0; i < BufferSize; i++) {
		 pbuffer1[i] = pbuffer2[i];
	 }
}
