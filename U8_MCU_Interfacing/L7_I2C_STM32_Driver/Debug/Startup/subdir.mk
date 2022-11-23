################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c6tx.s 

OBJS += \
./Startup/startup_stm32f103c6tx.o 

S_DEPS += \
./Startup/startup_stm32f103c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -mcpu=cortex-m3 -g3 -DDEBUG -c -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/EXTI" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/HAL/I2C_EEPROM" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/Inc" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/GPIO" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/I2C" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/RCC" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/SPI" -I"E:/Work/Embedded systems/Diploma/embedded_system_online_diploma/U8_MCU_Interfacing/L6_I2C_STM32_Driver/STM32F103C6_Drivers/UART" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c6tx.d ./Startup/startup_stm32f103c6tx.o

.PHONY: clean-Startup

