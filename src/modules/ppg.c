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

#define s_PPG__FIR_BLOCK_SIZE		29
#define s_PPG__FIR_NUM_TAPS         29

/* -- Constants -- */
/*const float32_t s_PPPG_FIR_COEFFS[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};*/


/* -- Variables -- */
arm_fir_instance_f32 g_Ppg_FirInst;




/* -- Functions -- */

/**
 * Initialize PPG
 * @param void No arguments
 * @return void No return
 */
void PPG_Init(void)
{

	//arm_fir_init_f32(&g_Ppg_FirInst, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);

}

/**
 * Deinitialize PPG
 * @param void No arguments
 * @return void No return
 */
void PPG_Deinit(void)
{

}



void PPG_Process(void)
{
	//float32_t  *inputF32, *outputF32;


}



