/*
 * 008i2c_master_tx_testing.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Narendran Srinivasan
 */
#include "stm32f446xx.h"

#define MY_ADDR		0x61
#define SLAVE_ADDR	0x68

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

/*
 * PB6 - SCL
 * PB9 - SDA
 * Alternate Function mode - 4
 */
I2C_Handle_t I2C1Handle;


void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_6;
	GPIO_Init(&I2CPins);

	// SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_9;
	GPIO_Init(&I2CPins);
}

void I2C1_Inits(void)
{

	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckCtrl = I2C_ACK_EN;
	I2C1Handle.I2C_Config.I2C_DeviceAddr = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

	GPIO_Init(&GPIOBtn);

}

int main(void)
{

	uint8_t some_data[] = "We are testing I2C master Tx\n";

	GPIO_ButtonInit();
	// I2C Gpio Inits
	I2C1_GPIOInits();

	// I2C1 Init
	I2C1_Inits();

	// Enable I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NUM_13));

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		// Send some data to the arduino slave
		I2C_MasterSendData(&I2C1Handle, some_data, strlen((char*)some_data), SLAVE_ADDR, I2C_ENABLE_SR);
	}


	return 0;
}
