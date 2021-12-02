################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/audio.c \
../Src/bsp_override.c \
../Src/eq_ui.c \
../Src/init.c \
../Src/main.c \
../Src/stm32f7xx_it.c \
../Src/system_stm32f7xx.c \
../Src/uart.c \
../Src/util.c 

OBJS += \
./Src/audio.o \
./Src/bsp_override.o \
./Src/eq_ui.o \
./Src/init.o \
./Src/main.o \
./Src/stm32f7xx_it.o \
./Src/system_stm32f7xx.o \
./Src/uart.o \
./Src/util.o 

C_DEPS += \
./Src/audio.d \
./Src/bsp_override.d \
./Src/eq_ui.d \
./Src/init.d \
./Src/main.d \
./Src/stm32f7xx_it.d \
./Src/system_stm32f7xx.d \
./Src/uart.d \
./Src/util.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Utilities/JPEG" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src/drivers" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

