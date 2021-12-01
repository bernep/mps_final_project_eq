################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.c 

OBJS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.o 

C_DEPS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F769I-Discovery/%.o: ../Drivers/BSP/STM32F769I-Discovery/%.c Drivers/BSP/STM32F769I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F769I-Discovery -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

