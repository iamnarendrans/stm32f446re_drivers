/*
 * 008i2c_master_tx_testing.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Narendran Srinivasan
 */
#include "stm32f446xx.h"
#include <stdio.h>

#define SLAVE_ADDR	0x68
#define MY_ADDR		SLAVE_ADDR

uint32_t data_len = 0;
uint8_t CommandCode;


void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

I2C_Handle_t I2C1Handle;
uint8_t tx_buf[32] = "HiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHi";

/*
 * PB6 - SCL
 * PB9 - SDA
 * Alternate Function mode - 4
 */


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
	// initialise_monitor_handles();
	// printf("Application is running\n");

	data_len = strlen((char*)tx_buf);

	GPIO_ButtonInit();
	// I2C Gpio Inits
	I2C1_GPIOInits();

	// I2C1 Init
	I2C1_Inits();

	// Enable I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// Ack bit is made 1 after PE = 1 [ After Enabling a peripheral]
	I2C_ManageAcking(I2C1, I2C_ACK_EN);

	// I2C IRQ Configurations
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);
	I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

	// Configure IRQ priority number if more number of interrupts


	while(1);


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


	static uint32_t cnt = 0;
	static uint32_t w_ptr = 0;



	if(AppEvent == I2C_ERROR_AF)
	{
		//This will happen during slave transmitting data to master .
		// slave should understand master needs no more data
		//slave concludes end of Tx


		//if the current active code is 0x52 then dont invalidate
		if(! (CommandCode == 0x52))
			CommandCode = 0XFF;

		//reset the cnt variable because its end of transmission
		cnt = 0;

		//Slave concludes it sent all the bytes when w_ptr reaches data_len
		if(w_ptr >= (data_len))
		{
			w_ptr=0;
			CommandCode = 0xff;
		}

	}else if (AppEvent == I2C_EV_STOP)
	{
		//This will happen during end slave reception
		//slave concludes end of Rx

		cnt = 0;

	}else if (AppEvent == I2C_EV_DATA_REQ)
	{
		//Master is requesting for the data . send data
		if(CommandCode == 0x51)
		{
			//Here we are sending 4 bytes of length information
			I2C_SlaveSendData(I2C1,((data_len >> ((cnt%4) * 8)) & 0xFF));
		    cnt++;
		}else if (CommandCode == 0x52)
		{
			//sending Tx_buf contents indexed by w_ptr variable
			I2C_SlaveSendData(I2C1,tx_buf[w_ptr++]);
		}
	}else if (AppEvent == I2C_EV_DATA_RCV)
	{
		//Master has sent command code, read it
		 CommandCode = I2C_SlaveReceiveData(I2C1);

	}
}
