################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Kalama/Src/amg8833.c \
../Kalama/Src/debug.c \
../Kalama/Src/i2c.c 

OBJS += \
./Kalama/Src/amg8833.o \
./Kalama/Src/debug.o \
./Kalama/Src/i2c.o 

C_DEPS += \
./Kalama/Src/amg8833.d \
./Kalama/Src/debug.d \
./Kalama/Src/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Kalama/Src/%.o Kalama/Src/%.su Kalama/Src/%.cyclo: ../Kalama/Src/%.c Kalama/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"D:/WorkSpace/STM32CUBEIDE/Kalama/Kalama/Inc" -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Kalama-2f-Src

clean-Kalama-2f-Src:
	-$(RM) ./Kalama/Src/amg8833.cyclo ./Kalama/Src/amg8833.d ./Kalama/Src/amg8833.o ./Kalama/Src/amg8833.su ./Kalama/Src/debug.cyclo ./Kalama/Src/debug.d ./Kalama/Src/debug.o ./Kalama/Src/debug.su ./Kalama/Src/i2c.cyclo ./Kalama/Src/i2c.d ./Kalama/Src/i2c.o ./Kalama/Src/i2c.su

.PHONY: clean-Kalama-2f-Src

