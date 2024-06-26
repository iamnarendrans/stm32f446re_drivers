/*
 * 008i2c_master_tx_testing.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Narendran Srinivasan
 */
#include "stm32f446xx.h"
#include <stdio.h>


extern initialise_monitor_handles();

#define MY_ADDR		0x61
#define SLAVE_ADDR	0x68

// Global flag
uint8_t rxComplete	= RESET;

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

	uint8_t recv_buffer[32];
	uint8_t commandcode;
	uint8_t length;

	// initialise_monitor_handles();
	// printf("Application is running\n");

	GPIO_ButtonInit();
	// I2C Gpio Inits
	I2C1_GPIOInits();

	// I2C1 Init
	I2C1_Inits();

	// I2C IRQ Configurations
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	// Configure IRQ priority number if more number of interrupts

	// Enable I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// Ack bit is made 1 after PE = 1 [ After Enabling a peripheral]
	I2C_ManageAcking(I2C1, I2C_ACK_EN);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NUM_13));

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		// receive the data from arduino slave
		commandcode = 0x51;

		while(I2C_MasterSendDataIT(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY);

		while(I2C_MasterReceiveDataIT(&I2C1Handle, &length, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY);

		commandcode = 0x52;

		while(I2C_MasterSendDataIT(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY);

		while(I2C_MasterReceiveDataIT(&I2C1Handle, recv_buffer, length, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY);

		rxComplete = RESET;

		// Wait until the rx completesf
		while(rxComplete != SET);

		recv_buffer[length+1] = '\0';

		 printf("DATA: %s", recv_buffer);

		 rxComplete = RESET;


	}


	return 0;
}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}
void I2C1_ER_IRQHandler(void)
{
	I2C_ERR_IRQHandling(&I2C1Handle);
}


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent)
{
	if(AppEvent == I2C_EV_TX_CMPLT)
	{
		printf("Tx is completed\n");
	}
	else if(AppEvent == I2C_EV_RX_CMPLT)
	{
		printf("Rx is completed\n");
		rxComplete = SET;
	}
	else if(AppEvent == I2C_ERROR_AF)
	{
		printf("Error: ACK Failure");
		// In master ack failure happens when slave fails to send ack for the byte
		// sent from the master
		I2C_CloseSendData(pI2CHandle);

		// Generate the stop condition to release the bus
		I2C_GenerateStopCondition(I2C1);

		// Hang in infinite loop
		while(1);
	}
}
