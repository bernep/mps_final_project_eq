//--------------------------------
// Final Project - Filtering
//--------------------------------
//
#include "filter.h"
#include "math.h"

//
//
// -- Globals -----
//
float alpha_fx1 = 0.1;
float alpha_fx2 = 0.15;
float alpha_fx3 = 0.49906992;
float alpha_fx4 = 0.26906992;

//
//
// -- Functions -----
//
//Low  Pass
void FX1(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt++;
		pBuffer++;
		*pBufferFilt = *pBuffer*2;
	}
}

//High Pass
void FX2(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = pBufferFilt[i-1] + (pBuffer[i]-pBuffer[i-1]);
	}
}

void FX3(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt++;
		pBuffer++;
		*pBufferFilt = *pBuffer/2;
	}
}

void FX4(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 0; i < Buffer_Size; i++) {
		pBufferFilt++;
		*pBufferFilt = 0;
	}
}
