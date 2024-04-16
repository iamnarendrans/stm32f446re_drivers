################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../helper/Src/user_helper.c 

OBJS += \
./helper/Src/user_helper.o 

C_DEPS += \
./helper/Src/user_helper.d 


# Each subdirectory must supply rules for building sources it contributes
helper/Src/%.o helper/Src/%.su helper/Src/%.cyclo: ../helper/Src/%.c helper/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Middlewares/Third_Party/FatFs/src -I"C:/Users/iamna/STM32CubeIDE/HAL_Workspace/Development/helper/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-helper-2f-Src

clean-helper-2f-Src:
	-$(RM) ./helper/Src/user_helper.cyclo ./helper/Src/user_helper.d ./helper/Src/user_helper.o ./helper/Src/user_helper.su

.PHONY: clean-helper-2f-Src

