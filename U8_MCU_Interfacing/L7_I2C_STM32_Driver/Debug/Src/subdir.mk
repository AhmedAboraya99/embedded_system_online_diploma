################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/EXTI" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/HAL/I2C_EEPROM" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/GPIO" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/I2C" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/RCC" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/SPI" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

