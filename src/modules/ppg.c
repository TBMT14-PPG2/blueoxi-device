/**
 * @file	ppg.c
 * @author  Eriks Zaharans
 * @date    27 Nov 2015
 *
 * @section DESCRIPTION
 *
 * PPG library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */
#define s_PPG__SAMPLING				1000.0f


#define s_PPG__FIR_BLOCK_SIZE		32
#define s_PPG__FIR_NUM_TAPS         32

#define s_PPG__PEAK_K				300
#define s_PPG__PEAK_VECTOR_SIZE		(s_PPG__PEAK_K * 2 + 1)
#define s_PPG__PEAK_DELAY			200

#define s_PPG__PULSE_AVG			10
#define s_PPG__SPO2_BUF_SIZE		1000

/* -- Constants -- */

const float32_t s_PPPG_FIR_COEFFS[s_PPG__FIR_NUM_TAPS] = {
		0.00255968478330947f, 0.00322380665929544f, 0.00469576299913165f, 0.00713417451543832f,
		0.0106298357924236f, 0.0151928596444780f, 0.0207460907920445f, 0.0271255646469108f,
		0.0340881927885039f, 0.0413262347295960f, 0.0484875210880014f, 0.0551998797950006f,
		0.0610978312740834f, 0.0658493963599317f, 0.0691808234351183f, 0.0708971937188156f,
		0.0708971937188156f, 0.0691808234351183f, 0.0658493963599317f, 0.0610978312740834f,
		0.0551998797950006f, 0.0484875210880014f, 0.0413262347295960f, 0.0340881927885039f,
		0.0271255646469108f, 0.0207460907920445f, 0.0151928596444780f, 0.0106298357924236f,
		0.00713417451543832f, 0.00469576299913165f, 0.00322380665929544f, 0.00255968478330947
};


/* -- Variables -- */
static float32_t g_Ppg_FirState[s_PPG__FIR_BLOCK_SIZE + s_PPG__FIR_NUM_TAPS - 1];
arm_fir_instance_f32 g_Ppg_FirInst;

float32_t g_Ppg_PeakVector[s_PPG__PEAK_VECTOR_SIZE];


uint16_t g_Ppg_Pulse;
float32_t g_Ppg_PulseBuf[s_PPG__PULSE_AVG];
uint8_t g_Ppg_PulseBufI = 0;

uint16_t g_Ppg_SpO2RedBuf[s_PPG__SPO2_BUF_SIZE];
uint16_t g_Ppg_SpO2RedBufI = 0;
uint16_t g_Ppg_SpO2IrBuf[s_PPG__SPO2_BUF_SIZE];
uint16_t g_Ppg_SpO2IrBufI = 0;



/* -- Functions -- */

/**
 * Initialize PPG
 * @param void No arguments
 * @return void No return
 */
void PPG_Init(void)
{
	// Init FIR
	arm_fir_init_f32(&g_Ppg_FirInst, s_PPG__FIR_NUM_TAPS, (float32_t *)&s_PPPG_FIR_COEFFS[0], &g_Ppg_FirState[0], s_PPG__FIR_BLOCK_SIZE);
}

/**
 * Deinitialize PPG
 * @param void No arguments
 * @return void No return
 */
void PPG_Deinit(void)
{

}



void PPG_Filter(uint16_t *Input, uint16_t *Output)
{
	uint8_t i;
	float32_t input[s_PPG__FIR_BLOCK_SIZE], output[s_PPG__FIR_BLOCK_SIZE];

	for(i = 0; i < s_PPG__FIR_BLOCK_SIZE; i++) {
		input[i] = (float32_t)Input[i];
	}

	arm_fir_f32(&g_Ppg_FirInst, input, output, s_PPG__FIR_BLOCK_SIZE);

	for(i = 0; i < s_PPG__FIR_BLOCK_SIZE; i++) {
		Output[i] = (uint16_t)output[i];
	}
}

uint16_t PPG_DetectPeak(uint16_t Input)
{
	static uint8_t delay = 0;
	static uint16_t time = 0;
	uint16_t i, index = 0;

	// Shift vector to right
	memmove(&g_Ppg_PeakVector[0], &g_Ppg_PeakVector[1], (s_PPG__PEAK_VECTOR_SIZE - 1) * sizeof(g_Ppg_PeakVector[0]));
	// Copy in new data
	g_Ppg_PeakVector[s_PPG__PEAK_VECTOR_SIZE-1] = (float32_t)Input;

	// Increase time
	time++;

	if(delay > 0)
	{
		delay--;
	}
	else
	{
		// Loop through vector
		for(i = 0; i <= s_PPG__PEAK_K; i++)
		{
			if(g_Ppg_PeakVector[i] > g_Ppg_PeakVector[s_PPG__PEAK_K]) {
				break;
			}
			else if(g_Ppg_PeakVector[s_PPG__PEAK_K + i] > g_Ppg_PeakVector[s_PPG__PEAK_K]) {
				break;
			}
			else {
				index = i;
			}
		}
	}

	if(index == s_PPG__PEAK_K)
	{
		PPG_CalcPulse(time);
		time = 0;

		delay = s_PPG__PEAK_DELAY;
		//return g_Ppg_Pulse + 10;
		return (uint16_t)g_Ppg_PeakVector[s_PPG__PEAK_K] + 200;
	}

	//return g_Ppg_Pulse;
	return (uint16_t)g_Ppg_PeakVector[s_PPG__PEAK_K];
}

void PPG_CalcPulse(uint16_t Time)
{
	uint8_t i;
	float32_t temp, pulse;

	temp = (float32_t)Time / s_PPG__SAMPLING;
	pulse = 60.0f / temp;

	if(pulse > 240.0f) {
		pulse = 240.0f;
	}

	g_Ppg_PulseBuf[g_Ppg_PulseBufI] = pulse;
	g_Ppg_PulseBufI = (g_Ppg_PulseBufI + 1) % s_PPG__PULSE_AVG;
	temp = 0.0f;
	for(i = 0; i < s_PPG__PULSE_AVG; i++)
	{
		temp += g_Ppg_PulseBuf[i] / (float32_t)s_PPG__PULSE_AVG;
	}

	g_Ppg_Pulse = (uint16_t)temp;
}



//void PPG_Buffer



/*void PPG_CalcSat()
{
    max_red=0;
    min_red=2^16;
    max_IR=0;
    min_IR=2^16;

    for(i=0;i<=900;i++)
            {
                if (redSig[count-1000+i]>max_red)
                {
                    max_red=redSig[count-1000+i];
                }
                else if (redSig[count-1000+i]<min_red)
                {
                    min_red=redSig[count-1000+i];
                }
                if (IRSig[count-500+i]>max_IR)
                {
                    max_IR=IRSig[count-1000+i];
                }
                else if (IRSig[count-1000+i]<min_IR)
                {
                    min_IR=IRSig[count-1000+i];
                }
            }
            AC_red=max_red-min_red;
            DC_red=max_red;
            AC_IR=max_IR-min_IR;
            DC_IR=max_IR;
            R=0.95*R+0.05*(AC_red/DC_red)/(AC_IR/DC_IR);
            Saturation=9.554*R+81.6639; // Round(alpha*R+beta);
}*/


