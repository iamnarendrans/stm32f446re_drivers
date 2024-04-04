################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f446xx_adc_driver.c \
../drivers/Src/stm32f446xx_clock_driver.c \
../drivers/Src/stm32f446xx_gpio_driver.c \
../drivers/Src/stm32f446xx_spi_driver.c \
../drivers/Src/stm32f446xx_usart_driver.c \
../drivers/Src/stm32f666xx_i2c_driver.c 

OBJS += \
./drivers/Src/stm32f446xx_adc_driver.o \
./drivers/Src/stm32f446xx_clock_driver.o \
./drivers/Src/stm32f446xx_gpio_driver.o \
./drivers/Src/stm32f446xx_spi_driver.o \
./drivers/Src/stm32f446xx_usart_driver.o \
./drivers/Src/stm32f666xx_i2c_driver.o 

C_DEPS += \
./drivers/Src/stm32f446xx_adc_driver.d \
./drivers/Src/stm32f446xx_clock_driver.d \
./drivers/Src/stm32f446xx_gpio_driver.d \
./drivers/Src/stm32f446xx_spi_driver.d \
./drivers/Src/stm32f446xx_usart_driver.d \
./drivers/Src/stm32f666xx_i2c_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su drivers/Src/%.cyclo: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/iamna/STM32CubeIDE/workspace_1.14.0/stm32f446xx_drivers/drivers/Inc" -I"C:/Users/iamna/STM32CubeIDE/workspace_1.14.0/stm32f446xx_drivers/libraries/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/stm32f446xx_adc_driver.cyclo ./drivers/Src/stm32f446xx_adc_driver.d ./drivers/Src/stm32f446xx_adc_driver.o ./drivers/Src/stm32f446xx_adc_driver.su ./drivers/Src/stm32f446xx_clock_driver.cyclo ./drivers/Src/stm32f446xx_clock_driver.d ./drivers/Src/stm32f446xx_clock_driver.o ./drivers/Src/stm32f446xx_clock_driver.su ./drivers/Src/stm32f446xx_gpio_driver.cyclo ./drivers/Src/stm32f446xx_gpio_driver.d ./drivers/Src/stm32f446xx_gpio_driver.o ./drivers/Src/stm32f446xx_gpio_driver.su ./drivers/Src/stm32f446xx_spi_driver.cyclo ./drivers/Src/stm32f446xx_spi_driver.d ./drivers/Src/stm32f446xx_spi_driver.o ./drivers/Src/stm32f446xx_spi_driver.su ./drivers/Src/stm32f446xx_usart_driver.cyclo ./drivers/Src/stm32f446xx_usart_driver.d ./drivers/Src/stm32f446xx_usart_driver.o ./drivers/Src/stm32f446xx_usart_driver.su ./drivers/Src/stm32f666xx_i2c_driver.cyclo ./drivers/Src/stm32f666xx_i2c_driver.d ./drivers/Src/stm32f666xx_i2c_driver.o ./drivers/Src/stm32f666xx_i2c_driver.su

.PHONY: clean-drivers-2f-Src

