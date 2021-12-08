//--------------------------------
// Final Project - Filtering
//--------------------------------
//
#include "filter.h"

//
//
// -- Globals -----
//
// *None*

//
//
// -- Functions -----
//
void FX1(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt++;
		pBuffer++;
		*pBufferFilt = *pBuffer*2;
	}
}

void FX2(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = pBufferFilt[i-1] + (pBuffer[i]-pBuffer[i-1]);
	}
}

void FX3(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt++;
		pBuffer++;
		*pBufferFilt = *pBuffer/2;
	}
}

void FX4(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 0; i < Buffer_Size; i++) {
		pBufferFilt++;
		*pBufferFilt = 0;
	}
}
