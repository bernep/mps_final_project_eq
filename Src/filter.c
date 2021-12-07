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
float alpha_fx1 = 0.2;
float alpha_fx2 = 0.2;
float alpha_fx3 = 0.49906992;
float alpha_fx4 = 0.26906992;

//
//
// -- Functions -----
//
void FX1(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = alpha_fx1 * pBuffer[i] + (1-alpha_fx1) * pBufferFilt[i-1];
	}
}

void FX2(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = alpha_fx2 * pBufferFilt[i-1] + alpha_fx2 * (pBuffer[i]-pBuffer[i-1]);
	}
}

void FX3(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = pBufferFilt[i]/3;
	}
}

void FX4(uint16_t* pBufferFilt, uint16_t* pBuffer, uint16_t Buffer_Size) {
	float ff = 3000/48000;
	double ita = 1.0/ tan(M_PI*ff);
	double q=sqrt(2.0);
	double b0 = 1.0 / (1.0 + q*ita + ita*ita);
	double b1 = 2*b0;
	double b2 = b0;
	double a1 = 2.0 * (ita*ita - 1.0) * b0;
	double a2 = -(1.0 - q*ita + ita*ita) * b0;
	for (int i = 1; i < Buffer_Size; i++) {
		pBufferFilt[i] = b0*pBuffer[i] + b1*pBuffer[i-1] + b2*pBuffer[i-2]
					   + a1*pBufferFilt[i-1] + a2*pBufferFilt[i-2];
	}
}
