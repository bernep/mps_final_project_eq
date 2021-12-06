################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp.c \
../Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp_ptp.c 

OBJS += \
./Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp.o \
./Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp_ptp.o 

C_DEPS += \
./Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp.d \
./Drivers/STM32_USB_Host_Library/Class/MTP/Src/usbh_mtp_ptp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32_USB_Host_Library/Class/MTP/Src/%.o: ../Drivers/STM32_USB_Host_Library/Class/MTP/Src/%.c Drivers/STM32_USB_Host_Library/Class/MTP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Utilities/JPEG" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src/drivers" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/STM32_USB_Host_Library/Core/Inc" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/STM32_USB_Host_Library/Class/HID/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

