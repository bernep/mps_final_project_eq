################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FatFs/src/option/cc932.c \
../Drivers/FatFs/src/option/cc936.c \
../Drivers/FatFs/src/option/cc949.c \
../Drivers/FatFs/src/option/cc950.c \
../Drivers/FatFs/src/option/ccsbcs.c \
../Drivers/FatFs/src/option/syscall.c \
../Drivers/FatFs/src/option/unicode.c 

OBJS += \
./Drivers/FatFs/src/option/cc932.o \
./Drivers/FatFs/src/option/cc936.o \
./Drivers/FatFs/src/option/cc949.o \
./Drivers/FatFs/src/option/cc950.o \
./Drivers/FatFs/src/option/ccsbcs.o \
./Drivers/FatFs/src/option/syscall.o \
./Drivers/FatFs/src/option/unicode.o 

C_DEPS += \
./Drivers/FatFs/src/option/cc932.d \
./Drivers/FatFs/src/option/cc936.d \
./Drivers/FatFs/src/option/cc949.d \
./Drivers/FatFs/src/option/cc950.d \
./Drivers/FatFs/src/option/ccsbcs.d \
./Drivers/FatFs/src/option/syscall.d \
./Drivers/FatFs/src/option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FatFs/src/option/%.o: ../Drivers/FatFs/src/option/%.c Drivers/FatFs/src/option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/Utilities/JPEG" -I"C:/Users/mchonaker/Documents/Projects/RPI-CLASSES/FALL 2021/ECSE 4790/workspace/mps_final_project_eq/Drivers/FatFs/src" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

