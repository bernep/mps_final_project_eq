//--------------------------------
// Final Project - Filtering
//--------------------------------
//
#include "filter.h"

//
//
// -- Globals -----
//
/*

FIR filter designed with
http://t-filter.appspot.com/

sampling frequency: 48000 Hz

* 0 Hz - 20 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = -40.160540821025194 dB

* 30 Hz - 200 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = 4.096587053653316 dB

*/
#define FILTER_TAP_NUM_FX1 63
static double filter_taps_fx1[FILTER_TAP_NUM_FX1] = {
  8578648748.986967,
  8535781276.138885,
  8420973857.706272,
  8208442452.94212,
  7909505351.354264,
  7579930190.913454,
  7269511367.654172,
  6900210819.200389,
  6437617908.593664,
  5882301381.513086,
  5283909126.751851,
  4687878248.550357,
  4052363223.5280676,
  3356411209.679854,
  2590217600.646446,
  1808403194.141123,
  1016896769.8809342,
  217572584.73324543,
  -584565950.3553756,
  -1530641022.9780746,
  -2549926675.5310335,
  -3595423212.0184593,
  -4644186172.709719,
  -5686188762.51133,
  -6779283057.236533,
  -7915257077.060918,
  -9053687217.459929,
  -10251140299.961704,
  -11476860985.575687,
  -12771278532.49489,
  -14128670625.770304,
  -15538931442.512207,
  -14128670625.770304,
  -12771278532.49489,
  -11476860985.575687,
  -10251140299.961704,
  -9053687217.459929,
  -7915257077.060918,
  -6779283057.236533,
  -5686188762.51133,
  -4644186172.709719,
  -3595423212.0184593,
  -2549926675.5310335,
  -1530641022.9780746,
  -584565950.3553756,
  217572584.73324543,
  1016896769.8809342,
  1808403194.141123,
  2590217600.646446,
  3356411209.679854,
  4052363223.5280676,
  4687878248.550357,
  5283909126.751851,
  5882301381.513086,
  6437617908.593664,
  6900210819.200389,
  7269511367.654172,
  7579930190.913454,
  7909505351.354264,
  8208442452.94212,
  8420973857.706272,
  8535781276.138885,
  8578648748.986967
};
static float firdata_fx1[FILTER_TAP_NUM_FX1];
static int firptr_fx1[FILTER_TAP_NUM_FX1];
static int fir_w_ptr_fx1 = 0;

//
//
// -- Initialization -----
//
void Calc_FX1_Buffer(uint16_t* pBuffer, uint16_t Buffer_Size) {
    for (int i = 0; i < Buffer_Size; i++) {
    	pBuffer[i] = Calc_FX1_Sample(pBuffer[i]);
    }
}

int Calc_FX1_Sample(int inSample) {
    float inSampleF = (float)inSample;
    float outdata = 0;

    for (int i=0;i < FILTER_TAP_NUM_FX1; i++) {
        outdata += (firdata_fx1[i]*filter_taps_fx1[firptr_fx1[i]]);
        firptr_fx1[i]++;
    }

    firdata_fx1[fir_w_ptr_fx1] = inSampleF;
    firptr_fx1[fir_w_ptr_fx1] = 0;
    fir_w_ptr_fx1++;
    if (fir_w_ptr_fx1 == FILTER_TAP_NUM_FX1) fir_w_ptr_fx1=0;

    return (int) outdata;
}
