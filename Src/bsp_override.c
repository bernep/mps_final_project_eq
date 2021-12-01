/*
 * bsp_override.c
 *
 *  Created on: Nov 29, 2021
 *      Author: mchonaker
 */

#include "bsp_override.h"

static void SAIx_In_Init(uint32_t AudioFreq)
     {
         /* Initialize SAI1 block A in MASTER TX */
         /* Initialize the haudio_out_sai Instance parameter */
         haudio_out_sai.Instance = AUDIO_OUT_SAIx;

         /* Disable SAI peripheral to allow access to SAI internal registers */
         __HAL_SAI_DISABLE(&haudio_out_sai);

         /* Configure SAI_Block_x */
         haudio_out_sai.Init.MonoStereoMode = SAI_STEREOMODE;
         haudio_out_sai.Init.AudioFrequency = AudioFreq;
         haudio_out_sai.Init.AudioMode      = SAI_MODEMASTER_TX;
         haudio_out_sai.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
         haudio_out_sai.Init.Protocol       = SAI_FREE_PROTOCOL;
         haudio_out_sai.Init.DataSize       = SAI_DATASIZE_16;
         haudio_out_sai.Init.FirstBit       = SAI_FIRSTBIT_MSB;
         haudio_out_sai.Init.ClockStrobing  = SAI_CLOCKSTROBING_FALLINGEDGE;
         haudio_out_sai.Init.Synchro        = SAI_ASYNCHRONOUS;
         haudio_out_sai.Init.OutputDrive    = SAI_OUTPUTDRIVE_ENABLE;
         haudio_out_sai.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
         haudio_out_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
         haudio_out_sai.Init.CompandingMode = SAI_NOCOMPANDING;
         haudio_out_sai.Init.TriState       = SAI_OUTPUT_NOTRELEASED;
         haudio_out_sai.Init.Mckdiv         = 0;

         /* Configure SAI_Block_x Frame */
         haudio_out_sai.FrameInit.FrameLength       = 64;
         haudio_out_sai.FrameInit.ActiveFrameLength = 32;
         haudio_out_sai.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
         haudio_out_sai.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
         haudio_out_sai.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

         /* Configure SAI Block_x Slot */
         haudio_out_sai.SlotInit.FirstBitOffset = 0;
         haudio_out_sai.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
         haudio_out_sai.SlotInit.SlotNumber     = 4;
         haudio_out_sai.SlotInit.SlotActive     = CODEC_AUDIOFRAME_SLOT_0123;

         HAL_SAI_Init(&haudio_out_sai);



         /* Initialize SAI1 block B in SLAVE RX synchronous from SAI1 block A */
         /* Initialize the haudio_in_sai Instance parameter */
         haudio_in_sai.Instance = AUDIO_IN_SAIx;

         /* Disable SAI peripheral to allow access to SAI internal registers */
         __HAL_SAI_DISABLE(&haudio_in_sai);

         /* Configure SAI_Block_x */
         haudio_in_sai.Init.MonoStereoMode = SAI_STEREOMODE;
         haudio_in_sai.Init.AudioFrequency = AudioFreq;
         haudio_in_sai.Init.AudioMode      = SAI_MODESLAVE_RX;
         haudio_in_sai.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
         haudio_in_sai.Init.Protocol       = SAI_FREE_PROTOCOL;
         haudio_in_sai.Init.DataSize       = SAI_DATASIZE_16;
         haudio_in_sai.Init.FirstBit       = SAI_FIRSTBIT_MSB;
         haudio_in_sai.Init.ClockStrobing  = SAI_CLOCKSTROBING_FALLINGEDGE;
         haudio_in_sai.Init.Synchro        = SAI_SYNCHRONOUS;
         haudio_in_sai.Init.OutputDrive    = SAI_OUTPUTDRIVE_DISABLE;
         haudio_in_sai.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
         haudio_in_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
         haudio_in_sai.Init.CompandingMode = SAI_NOCOMPANDING;
         haudio_in_sai.Init.TriState       = SAI_OUTPUT_RELEASED;
         haudio_in_sai.Init.Mckdiv         = 0;

         /* Configure SAI_Block_x Frame */
         haudio_in_sai.FrameInit.FrameLength       = 64;
         haudio_in_sai.FrameInit.ActiveFrameLength = 32;
         haudio_in_sai.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
         haudio_in_sai.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
         haudio_in_sai.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

         /* Configure SAI Block_x Slot */
         haudio_in_sai.SlotInit.FirstBitOffset = 0;
         haudio_in_sai.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
         haudio_in_sai.SlotInit.SlotNumber     = 4;
         haudio_in_sai.SlotInit.SlotActive     = CODEC_AUDIOFRAME_SLOT_0123;

         HAL_SAI_Init(&haudio_in_sai);

         /* Enable SAI peripheral */
         __HAL_SAI_ENABLE(&haudio_in_sai);

         /* Enable SAI peripheral to generate MCLK */
         __HAL_SAI_ENABLE(&haudio_out_sai);
     }


     /**
       * @brief  Deinitializes the output Audio Codec audio interface (SAI).
       * @retval None
       */
     static void SAIx_In_DeInit(void)
     {
         /* Initialize the haudio_in_sai Instance parameter */
         haudio_in_sai.Instance = AUDIO_IN_SAIx;
         haudio_out_sai.Instance = AUDIO_OUT_SAIx;
         /* Disable SAI peripheral */
         __HAL_SAI_DISABLE(&haudio_in_sai);

         HAL_SAI_DeInit(&haudio_in_sai);
         HAL_SAI_DeInit(&haudio_out_sai);
     }


     /**
       * @brief  Initializes SAI Audio IN MSP.
       * @param  hsai: SAI handle
       * @retval None
       */
     static void SAI_AUDIO_IN_MspInit(SAI_HandleTypeDef *hsai, void *Params)
     {
         static DMA_HandleTypeDef hdma_sai_rx;
         GPIO_InitTypeDef  gpio_init_structure;

         /* Enable SAI clock */
         AUDIO_IN_SAIx_CLK_ENABLE();

         /* Enable SD GPIO clock */
         AUDIO_IN_SAIx_SD_ENABLE();
         /* CODEC_SAI pin configuration: SD pin */
         gpio_init_structure.Pin = AUDIO_IN_SAIx_SD_PIN;
         gpio_init_structure.Mode = GPIO_MODE_AF_PP;
         gpio_init_structure.Pull = GPIO_NOPULL;
         gpio_init_structure.Speed = GPIO_SPEED_FAST;
         gpio_init_structure.Alternate = AUDIO_IN_SAIx_AF;
         HAL_GPIO_Init(AUDIO_IN_SAIx_SD_GPIO_PORT, &gpio_init_structure);

         /* Enable Audio INT GPIO clock */
         AUDIO_IN_INT_GPIO_ENABLE();
         /* Audio INT pin configuration: input */
         gpio_init_structure.Pin = AUDIO_IN_INT_GPIO_PIN;
         gpio_init_structure.Mode = GPIO_MODE_INPUT;
         gpio_init_structure.Pull = GPIO_NOPULL;
         gpio_init_structure.Speed = GPIO_SPEED_FAST;
         HAL_GPIO_Init(AUDIO_IN_INT_GPIO_PORT, &gpio_init_structure);

         /* Enable the DMA clock */
         AUDIO_IN_SAIx_DMAx_CLK_ENABLE();

         if (hsai->Instance == AUDIO_IN_SAIx)
         {
             /* Configure the hdma_sai_rx handle parameters */
             hdma_sai_rx.Init.Channel             = AUDIO_IN_SAIx_DMAx_CHANNEL;
             hdma_sai_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
             hdma_sai_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
             hdma_sai_rx.Init.MemInc              = DMA_MINC_ENABLE;
             hdma_sai_rx.Init.PeriphDataAlignment = AUDIO_IN_SAIx_DMAx_PERIPH_DATA_SIZE;
             hdma_sai_rx.Init.MemDataAlignment    = AUDIO_IN_SAIx_DMAx_MEM_DATA_SIZE;
             hdma_sai_rx.Init.Mode                = DMA_CIRCULAR;
             hdma_sai_rx.Init.Priority            = DMA_PRIORITY_HIGH;
             hdma_sai_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
             hdma_sai_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
             hdma_sai_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
             hdma_sai_rx.Init.PeriphBurst         = DMA_MBURST_SINGLE;

             hdma_sai_rx.Instance = AUDIO_IN_SAIx_DMAx_STREAM;

             /* Associate the DMA handle */
             __HAL_LINKDMA(hsai, hdmarx, hdma_sai_rx);

             /* Deinitialize the Stream for new transfer */
             HAL_DMA_DeInit(&hdma_sai_rx);

             /* Configure the DMA Stream */
             HAL_DMA_Init(&hdma_sai_rx);
         }

         /* SAI DMA IRQ Channel configuration */
         HAL_NVIC_SetPriority(AUDIO_IN_SAIx_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
         HAL_NVIC_EnableIRQ(AUDIO_IN_SAIx_DMAx_IRQ);

         /* Audio INT IRQ Channel configuration */
         HAL_NVIC_SetPriority(AUDIO_IN_INT_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
         HAL_NVIC_EnableIRQ(AUDIO_IN_INT_IRQ);
     }



uint8_t BSP_AUDIO_IN_OUT_Init(uint32_t AudioFreq)
     {
         uint8_t ret = AUDIO_ERROR;

         /* Disable SAI */
         SAIx_In_DeInit();

         /* PLL clock is set depending by the AudioFreq (44.1khz vs 48khz groups) */
         BSP_AUDIO_OUT_ClockConfig(&haudio_in_sai, AudioFreq, NULL);
         haudio_out_sai.Instance = AUDIO_OUT_SAIx;
         haudio_in_sai.Instance = AUDIO_IN_SAIx;
         if (HAL_SAI_GetState(&haudio_in_sai) == HAL_SAI_STATE_RESET)
         {
             BSP_AUDIO_OUT_MspInit(&haudio_out_sai, NULL);
             SAI_AUDIO_IN_MspInit(&haudio_in_sai, NULL);
         }


         SAIx_In_Init(AudioFreq); // inclu déja le code de SAIx_Out_Init()


         if ((wm8994_drv.ReadID(AUDIO_I2C_ADDRESS)) == WM8994_ID)
         {
             /* Reset the Codec Registers */
             wm8994_drv.Reset(AUDIO_I2C_ADDRESS);
             /* Initialize the audio driver structure */
             audio_drv = &wm8994_drv;
             ret = AUDIO_OK;
         } else {
             ret = AUDIO_ERROR;
         }

         if (ret == AUDIO_OK)
         {
             /* Initialize the codec internal registers */
             audio_drv->Init(AUDIO_I2C_ADDRESS, INPUT_DEVICE_ANALOG_MIC | OUTPUT_DEVICE_HEADPHONE , 100, AudioFreq);
         }

         /* Return AUDIO_OK when all operations are correctly done */
         return ret;
     }


     uint8_t _BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size)
     {
         /* Call the audio Codec Play function */
         if (audio_drv->Play(AUDIO_I2C_ADDRESS, (uint16_t *)pBuffer, Size) != 0)
         {
             return AUDIO_ERROR;
         }
         else
         {
             /* Update the Media layer and enable it for play */
             //if (HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*) pBuffer, DMA_MAX(Size / AUDIODATA_SIZE)) !=  HAL_OK)
             if (HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*) pBuffer, Size) !=  HAL_OK)
                 return AUDIO_ERROR;
             return AUDIO_OK;
         }
     }
