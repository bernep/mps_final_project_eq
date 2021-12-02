/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "init.h"
#include "stm32f7xx_hal.h"
#include "uart.h"
#include "util.h"
#include "audio.h"
#include "bsp_override.h"


/* USER CODE BEGIN Includes */
/**
 * this software builds heavily on the work by https://community.st.com/people/Beaulier.Francois
 **/


#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"
#include <string.h>

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/
	Sys_Init();
	UI_Init();
	  Audio_Init();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */


  /* USER CODE BEGIN 2 */

  printf("Connected to STM32F769I-Discovery USART 1\r\n");
  printf("\r\n");

  //BSP_AUDIO_IN_Init(BSP_AUDIO_FREQUENCY_44K, DEFAULT_AUDIO_IN_BIT_RESOLUTION, DEFAULT_AUDIO_IN_CHANNEL_NBR);
  //BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 50, BSP_AUDIO_FREQUENCY_44K);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int fx_state;

  while (1)
  	 {
	  	  //handle UI updates
	  	  fx_state = UI_Handler();

  		 /* 1st or 2nd half of the record buffer ready for being copied
  		 to the Playback buffer */
  		 if (audio_rec_buffer_state != BUFFER_OFFSET_NONE)
  		 {
  			 /* Copy half of the record buffer to the playback buffer */
  			 if (audio_rec_buffer_state == BUFFER_OFFSET_HALF)
  			 {
  				 CopyBuffer(&audio_out_buffer[0], &audio_in_buffer[0], RECORD_BUFFER_SIZE / 2);
  			 } else {
  				 /* if(audio_rec_buffer_state == BUFFER_OFFSET_FULL)*/
  				 CopyBuffer(&audio_out_buffer[RECORD_BUFFER_SIZE / 2],
  							  &audio_in_buffer[RECORD_BUFFER_SIZE / 2],
  											RECORD_BUFFER_SIZE / 2);
  			 }
  			 /* Wait for next data */
  			 audio_rec_buffer_state = BUFFER_OFFSET_NONE;
  		 }
  		 if (audio_tx_buffer_state)
  		 {
  			 audio_tx_buffer_state = 0;
  		 }
  	 } // end while(1)
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/


/* USER CODE BEGIN 4 */
     /*
      * Cop the contents of the Record buffer to the
      * Playback buffer
      *
      * If you wanted to hook into the signal and do some
      * signal processing, here is a place where you have
      * both buffers available
      *
      */





 /**
  * @brief  Starts playing audio stream from a data buffer for a determined size.
  * @param  pBuffer: Pointer to the buffer
  * @param  Size: Number of audio data BYTES.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */







/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
