//--------------------------------
// Final Project - Filtering
//--------------------------------
//
#include "filter.h"

//
//
// -- Globals -----
//
//Filter parameters
float alpha_fx1 = 0.02;
float alpha_fx2 = 0.7;

//
//
// -- Functions -----
//
void FX1(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		//Lowpass Filter
		pBufferFilt[i] = pBufferFilt[i-1]*alpha_fx1 + (pBuffer[i])*(1-alpha_fx1);
	}
}

void FX2(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		//Highpass Filter
		pBufferFilt[i] = (pBufferFilt[i-1])*alpha_fx2 + (pBuffer[i])*(1-alpha_fx2);

	}
}

void FX3(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	//Bandpass Filter
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = ((pBufferFilt[i-1])*alpha_fx2 + (pBuffer[i])*(1-alpha_fx2)) - (pBufferFilt[i-1]*alpha_fx1 + (pBuffer[i])*(1-alpha_fx1));
	}
}

void FX4(int16_t* pBufferFilt, int16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 0; i < Buffer_Size; i++) {
		pBufferFilt++;
		*pBufferFilt = 0;
	}
}
