################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MIDWARE/FATFS_SD/FATFS_SD.c 

OBJS += \
./MIDWARE/FATFS_SD/FATFS_SD.o 

C_DEPS += \
./MIDWARE/FATFS_SD/FATFS_SD.d 


# Each subdirectory must supply rules for building sources it contributes
MIDWARE/FATFS_SD/%.o MIDWARE/FATFS_SD/%.su MIDWARE/FATFS_SD/%.cyclo: ../MIDWARE/FATFS_SD/%.c MIDWARE/FATFS_SD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -IC:/Users/iamna/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Middlewares/Third_Party/FatFs/src -I"C:/Users/iamna/STM32CubeIDE/HAL_Workspace/Development/libraries/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MIDWARE-2f-FATFS_SD

clean-MIDWARE-2f-FATFS_SD:
	-$(RM) ./MIDWARE/FATFS_SD/FATFS_SD.cyclo ./MIDWARE/FATFS_SD/FATFS_SD.d ./MIDWARE/FATFS_SD/FATFS_SD.o ./MIDWARE/FATFS_SD/FATFS_SD.su

.PHONY: clean-MIDWARE-2f-FATFS_SD

