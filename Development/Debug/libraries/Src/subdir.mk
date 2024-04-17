################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/Src/SD.c \
../libraries/Src/user_dsp.c \
../libraries/Src/user_helper.c \
../libraries/Src/user_math.c 

OBJS += \
./libraries/Src/SD.o \
./libraries/Src/user_dsp.o \
./libraries/Src/user_helper.o \
./libraries/Src/user_math.o 

C_DEPS += \
./libraries/Src/SD.d \
./libraries/Src/user_dsp.d \
./libraries/Src/user_helper.d \
./libraries/Src/user_math.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Src/%.o libraries/Src/%.su libraries/Src/%.cyclo: ../libraries/Src/%.c libraries/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Middlewares/Third_Party/FatFs/src -I"C:/Users/iamna/STM32CubeIDE/Development/Development/libraries/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-libraries-2f-Src

clean-libraries-2f-Src:
	-$(RM) ./libraries/Src/SD.cyclo ./libraries/Src/SD.d ./libraries/Src/SD.o ./libraries/Src/SD.su ./libraries/Src/user_dsp.cyclo ./libraries/Src/user_dsp.d ./libraries/Src/user_dsp.o ./libraries/Src/user_dsp.su ./libraries/Src/user_helper.cyclo ./libraries/Src/user_helper.d ./libraries/Src/user_helper.o ./libraries/Src/user_helper.su ./libraries/Src/user_math.cyclo ./libraries/Src/user_math.d ./libraries/Src/user_math.o ./libraries/Src/user_math.su

.PHONY: clean-libraries-2f-Src

