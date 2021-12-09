################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USBConf/Src/audio_mic_node.c \
../USBConf/Src/audio_speaker_node.c \
../USBConf/Src/stm32f7xx_hal_msp.c \
../USBConf/Src/usbd_conf.c \
../USBConf/Src/usbd_desc.c 

OBJS += \
./USBConf/Src/audio_mic_node.o \
./USBConf/Src/audio_speaker_node.o \
./USBConf/Src/stm32f7xx_hal_msp.o \
./USBConf/Src/usbd_conf.o \
./USBConf/Src/usbd_desc.o 

C_DEPS += \
./USBConf/Src/audio_mic_node.d \
./USBConf/Src/audio_speaker_node.d \
./USBConf/Src/stm32f7xx_hal_msp.d \
./USBConf/Src/usbd_conf.d \
./USBConf/Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
USBConf/Src/%.o: ../USBConf/Src/%.c USBConf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DUSE_HAL_DRIVER -DUSE_AUDIO_DFSDM_MEMS_MIC=1 -DSTM32F769xx -DUSE_STM32F769I_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -DUSE_USB_FS_INTO_HS -DUSE_USB_AUDIO_RECORDING=1 -DUSE_USB_AUDIO_PLAYBACK=1 -DUSB_DEVICE_ENABLE '-D__packed="__attribute__((__packed__))"' -c -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Utilities/JPEG" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src/drivers" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/USBConf/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Common/Streaming/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/BSP/Components/wm8994_ex" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/STM32_USB_Device_Library/Class/AUDIO_10/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/BSP/STM32F769I-Discovery" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/CMSIS/Include" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/BSP/Components/Common" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

