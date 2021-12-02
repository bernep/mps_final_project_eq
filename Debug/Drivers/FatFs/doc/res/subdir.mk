################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FatFs/doc/res/app1.c \
../Drivers/FatFs/doc/res/app2.c \
../Drivers/FatFs/doc/res/app3.c \
../Drivers/FatFs/doc/res/app4.c 

OBJS += \
./Drivers/FatFs/doc/res/app1.o \
./Drivers/FatFs/doc/res/app2.o \
./Drivers/FatFs/doc/res/app3.o \
./Drivers/FatFs/doc/res/app4.o 

C_DEPS += \
./Drivers/FatFs/doc/res/app1.d \
./Drivers/FatFs/doc/res/app2.d \
./Drivers/FatFs/doc/res/app3.d \
./Drivers/FatFs/doc/res/app4.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FatFs/doc/res/%.o: ../Drivers/FatFs/doc/res/%.c Drivers/FatFs/doc/res/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Utilities/JPEG" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

