/*
 * stm32f446xx.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Narendran Srinivasan
 */

#ifndef INC_STM32F466XX_H_
#define INC_STM32F466XX_H_

#include <stdint.h>
#include <stddef.h>

#define __vo volatile
#define __weak	__attribute__((weak))

/**********************************************START: PROCESSOR SPECIFIC DETAILS***********************************************************
 * 									   ARM Cortex Mx Processor NVIC register Addresses
 ******************************************************************************************************************************************/

#define NVIC_ISER0			((__vo uint32_t*)0xE000E100)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER1			((__vo uint32_t*)0xE000E104)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER2			((__vo uint32_t*)0xE000E108)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER3			((__vo uint32_t*)0xE000E10C)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER4			((__vo uint32_t*)0xE000E110)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER5			((__vo uint32_t*)0xE000E114)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER6			((__vo uint32_t*)0xE000E118)		/*!Interrupt Set-enable Register*/
#define NVIC_ISER7			((__vo uint32_t*)0xE000E11C)		/*!Interrupt Set-enable Register*/


#define NVIC_ICER0			((__vo uint32_t*)0xE000E180)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER1			((__vo uint32_t*)0xE000E184)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER2			((__vo uint32_t*)0xE000E188)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER3			((__vo uint32_t*)0xE000E18C)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER4			((__vo uint32_t*)0xE000E190)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER5			((__vo uint32_t*)0xE000E194)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER6			((__vo uint32_t*)0xE000E198)		/*!Interrupt Clear-enable Register*/
#define NVIC_ICER7			((__vo uint32_t*)0xE000E19C)		/*!Interrupt Clear-enable Register*/


#define NVIC_ISPR0			((__vo uint32_t*)0xE000E200)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR1			((__vo uint32_t*)0xE000E204)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR2			((__vo uint32_t*)0xE000E208)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR3			((__vo uint32_t*)0xE000E20C)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR4			((__vo uint32_t*)0xE000E210)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR5			((__vo uint32_t*)0xE000E214)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR6			((__vo uint32_t*)0xE000E218)		/*!Interrupt Set-pending Register*/
#define NVIC_ISPR7			((__vo uint32_t*)0xE000E21C)		/*!Interrupt Set-pending Register*/


#define NVIC_ICPR0			((__vo uint32_t*)0xE000E280)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR1			((__vo uint32_t*)0xE000E284)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR2			((__vo uint32_t*)0xE000E288)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR3			((__vo uint32_t*)0xE000E28C)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR4			((__vo uint32_t*)0xE000E290)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR5			((__vo uint32_t*)0xE000E294)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR6			((__vo uint32_t*)0xE000E298)		/*!Interrupt Clear-pending Register*/
#define NVIC_ICPR7			((__vo uint32_t*)0xE000E29C)		/*!Interrupt Clear-pending Register*/



#define NVIC_PR_BASEADDR	((__vo uint32_t*)0xE000E400)		/*!Interrupt Priority Registers 0*/

#define NO_PR_BITS_IMPLEMENTED		4							/*! Number of priority bits implemented in STM, will differ for other MCUs*/


/**********************************************END: PROCESSOR SPECIFIC DETAILS*************************************************************/

/**********************************************START: BASE ADDRESS OF THE PERI*************************************************************
 *									   BASE ADDRESS OF THE FLASH, SRAM & PERIPHERALS
 ******************************************************************************************************************************************/

/*
 * Base address of the flash and SRAM memories
 */

#define FLASH_BASEADDR				0x08000000U 			/*! Base address of the flash memory*/
#define SRAM1_BASEADDR				0x20000000U 			/*! Base address of the SRAM1 memory*/
#define SRAM2_BASEADDR				0x20001C00U				/*! Base address of the SRAM2 memory*/
#define ROM_BASEADDR				0x1FFF0000U 			/*! Base address of the System memory*/
#define OTP_BASEADDR				0x1FFF7800U				/*! Base address of the OTP AREA*/
#define SRAM						SRAM1_BASEADDR		 	/*! Base address of the SRAM memory*/

/*
 * AHBx and APBx Bus peripheral base address
 */

#define PERIPH_BASEADDR				0x40000000U 		 /*! Base address of the Peripheral*/
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR		 /*! Base address of the APB1 bus*/
#define	APB2PERIPH_BASEADDR			0x40010000U			 /*! Base address of the APB2 bus*/
#define	AHB1PERIPH_BASEADDR			0x40020000U 		 /*! Base address of the AHB1 bus*/
#define	AHB2PERIPH_BASEADDR			0x50000000U			 /*! Base address of the AHB2 bus*/
#define	AHB3PERIPH_BASEADDR			0xA0000000U			 /*! Base address of the AHB23 bus*/


/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */

#define CRC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3000)  /*! Base address of the CRC*/
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)  /*! Base address of the RCC peripheral*/
#define FLASH_INTER_BASEADDR		(AHB1PERIPH_BASEADDR + 0x3C00)  /*! Base address of the Flash Interface*/
#define BKPSRAM_BASEADDR			(AHB1PERIPH_BASEADDR + 0x4000)  /*! Base address of the BKPSRAM*/
#define DMA1_BASEADDR				(AHB1PERIPH_BASEADDR + 0x6000)  /*! Base address of the DMA1 controller*/
#define DMA2_BASEADDR				(AHB1PERIPH_BASEADDR + 0x6400)  /*! Base address of the DMA2 controller*/
#define USB_OTG_HS_BASEADDR			(AHB1PERIPH_BASEADDR + 0x19C00) /*! Base address of the USBOTG HalfSpeed*/

/*
 * Base addresses of peripherals which are hanging on AHB2 bus
 */
#define USB_OTG_FS_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0000)  /*! Base address of the USBOTG FullSpeed*/
#define DCMI_BASEADDR				(AHB2PERIPH_BASEADDR + 0x50000) /*! Base address of the USBOTG FullSpeed*/


/*
 * Base addresses of peripherals which are hanging on AHB3 bus
 */
#define QUADSPI_BASEADDR			(AHB3PERIPH_BASEADDR + 0X1000)	/*! QUADSPI base address register*/
#define FMCCTRL_BASEADDR			(AHB3PERIPH_BASEADDR + 0X0000)	/*! Base address of the FMC Control*/

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */

/************************************************GPIO BASE ADDRESSES***********************************************************************/
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000) /*! Base address of the GPIOA PORT*/
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400) /*! Base address of the GPIOB PORT*/
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800) /*! Base address of the GPIOC PORT*/
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00) /*! Base address of the GPIOD PORT*/
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000) /*! Base address of the GPIOE PORT*/
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400) /*! Base address of the GPIOF PORT*/
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800) /*! Base address of the GPIOG PORT*/
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00) /*! Base address of the GPIOH PORT*/
/******************************************************************************************************************************************/


/*
 * Base addresses of peripherals which are hanging on APB bus
 */

/**********************************************TIMER BASE ADDRESSES************************************************************************/
#define TIM1_BASEADDR				(APB2PERIPH_BASEADDR + 0x0000)  /*! Base address of the TIMER1 */
#define TIM2_BASEADDR				(APB1PERIPH_BASEADDR + 0x0000)  /*! Base address of the TIMER2 */
#define TIM3_BASEADDR				(APB1PERIPH_BASEADDR + 0x0400)  /*! Base address of the TIMER3 */
#define TIM4_BASEADDR				(APB1PERIPH_BASEADDR + 0x0800)  /*! Base address of the TIMER4 */
#define TIM5_BASEADDR				(APB1PERIPH_BASEADDR + 0x0C00)  /*! Base address of the TIMER5 */
#define TIM6_BASEADDR				(APB1PERIPH_BASEADDR + 0x1000)  /*! Base address of the TIMER6 */
#define TIM7_BASEADDR				(APB1PERIPH_BASEADDR + 0x1400)  /*! Base address of the TIMER7 */
#define TIM8_BASEADDR				(APB2PERIPH_BASEADDR + 0x0400)  /*! Base address of the TIMER8 */
#define TIM9_BASEADDR				(APB2PERIPH_BASEADDR + 0x4000)  /*! Base address of the TIMER9 */
#define TIM10_BASEADDR				(APB2PERIPH_BASEADDR + 0x4400)  /*! Base address of the TIMER10 */
#define TIM11_BASEADDR				(APB2PERIPH_BASEADDR + 0x4800)  /*! Base address of the TIMER11 */
#define TIM12_BASEADDR				(APB1PERIPH_BASEADDR + 0x1800)  /*! Base address of the TIMER12 */
#define TIM13_BASEADDR				(APB1PERIPH_BASEADDR + 0x0C00)  /*! Base address of the TIMER13 */
#define TIM14_BASEADDR				(APB1PERIPH_BASEADDR + 0x2000)  /*! Base address of the TIMER14 */
#define RTC_BASEADDR				(APB1PERIPH_BASEADDR + 0x2800)  /*! Base address of the RTC TIMER */
/******************************************************************************************************************************************/

/**********************************************SPI BUS ADDRESSES***************************************************************************/
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)    /*! Base address of the SPI1 BUS */
#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)    /*! Base address of the SPI2 BUS */
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)    /*! Base address of the SPI3 BUS */
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR + 0x3400)    /*! Base address of the SPI4 BUS */
/******************************************************************************************************************************************/

/**********************************************I2S BUS ADDRESSES***************************************************************************/
#define I2S2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)    /*! Base address of the I2S2 BUS */
#define I2S3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)    /*! Base address of the I2S3 BUS */
/******************************************************************************************************************************************/

/**********************************************CAN BUS ADDRESSES***************************************************************************/
#define CAN1_BASEADDR				(APB1PERIPH_BASEADDR + 0X6400)    /*! Base address of the I2S2 BUS */
#define CAN2_BASEADDR				(APB1PERIPH_BASEADDR + 0X6800)    /*! Base address of the I2S3 BUS */
/******************************************************************************************************************************************/


/**********************************************I2C BUS ADDRESSES***************************************************************************/
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)    /*! Base address of the I2C1 BUS */
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)    /*! Base address of the I2C2 BUS */
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)    /*! Base address of the I2C3 BUS */
/******************************************************************************************************************************************/

/*************************************************ADC ADDRESSES****************************************************************************/
// #define ADC_BASEADDR				(APBPERIPH_BASEADDR + 0x12400)   /*! Base address of the ADC */
/******************************************************************************************************************************************/

/**********************************************USART ADDRESSES*****************************************************************************/
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)   /*! Base address of the USART1 */
#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)   /*! Base address of the USART2 */
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)   /*! Base address of the USART3 */
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)   /*! Base address of the UART4 */
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)   /*! Base address of the UART5 */
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)   /*! Base address of the USART6 */
/******************************************************************************************************************************************/

/**********************************************OTHER INTERRUPT ADDRESSES*******************************************************************/
#define WWDG_BASEADDR				(APB1PERIPH_BASEADDR + 0x2C00)   /*! Base address of the WATCHDOG */
#define IWDG_BASEADDR				(APB1PERIPH_BASEADDR + 0x3000)   /*! Base address of the IWDG */
#define USB_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)   /*! Base address of the USB */
#define PWR_BASEADDR				(APB1PERIPH_BASEADDR + 0x7000)   /*! Base address of the PWR */
#define DAC_BASEADDR				(APB1PERIPH_BASEADDR + 0X7400)	 /*! Base address of the DAC register */
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)   /*! Base address of the SYSTEMCONFIG */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)   /*! Base address of the EXTERNAL INTERRUPT HANDLERS */
#define SPDIF_RX_BASEADDR			(APB1PERIPH_BASEADDR + 0X4000)	 /*! Base address of the SPDIF Rx */
#define HDMI_CEC_BASEADDR			(APB1PERIPH_BASEADDR + 0X6C00)	 /*! Base address of the HDMI CEC */
#define ADC1_BASEADDR				(APB2PERIPH_BASEADDR + 0x2000)	 /*! Base address of the ADC1 */
#define ADC2_BASEADDR				(APB2PERIPH_BASEADDR + 0x2000)	 /*! Base address of the ADC2 */
#define ADC3_BASEADDR				(APB2PERIPH_BASEADDR + 0x2000)	 /*! Base address of the ADC3 */
#define SDMMC_BASEADDR				(APB2PERIPH_BASEADDR + 0x2C00)	 /*! Base address of the SDMMC */
#define SAI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x5800)	 /*! Base address of the SAI1 */
#define SAI2_BASEADDR				(APB2PERIPH_BASEADDR + 0x5C00)	 /*! Base address of the SAI2 */
/******************************************************************************************************************************************/
/**********************************************END: BASE ADDRESS OF THE PERI***************************************************************/

/**********************************************START: PERIPHERAL STRUCTURES****************************************************************
 *											PERIPHERAL DEFINITION STRUCTURES
 ******************************************************************************************************************************************/

/*
 * Note: Registers of peripherals are specific to MCU
 * e.g: Number of registers of SPI peripheral of STM32F446xx family of MCUs may be different(more or less)
 * Compared to number of registers of SPI peripheral of STM32Lx or STM32F4x family of MCUs
 * Please check your device RM
 */

/*
 * Peripheral Register definition structure for GPIO
 */
typedef struct{
	__vo uint32_t MODER;		/*!< GPIO Port Mode Register> 				Address offset: 0x00*/
	__vo uint32_t OTYPER;		/*!< GPIO Port Output Type > 				Address offset: 0x04*/
	__vo uint32_t OSPEEDR;		/*!< GPIO Port Speed Register> 				Address offset: 0x08*/
	__vo uint32_t PUPDR;		/*!< GPIO Port Pull-up/Pull-Down Register> 	Address offset: 0x0C*/
	__vo uint32_t IDR;			/*!< GPIO Port Input Data Register> 		Address offset: 0x10*/
	__vo uint32_t ODR;			/*!< GPIO Port Output Data Register> 		Address offset: 0x14*/
	__vo uint32_t BSRR;			/*!< GPIO Port Bit-Set/Reset Register> 		Address offset: 0x18*/
	__vo uint32_t LCKR;			/*!< GPIO Port Lock Config Register> 		Address offset: 0x1C*/
	__vo uint32_t AFR[2];		/*!< AFR[0] is AFRL | AFR[1] is AFRH		Address offset: 0x20 - 0x24*/
//	__vo uint32_t AFRL;			/*!< GPIO AF Low Register> 					Address offset: 0x20*/
//	__vo uint32_t AFRH;			/*!< GPIO AF High Register> 				Address offset: 0x24*/

}GPIO_RegDef_t;

/*
 * Peripheral Register definiton structure for SPIx
 */

typedef struct
{
	__vo uint32_t CR1;			/*! SPI Control Register 1					Address offset: 0x00*/
	__vo uint32_t CR2;			/*! SPI Control Register 2					Address offset: 0x04*/
	__vo uint32_t SR;			/*! SPI Status Register 					Address offset: 0x08*/
	__vo uint32_t DR;			/*! SPI Data Register 						Address offset: 0x0C*/
	__vo uint32_t CRCPR;		/*! SPI CRC Polynomial Register				Address offset: 0x10*/
	__vo uint32_t RXCRCR;		/*! SPI Rx CRC Polynomial Register			Address offset: 0x14*/
	__vo uint32_t TXCRCR;		/*! SPI Tx CRC Polynomial Register			Address offset: 0x18*/
	__vo uint32_t I2SCFRG;		/*! SPI I2s Configuration Register			Address offset: 0x1C*/
	__vo uint32_t I2SPR;		/*! SPI I2S Prescaler Register 				Address offset: 0x20*/
}SPI_RegDef_t;

/*
 * Peripheral Register definition structure for I2Cx
 */

typedef struct
{
	__vo uint32_t CR1;			/*! I2C Control Register 1					Address offset: 0x00*/
	__vo uint32_t CR2;			/*! I2C Control Register 2					Address offset: 0x04*/
	__vo uint32_t OAR1;			/*! I2C Own Address Register 1				Address offset: 0x08*/
	__vo uint32_t OAR2;			/*! I2C Own Address Register 2				Address offset: 0x0C*/
	__vo uint32_t DR;		 	/*! I2C Data Register 						Address offset: 0x10*/
	__vo uint32_t SR1;			/*! I2C Status Register 1					Address offset: 0x14*/
	__vo uint32_t SR2;			/*! I2C Status Register 2	 				Address offset: 0x18*/
	__vo uint32_t CCR;			/*! I2C Clock control Register 				Address offset: 0x1C*/
	__vo uint32_t TRISE;		/*! I2C TRISE Register 						Address offset: 0x20*/
	__vo uint32_t FLTR;			/*! I2C FLTR Register 						Address offset: 0x24*/

}I2C_RegDef_t;

/*
 * Peripheral Register definition structure for RCC
 */
typedef struct{
	__vo uint32_t CR;			/*!< RCC Clock Control REG>					Address offset: 0x00*/
	__vo uint32_t PLLCFGR;		/*!< RCC PLL Clock CONGIG REG>				Address offset: 0x04*/
	__vo uint32_t CFRG;			/*!< RCC Clock CONGIG REG>					Address offset: 0x08*/
	__vo uint32_t CIR;			/*!< RCC Clock INTERRUPT REG>				Address offset: 0x0C*/
	__vo uint32_t AHB1RSTR;		/*!< RCC AHB1 Reset>						Address offset: 0x10*/
	__vo uint32_t AHB2RSTR;		/*!< RCC AHB2 Reset>						Address offset: 0x14*/
	__vo uint32_t AHB3RSTR;		/*!< RCC AHB3 Rese>							Address offset: 0x18*/
		 uint32_t RESERVED1;	/*!< RESERVED 1								Address offset: 0x1C*/
	__vo uint32_t APB1RSTR;		/*!< RCC APB1 Reset>						Address offset: 0x20*/
	__vo uint32_t APB2RSTR;		/*!< RCC APB2 Reset>						Address offset: 0x24*/
		 uint32_t RESERVED2;	/*!< RESERVED 1		>						Address offset: 0x28*/
		 uint32_t RESERVED3;	/*!< RESERVED 3		>						Address offset: 0x2C*/
	__vo uint32_t AHB1ENR;		/*!< RCC AHB1 ENABLE>						Address offset: 0x30*/
	__vo uint32_t AHB2ENR;		/*!< RCC AHB2 ENABLE>						Address offset: 0x34*/
	__vo uint32_t AHB3ENR;		/*!< RCC AHB3 ENABLE>						Address offset: 0x38*/
		 uint32_t RESERVED4;	/*!< RESERVED 4		>						Address offset: 0x3C*/
	__vo uint32_t APB1ENR;		/*!< RCC APB1 ENABLE>						Address offset: 0x40*/
	__vo uint32_t APB2ENR;		/*!< RCC APB2 ENABLE>						Address offset: 0x44*/
		 uint32_t RESERVED5;	/*!< RESERVED 5	>							Address offset: 0x48*/
		 uint32_t RESERVED6;	/*!< RESERVED 6	>							Address offset: 0x4C*/
	__vo uint32_t AHB1LPENR;	/*!< RCC LPAHB1 LPENABLE>					Address offset: 0x50*/
	__vo uint32_t AHB2LPENR;	/*!< RCC LPAHB2 ENABLE>						Address offset: 0x54*/
	__vo uint32_t AHB3LPENR;	/*!< RCC LPAHB3 ENABLE>						Address offset: 0x58*/
		 uint32_t RESERVED7;	/*!< RESERVED 7>							Address offset: 0x5C*/
	__vo uint32_t APB1LPENR;	/*!< RCC APB1 LPENABLE>						Address offset: 0x60*/
	__vo uint32_t APB2LPENR;	/*!< RCC APB2 LPENABLE>						Address offset: 0x64*/
		 uint32_t RESERVED8;	/*!< RESERVED 8>							Address offset: 0x68*/
		 uint32_t RESERVED9;	/*!< RESERVED 9>							Address offset: 0x6C*/
	__vo uint32_t BDCR;			/*!< RTC Domain Control REG>				Address offset: 0x70*/
	__vo uint32_t CSR;			/*!< Control/Status REG>					Address offset: 0x74*/
		 uint32_t RESERVED10;	/*!< RESERVED 10>							Address offset: 0x78*/
		 uint32_t RESERVED11;	/*!< RESERVED 11>							Address offset: 0x7C*/
	__vo uint32_t SSCGR;		/*!< Spread spectclock generation reg>		Address offset: 0x80*/
	__vo uint32_t PLLI2SCFGR;	/*!< PLLI2SCFGR REG>						Address offset: 0x84*/
	__vo uint32_t PLLISAICFGR;	/*!< PLLISAICFGR REG>						Address offset: 0x88*/
	__vo uint32_t DCKCFGR;		/*!< DCKCFGR REG>							Address offset: 0x8C*/
	__vo uint32_t CKGATECFGR;	/*!< CKGATECFGR REG>						Address offset: 0x90*/
	__vo uint32_t DCKCFGR2;		/*!< DCKCFGR2 REG>							Address offset: 0x94*/


}RCC_RegDef_t;


/*
 * Peripheral Register definition structure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;			/*!< EXTI Interrupt Mask Register>			Address offset: 0x00*/
	__vo uint32_t EMR;			/*!< EXTI Event Mask Register>				Address offset: 0x04*/
	__vo uint32_t RTSR;			/*!< EXTI Rising Trigger Selection Reg.,>	Address offset: 0x08*/
	__vo uint32_t FTSR;			/*!< EXTI Falling Trigger Selection Reg.,>	Address offset: 0x0C*/
	__vo uint32_t SWIER;		/*!< EXTI SW interrupt EVent Register>		Address offset: 0x10*/
	__vo uint32_t PR;			/*!< EXTI Pending Register>					Address offset: 0x14*/

}EXTI_RegDef_t;


/*
 * Peripheral Register definition structure for SYSCFG
 */

typedef struct{
	__vo uint32_t MEMRMP;		/*!< Memory Remap Register					Address offset: 0x00 */
	__vo uint32_t PMC;			/*!< Peripheral mode config					Address offset: 0x04 */
	__vo uint32_t EXTICR[4];	/*!<SYSCFG External IRQ CFG Register>		Address offset: 0x08-0x14*/
	uint32_t 	  RESERVED1[2];	/*! RESERVED								Address offset: 0x18-0x1C*/
	__vo uint32_t CMPCR;		/*!< Compensation cell control				Address offset: 0x20 */
	uint32_t 	  RESERVED2[2];	/*! RESERVED								Address offset: 0x24-0x28*/
	__vo uint32_t CFGR;			/*!<SYSCFG Configuration Register2>			Address offset: 0x2C*/
}SYSCFG_RegDef_t;


/*
 * Peripheral definitions (Peripheral base addresses type casted to xxx_RegDef_t)
 */

#define GPIOA				((GPIO_RegDef_t*)GPIOA_BASEADDR)		/*! Defining GPIOA peripheral as typecasting base address*/
#define GPIOB				((GPIO_RegDef_t*)GPIOB_BASEADDR)		/*! Defining GPIOB peripheral as typecasting base address*/
#define GPIOC				((GPIO_RegDef_t*)GPIOC_BASEADDR)		/*! Defining GPIOC peripheral as typecasting base address*/
#define GPIOD				((GPIO_RegDef_t*)GPIOD_BASEADDR)		/*! Defining GPIOD peripheral as typecasting base address*/
#define GPIOE				((GPIO_RegDef_t*)GPIOE_BASEADDR)		/*! Defining GPIOE peripheral as typecasting base address*/
#define GPIOF				((GPIO_RegDef_t*)GPIOF_BASEADDR)		/*! Defining GPIOF peripheral as typecasting base address*/
#define GPIOG				((GPIO_RegDef_t*)GPIOG_BASEADDR)		/*! Defining GPIOG peripheral as typecasting base address*/
#define GPIOH				((GPIO_RegDef_t*)GPIOH_BASEADDR)		/*! Defining GPIOH peripheral as typecasting base address*/

#define RCC					((RCC_RegDef_t*)RCC_BASEADDR)			/*! Defining RCC peripheral as typecasting base address*/
#define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)			/*! Defining EXTI peripheral as typecasting base address*/
#define SYSGFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)		/*! Defining SYSCFG peripheral as typecasting base address*/

#define SPI1				((SPI_RegDef_t*)SPI1_BASEADDR)			/*! Defining SPI1 peripheral as typecasting base address*/
#define SPI2				((SPI_RegDef_t*)SPI2_BASEADDR)			/*! Defining SPI2 peripheral as typecasting base address*/
#define SPI3				((SPI_RegDef_t*)SPI3_BASEADDR)			/*! Defining SPI3 peripheral as typecasting base address*/
#define SPI4				((SPI_RegDef_t*)SPI4_BASEADDR)			/*! Defining SPI4 peripheral as typecasting base address*/

#define I2C1				((I2C_RegDef_t*)I2C1_BASEADDR)			/*! Defining I2C1 peripheral as typecasting base address*/
#define I2C2				((I2C_RegDef_t*)I2C2_BASEADDR)			/*! Defining I2C2 peripheral as typecasting base address*/
#define I2C3				((I2C_RegDef_t*)I2C3_BASEADDR)			/*! Defining I2C3 peripheral as typecasting base address*/

/**********************************************END: PERIPHERAL STRUCTURES******************************************************************/

/**********************************************START:IMPORTANT MACRO DEFINITIONS************************************************************
 *									 CLOCK DISABLE/ENABLE MACRO FOR ALL PERIPHERALS
 ******************************************************************************************************************************************/
/*
 * Clock Enable Macros for GPIOx Peripherals
 */

#define GPIOA_PCLK_EN()			RCC->AHB1ENR |= (1 << 0)			/*! Enabling GPIOA peripheral clock from AHB1 bus 0th bit*/
#define GPIOB_PCLK_EN()			RCC->AHB1ENR |= (1 << 1)			/*! Enabling GPIOB peripheral clock from AHB1 bus 1st bit*/
#define GPIOC_PCLK_EN()			RCC->AHB1ENR |= (1 << 2)			/*! Enabling GPIOC peripheral clock from AHB1 bus 2nd bit*/
#define GPIOD_PCLK_EN()			RCC->AHB1ENR |= (1 << 3)			/*! Enabling GPIOD peripheral clock from AHB1 bus 3rd bit*/
#define GPIOE_PCLK_EN()			RCC->AHB1ENR |= (1 << 4)			/*! Enabling GPIOE peripheral clock from AHB1 bus 4th bit*/
#define GPIOF_PCLK_EN()			RCC->AHB1ENR |= (1 << 5)			/*! Enabling GPIOF peripheral clock from AHB1 bus 5th bit*/
#define GPIOG_PCLK_EN()			RCC->AHB1ENR |= (1 << 6)			/*! Enabling GPIOG peripheral clock from AHB1 bus 6th bit*/
#define GPIOH_PCLK_EN()			RCC->AHB1ENR |= (1 << 7)			/*! Enabling GPIOH peripheral clock from AHB1 bus 7th bit*/

/*
 * Clock Disable Macros for GPIOx Peripherals
 */

#define GPIOA_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 0)			/*! Disabling GPIOA peripheral clock from AHB1 bus 0th bit*/
#define GPIOB_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 1)			/*! Disabling GPIOB peripheral clock from AHB1 bus 1st bit*/
#define GPIOC_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 2)			/*! Disabling GPIOC peripheral clock from AHB1 bus 2nd bit*/
#define GPIOD_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 3)			/*! Disabling GPIOD peripheral clock from AHB1 bus 3rd bit*/
#define GPIOE_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 4)			/*! Disabling GPIOE peripheral clock from AHB1 bus 4th bit*/
#define GPIOF_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 5)			/*! Disabling GPIOF peripheral clock from AHB1 bus 5th bit*/
#define GPIOG_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 6)			/*! Disabling GPIOG peripheral clock from AHB1 bus 6th bit*/
#define GPIOH_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 7)			/*! Disabling GPIOH peripheral clock from AHB1 bus 7th bit*/

/*
 * Remaining clock enable macros for AHB1 tied peripherals
 */

#define CRC_PCLK_EN()			RCC->AHB1ENR |= (1 << 12)			/*! Enabling the CRC clock peripheral from AHB1 bus 12th bit*/
#define BKPSRAM_PLCK_EN()		RCC->AHB1ENR |= (1 << 18)			/*! Enabling the Backup SRAM clock from AHB1 bus 18th bit */
#define DMA1_PCLK_EN()			RCC->AHB1ENR |= (1 << 21)			/*! Enabling the DMA1 clock from AHB1 bus 21st bit*/
#define DMA2_PCLK_EN()			RCC->AHB1ENR |= (1 << 22)			/*! Enabling the DMA2 clock from AHB1 bus 2nd bit*/
#define OTG_HS_PCLK_EN()		RCC->AHB1ENR |= (1 << 29)			/*! Enabling the OTG Half Speed clock from AHB1 bus 29th bit */
#define OTGHSULPI_PCLK_EN()		RCC->AHB1ENR |= (1 << 30)			/*! Enabling the OTG HSULPI clock from AHB1 bus 30th bit */

/*
 * Remaining clock disable macros for AHB1 tied peripherals
 */
#define CRC_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 12)			/*! Disabling the CRC clock peripheral from AHB1 bus 12th bit*/
#define BKPSRAM_PLCK_DI()		RCC->AHB1ENR &= ~(1 << 18)			/*! Disabling the Backup SRAM clock from AHB1 bus 18th bit */
#define DMA1_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 21)			/*! Disabling the DMA1 clock from AHB1 bus 21st bit*/
#define DMA2_PCLK_DI()			RCC->AHB1ENR &= ~(1 << 22)			/*! Disabling the DMA2 clock from AHB1 bus 2nd bit*/
#define OTG_HS_PCLK_DI()		RCC->AHB1ENR &= ~(1 << 29)			/*! Disabling the OTG Half Speed clock from AHB1 bus 29th bit */
#define OTGHSULPI_PCLK_DI()		RCC->AHB1ENR &= ~(1 << 30)			/*! Disabling the OTG HSULPI clock from AHB1 bus 30th bit */

/*
 * Enabling/Disabling the macros for AHB2 tied peripherals
 */
#define DCMIEN_PCLK_EN()		RCC->AHB2ENR |= (1 << 0)			/*! Enabling the Camera Interface from AHB2 bus 1st bit */
#define OTGFS_PCLK_EN()			RCC->AHB2ENR |= (1 << 7)			/*! Enabling the USB OTG FS from AHB2 bus 7th bit */

#define DCMIEN_PCLK_DI()		RCC->AHB2ENR &= ~(1 << 0)			/*! Disabling the Camera Interface from AHB2 bus 1st bit */
#define OTGFS_PCLK_DI()			RCC->AHB2ENR &= ~(1 << 7)			/*! Disabling the USB OTG FS from AHB2 bus 7th bit */

/*
 * Enabling/Disabling the macros for AHB3 tied peripherals
 */
#define FMCEN_PCLK_EN()			RCC->AHB3ENR |= (1 << 0)			/*! Enabling the Flexible memory controller */
#define QSPI_PCLK_EN()			RCC->AHB3ENR |= (1 << 1)			/*! Enabling the QuadSPI Memory controller */

#define FMCEN_PCLK_DI()			RCC->AHB3ENR &= ~(1 << 0)			/*! Disabling the Flexible memory controller */
#define QSPI_PCLK_DI()			RCC->AHB3ENR &= ~(1 << 1)			/*! Disabling the QuadSPI Memory controller */
/******************************************************************************************************************************************/


/****************************************TIMER CLOCK ENABLE/DISABLE MACROS ****************************************************************/
/*
 * Clock Enable Macros for TIMx Peripherals
 */
#define TIM1_PCLK_EN()			RCC->APB2ENR |= (1 << 1)			/*! Enabling TIM1  peripheral clock from APB2 bus 1st bit*/
#define TIM2_PCLK_EN()			RCC->APB1ENR |= (1 << 0)			/*! Enabling TIM1  peripheral clock from APB1 bus 0th bit*/
#define TIM3_PCLK_EN()			RCC->APB1ENR |= (1 << 1)			/*! Enabling TIM3  peripheral clock from APB1 bus 1st  bit*/
#define TIM4_PCLK_EN()			RCC->APB1ENR |= (1 << 2)			/*! Enabling TIM1  peripheral clock from APB1 bus 2nd bit*/
#define TIM5_PCLK_EN()			RCC->APB1ENR |= (1 << 3)			/*! Enabling TIM1  peripheral clock from APB1 bus 3rd bit*/
#define TIM6_PCLK_EN()			RCC->APB1ENR |= (1 << 4)			/*! Enabling TIM6  peripheral clock from APB1 bus 4th  bit*/
#define TIM7_PCLK_EN()			RCC->APB1ENR |= (1 << 5)			/*! Enabling TIM7  peripheral clock from APB1 bus 5th  bit*/
#define TIM8_PCLK_EN()			RCC->APB2ENR |= (1 << 2)			/*! Enabling TIM1  peripheral clock from APB2 bus 2nd bit*/
#define TIM9_PCLK_EN()			RCC->APB2ENR |= (1 << 16)			/*! Enabling TIM1  peripheral clock from APB2 bus 16th bit*/
#define TIM10_PCLK_EN()			RCC->APB2ENR |= (1 << 17)			/*! Enabling TIM1  peripheral clock from APB2 bus 17th bit*/
#define TIM11_PCLK_EN()			RCC->APB2ENR |= (1 << 18)			/*! Enabling TIM1  peripheral clock from APB2 bus 18th bit*/
#define TIM12_PCLK_EN()			RCC->APB1ENR |= (1 << 6)			/*! Enabling TIM1  peripheral clock from APB1 bus 6th bit*/
#define TIM13_PCLK_EN()			RCC->APB1ENR |= (1 << 7)			/*! Enabling TIM1  peripheral clock from APB1 bus 7th bit*/
#define TIM14_PCLK_EN()			RCC->APB1ENR |= (1 << 8)			/*! Enabling TIM14 peripheral clock from APB1 bus 8th  bit*/

/*
 * Clock Disable Macros for TIMx Peripherals
 */

#define TIM1_PCLK_DI()			RCC->APB2ENR &= ~(1 << 1)			/*! Disabling TIM1  peripheral clock from APB2 bus 1st bit*/
#define TIM2_PCLK_DI()			RCC->APB1ENR &= ~(1 << 0)			/*! Disabling TIM1  peripheral clock from APB1 bus 0th bit*/
#define TIM3_PCLK_DI()			RCC->APB1ENR &= ~(1 << 1)			/*! Disabling TIM3  peripheral clock from APB1 bus 1st  bit*/
#define TIM4_PCLK_DI()			RCC->APB1ENR &= ~(1 << 2)			/*! Disabling TIM1  peripheral clock from APB1 bus 2nd bit*/
#define TIM5_PCLK_DI()			RCC->APB1ENR &= ~(1 << 3)			/*! Disabling TIM1  peripheral clock from APB1 bus 3rd bit*/
#define TIM6_PCLK_DI()			RCC->APB1ENR &= ~(1 << 4)			/*! Disabling TIM6  peripheral clock from APB1 bus 4th  bit*/
#define TIM7_PCLK_DI()			RCC->APB1ENR &= ~(1 << 5)			/*! Disabling TIM7  peripheral clock from APB1 bus 5th  bit*/
#define TIM8_PCLK_DI()			RCC->APB2ENR &= ~(1 << 2)			/*! Disabling TIM1  peripheral clock from APB2 bus 2nd bit*/
#define TIM9_PCLK_DI()			RCC->APB2ENR &= ~(1 << 16)			/*! Disabling TIM1  peripheral clock from APB2 bus 16th bit*/
#define TIM10_PCLK_DI()			RCC->APB2ENR &= ~(1 << 17)			/*! Disabling TIM1  peripheral clock from APB2 bus 17th bit*/
#define TIM11_PCLK_DI()			RCC->APB2ENR &= ~(1 << 18)			/*! Disabling TIM1  peripheral clock from APB2 bus 18th bit*/
#define TIM12_PCLK_DI()			RCC->APB1ENR &= ~(1 << 6)			/*! Disabling TIM1  peripheral clock from APB1 bus 6th bit*/
#define TIM13_PCLK_DI()			RCC->APB1ENR &= ~(1 << 7)			/*! Disabling TIM1  peripheral clock from APB1 bus 7th bit*/
#define TIM14_PCLK_DI()			RCC->APB1ENR &= ~(1 << 8)			/*! Disabling TIM14 peripheral clock from APB1 bus 8th  bit*/

/******************************************************************************************************************************************/

/******************************************SPI CLOCK ENABLE/DISABLE MACROS ****************************************************************/
/*
 * Clock Enable Macros for SPI Peripherals
 */

#define SPI1_PCLK_EN()			RCC->APB2ENR |= (1 << 12)			/*! Enabling SPI1 peripheral clock from APB2 bus 12th bit*/
#define SPI2_PCLK_EN()			RCC->APB1ENR |= (1 << 14)			/*! Enabling SPI2 peripheral clock from APB1 bus 14th bit*/
#define SPI3_PCLK_EN()			RCC->APB1ENR |= (1 << 15)			/*! Enabling SPI3 peripheral clock from APB1 bus 15th bit*/
#define SPI4_PCLK_EN()			RCC->APB2ENR |= (1 << 13)			/*! Enabling SPI4 peripheral clock from APB2 bus 13th bit*/

/*
 * Clock Disable Macros for SPI Peripherals
 */

#define SPI1_PCLK_DI()			RCC->APB2ENR &= ~(1 << 12)			/*! Disabling SPI1 peripheral clock from APB2 bus 12th bit*/
#define SPI2_PCLK_DI()			RCC->APB1ENR &= ~(1 << 14)			/*! Disabling SPI2 peripheral clock from APB1 bus 14th bit*/
#define SPI3_PCLK_DI()			RCC->APB1ENR &= ~(1 << 15)			/*! Disabling SPI3 peripheral clock from APB1 bus 15th bit*/
#define SPI4_PCLK_DI()			RCC->APB2ENR &= ~(1 << 13)			/*! Disabling SPI4 peripheral clock from APB2 bus 13th bit*/

/******************************************************************************************************************************************/

/******************************************I2C CLOCK ENABLE/DISABLE MACROS ****************************************************************/
/*
 * Clock Enable Macros for I2C Peripherals
 */

#define I2C1_PCLK_EN()			RCC->APB1ENR |= (1 << 21)			/*! Enabling I2C1 peripheral clock from APB1 bus 21st bit*/
#define I2C2_PCLK_EN()			RCC->APB1ENR |= (1 << 22)			/*! Enabling I2C2 peripheral clock from APB1 bus 22nd bit*/
#define I2C3_PCLK_EN()			RCC->APB1ENR |= (1 << 23)			/*! Enabling I2C3 peripheral clock from APB1 bus 23rd bit*/

/*
 * Clock Disable Macros for I2C Peripherals
 */

#define I2C1_PCLK_DI()			RCC->APB1ENR &= ~(1 << 21)			/*! Disabling I2C1 peripheral clock from APB1 bus 21st bit*/
#define I2C2_PCLK_DI()			RCC->APB1ENR &= ~(1 << 22)			/*! Disabling I2C2 peripheral clock from APB1 bus 22nd bit*/
#define I2C3_PCLK_DI()			RCC->APB1ENR &= ~(1 << 23)			/*! Disabling I2C3 peripheral clock from APB1 bus 23rd bit*/

/******************************************************************************************************************************************/


/******************************************USART CLOCK ENABLE/DISABLE MACROS **************************************************************/
/*
 * Clock Enable Macros for USART Peripherals
 */
#define USART1_PCLK_EN()		RCC->APB2ENR |= (1 << 4)			/*! Enabling USART1 peripheral clock from APB2 bus 14th bit*/
#define USART2_PCLK_EN()		RCC->APB1ENR |= (1 << 17)			/*! Enabling USART2 peripheral clock from APB1 bus 17th bit*/
#define USART3_PCLK_EN()		RCC->APB1ENR |= (1 << 18)			/*! Enabling USART3 peripheral clock from APB1 bus 18th bit*/
#define UART4_PCLK_EN()			RCC->APB1ENR |= (1 << 19)			/*! Enabling USART4 peripheral clock from APB1 bus 19th bit*/
#define UART5_PCLK_EN()			RCC->APB1ENR |= (1 << 20)			/*! Enabling USART5 peripheral clock from APB1 bus 20th bit*/
#define USART6_PCLK_EN()		RCC->APB2ENR |= (1 << 5)			/*! Enabling USART6 peripheral clock from APB2 bus 5th  bit*/

/*
 * Clock Disable Macros for USART Peripherals
 */

#define USART1_PCLK_DI()		RCC->APB2ENR &= ~(1 << 4)			/*! Disabling USART1 peripheral clock from APB2 bus 14th bit*/
#define USART2_PCLK_DI()		RCC->APB1ENR &= ~(1 << 17)			/*! Disabling USART2 peripheral clock from APB1 bus 17th bit*/
#define USART3_PCLK_DI()		RCC->APB1ENR &= ~(1 << 18)			/*! Disabling USART3 peripheral clock from APB1 bus 18th bit*/
#define UART4_PCLK_DI()			RCC->APB1ENR &= ~(1 << 19)			/*! Disabling USART4 peripheral clock from APB1 bus 19th bit*/
#define UART5_PCLK_DI()			RCC->APB1ENR &= ~(1 << 20)			/*! Disabling USART5 peripheral clock from APB1 bus 20th bit*/
#define USART6_PCLK_DI()		RCC->APB2ENR &= ~(1 << 5)			/*! Disabling USART6 peripheral clock from APB2 bus 5th  bit*/


/******************************************************************************************************************************************/


/****************************************************** ADC MACROS ************************************************************************/
/*
 * Clock Enable Macros for ADC
 */

#define ADC1_PCLK_EN()		RCC->APB2ENR |= (1 << 8)			/*! Enabling ADC1 peripheral clock from APB2 bus 8th bit*/
#define ADC2_PCLK_EN()		RCC->APB2ENR |= (1 << 9)			/*! Enabling ADC2 peripheral clock from APB2 bus 9th bit*/
#define ADC3_PCLK_EN()		RCC->APB2ENR |= (1 << 10)			/*! Enabling ADC3 peripheral clock from APB2 bus 10th bit*/

/*
 * Clock Disable Macros for ADC
 */

#define ADC1_PCLK_DI()		RCC->APB2ENR &= ~(1 << 8)			/*! Disabling ADC1 peripheral clock from APB2 bus 8th bit*/
#define ADC2_PCLK_DI()		RCC->APB2ENR &= ~(1 << 9)			/*! Disabling ADC2 peripheral clock from APB2 bus 9th bit*/
#define ADC3_PCLK_DI()		RCC->APB2ENR &= ~(1 << 10)			/*! Disabling ADC3 peripheral clock from APB2 bus 10th bit*/

/******************************************************************************************************************************************/


/****************************************************** OTHER MACROS **********************************************************************/
/*
 * From APB1 bus
 */
#define WWDGEN_PCLK_EN()	RCC->APB1ENR |= (1 << 11)			/*! Enabling the watchdog clock from APB1 bus 11th bit */
#define SPDIFRX_PCLK_EN()	RCC->APB1ENR |= (1 << 16)			/*! Enabling the SPDIF-Rx clock from APB1 bus 16th bit */
#define FMPI2C1_PCLK_EN()	RCC->ABP1ENR |= (1 << 24)			/*! Enbling the FMPI2C1 clock from APB1 bus 24th bit */
#define CAN1_PCLK_EN()		RCC->APB1ENR |= (1 << 25)			/*! Enabling the CAN1 clock from APB1 bus 25th bit*/
#define CAN2_PCLK_EN()		RCC->APB1ENR |= (1 << 26)			/*! Enabling the CAN2 clock from APB1 bus 26th bit*/
#define CEC_PCLK_EN()		RCC->APB1ENR |= (1 << 27)			/*! Enabling the CEC clock from APB1 bus 27th bit*/
#define PWR_PCLK_EN()		RCC->APB1ENR |= (1 << 28)			/*! Enabling the PWR clock from APB1 bus 28th bit*/
#define DAC_PCLK_EN()		RCC->APB1ENR |= (1 << 29)			/*! Enabling the DAC clock from APB1 bus 29th bit*/

#define WWDGEN_PCLK_DI()	RCC->APB1ENR &= ~(1 << 11)			/*! Disabling the watchdog clock from APB1 bus 11th bit */
#define SPDIFRX_PCLK_DI()	RCC->APB1ENR &= ~(1 << 16)			/*! Disabling the SPDIF-Rx clock from APB1 bus 16th bit */
#define FMPI2C1_PCLK_DI()	RCC->ABP1ENR &= ~(1 << 24)			/*! Disbling the FMPI2C1 clock from APB1 bus 24th bit */
#define CAN1_PCLK_DI()		RCC->APB1ENR &= ~(1 << 25)			/*! Disabling the CAN1 clock from APB1 bus 25th bit*/
#define CAN2_PCLK_DI()		RCC->APB1ENR &= ~(1 << 26)			/*! Disabling the CAN2 clock from APB1 bus 26th bit*/
#define CEC_PCLK_DI()		RCC->APB1ENR &= ~(1 << 27)			/*! Disabling the CEC clock from APB1 bus 27th bit*/
#define PWR_PCLK_DI()		RCC->APB1ENR &= ~(1 << 28)			/*! Disabling the PWR clock from APB1 bus 28th bit*/
#define DAC_PCLK_DI()		RCC->APB1ENR &= ~(1 << 29)			/*! Disabling the DAC clock from APB1 bus 29th bit*/

/*
 * From AB2 bus
 */
#define SDIO_PCLK_EN()		RCC->ABP2ENR |= (1 << 11)			/*! Enabling the SDIO clock from APB2 bus 11th bit */
#define SAI1_PCLK_EN()		RCC->APB2ENR |= (1 << 22)			/*! Enabling the SAI1 clock from APB2 bus 22nd bit */
#define SAI2_PCLK_EN()		RCC->APB2ENR |= (1 << 23)			/*! Enabling the SAI2 clock from APB2 bus 23rd bit */

#define SDIO_PCLK_DI()		RCC->ABP2ENR &= ~(1 << 11)			/*! Disbling the SDIO clock from APB2 bus 11th bit */
#define SAI1_PCLK_DI()		RCC->APB2ENR &= ~(1 << 22)			/*! Disabling the SAI1 clock from APB2 bus 22nd bit */
#define SAI2_PCLK_DI()		RCC->APB2ENR &= ~(1 << 23)			/*! Disabling the SAI2 clock from APB2 bus 23rd bit */

/******************************************************************************************************************************************/


/********************************************* SYSTEM CONFIGURATION MACROS ****************************************************************/
/*
 * Clock Enable Macros for SYSCFG
 */

#define SYSCFG_PCLK_EN()		RCC->APB2ENR |= (1 << 14)		/*! Enabling SYSCFG peripheral clock from APB2 bus 14th bit*/

/*
 * Clock Disable Macros for SYSCFG
 */

#define SYSCFG_PCLK_DI()		RCC->APB2ENR &= ~(1 << 14)		/*! Disabling SYSCFG peripheral clock from APB2 bus 14th bit*/

/******************************************************************************************************************************************/

/************************************************** GPIOx RESET MACROS ********************************************************************/

/*
 * Macros to reset the GPIOx peripherals
 */

#define GPIOA_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 0));(RCC -> AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 1));(RCC -> AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 2));(RCC -> AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 3));(RCC -> AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 4));(RCC -> AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 5));(RCC -> AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 6));(RCC -> AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()		do{ (RCC -> AHB1RSTR |= (1 << 7));(RCC -> AHB1RSTR &= ~(1 << 7)); }while(0)

/******************************************************************************************************************************************/

/************************************************** SPIx RESET MACROS ********************************************************************/

/*
 * Macros to reset the SPIx peripherals
 */

#define SPI1_REG_RESET()		do{ (RCC -> APB2RSTR |= (1 << 12));(RCC -> APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()		do{ (RCC -> APB1RSTR |= (1 << 14));(RCC -> APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()		do{ (RCC -> APB1RSTR |= (1 << 15));(RCC -> APB1RSTR &= ~(1 << 15)); }while(0)
#define SPI4_REG_RESET()		do{ (RCC -> APB2RSTR |= (1 << 13));(RCC -> APB1RSTR &= ~(1 << 13)); }while(0)

/******************************************************************************************************************************************/
/************************************************** I2Cx RESET MACROS ********************************************************************/

/*
 * Macros to reset the I2Cx peripherals
 */

#define I2C1_REG_RESET()		do{ (RCC -> APB1RSTR |= (1 << 21));(RCC -> APB2RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()		do{ (RCC -> APB1RSTR |= (1 << 22));(RCC -> APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()		do{ (RCC -> APB1RSTR |= (1 << 23));(RCC -> APB1RSTR &= ~(1 << 23)); }while(0)

/******************************************************************************************************************************************/
/*********************************************** GPIO_BASEADDR_TO_CODE ********************************************************************/
/*
 * This macro returns a code (between 0 to 4) for a given GPIO base Address(x)
 */
#define GPIO_BASEADDR_TO_CODE(x)	((x == GPIOA) ? 0:\
									 (x == GPIOB) ? 1:\
									 (x == GPIOC) ? 2:\
									 (x == GPIOD) ? 3:\
									 (x == GPIOE) ? 4:\
									 (x == GPIOF) ? 5:\
									 (x == GPIOG) ? 6:\
									 (x == GPIOH) ? 7:0 )

/******************************************************************************************************************************************/

/**************************************************** IRQ MACROS **************************************************************************/
/*
 * IRQ (Interrupt Requests) Numbers of STM32F070xx MCU
 * NOTE: update these macros with valid values according to your MCU
 * TO DO: You may complete this list for other peripherals
 */

#define IRQ_NO_EXTI0		6		/*!EXTI Line[0] interrupts*/
#define IRQ_NO_EXTI1		7		/*!EXTI Line[1] interrupts*/
#define IRQ_NO_EXTI2		8		/*!EXTI Line[2] interrupts*/
#define IRQ_NO_EXTI3		9		/*!EXTI Line[3] interrupts*/
#define IRQ_NO_EXTI4		10		/*!EXTI Line[4] interrupts*/
#define IRQ_NO_EXTI9_5		23		/*!EXTI Line[9:5] interrupts*/
#define IRQ_NO_EXTI15_10	40		/*!EXTI Line[15:10] interrupts*/

#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51
#define IRQ_NO_SPI4			84


/*
 * Macros for all the priority levels
 */
#define NVIC_IRQ_PRI0		0		/*! NeNested Vectored Interrupt Controller Priority 0*/
#define NVIC_IRQ_PRI1		1		/*! NeNested Vectored Interrupt Controller Priority 1*/
#define NVIC_IRQ_PRI2		2		/*! NeNested Vectored Interrupt Controller Priority 2*/
#define NVIC_IRQ_PRI3		3		/*! NeNested Vectored Interrupt Controller Priority 3*/
#define NVIC_IRQ_PRI4		4		/*! NeNested Vectored Interrupt Controller Priority 4*/
#define NVIC_IRQ_PRI5		5		/*! NeNested Vectored Interrupt Controller Priority 5*/
#define NVIC_IRQ_PRI6		6		/*! NeNested Vectored Interrupt Controller Priority 6*/
#define NVIC_IRQ_PRI7		7		/*! NeNested Vectored Interrupt Controller Priority 7*/
#define NVIC_IRQ_PRI8		8		/*! NeNested Vectored Interrupt Controller Priority 8*/
#define NVIC_IRQ_PRI9		9		/*! NeNested Vectored Interrupt Controller Priority 9*/
#define NVIC_IRQ_PRI10		10		/*! NeNested Vectored Interrupt Controller Priority 10*/
#define NVIC_IRQ_PRI11		11		/*! NeNested Vectored Interrupt Controller Priority 11*/
#define NVIC_IRQ_PRI12		12		/*! NeNested Vectored Interrupt Controller Priority 12*/
#define NVIC_IRQ_PRI13		13		/*! NeNested Vectored Interrupt Controller Priority 13*/
#define NVIC_IRQ_PRI14		14		/*! NeNested Vectored Interrupt Controller Priority 14*/
#define NVIC_IRQ_PRI15		15		/*! NeNested Vectored Interrupt Controller Priority 15*/

/******************************************************************************************************************************************/


/************************************************* SOME GENERIC MACROS ********************************************************************/

#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define	GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_RESET		RESET
#define FLAG_SET		SET

/*****************************************************************************************************************************************/
/****************************************END:IMPORTANT MACRO DEFINITONS *******************************************************************/
/******************************************DRIVER FILES INCLUSION**************************************************************************/


/******************************************************************************************************************************************
 *  										Bit position definitons of the SPI peripherals - START
 ******************************************************************************************************************************************/
/****************************************************************CR1***********************************************************************/
/*
 * @CR1 - Control Register 1
 */
#define SPI_CR1_CPHA		0		/*! Clock phase */
#define SPI_CR1_CPOL		1		/*! Clock polarity */
#define SPI_CR1_MSTR		2		/*! Clock polarity */
#define SPI_CR1_BR			3		/*! Baud rate control */
#define SPI_CR1_SPE			6		/*! SPI enable */
#define SPI_CR1_LSBFIRST	7		/*! Frame format */
#define SPI_CR1_SSI			8		/*! Internal slave select */
#define SPI_CR1_SSM			9		/*! Software slave management */
#define SPI_CR1_RXONLY		10		/*! Receive only mode enabled. */
#define SPI_CR1_DFF			11		/*! CRC length */
#define SPI_CR1_CRCNEXT		12		/*! Transmit CRC next */
#define SPI_CR1_CRCEN		13		/*! Clock phaseHardware CRC calculation enable */
#define SPI_CR1_BIDIOE		14		/*! Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE	15		/*! Bidirectional data mode enable */
/****************************************************************CR1***********************************************************************/
/****************************************************************CR2***********************************************************************/
/*
 * @CR2 - Control Register 2
 */
#define SPI_CR2_RXDMAEN		0		/*! Rx buffer DMA enable */
#define SPI_CR2_TXDMAEN		1		/*! Tx buffer DMA enable */
#define SPI_CR2_SSOE		2		/*! SS output enable */
#define SPI_CR2_NSSP		3		/*! NSS pulse management */
#define SPI_CR2_FRF			4		/*! Frame format */
#define SPI_CR2_ERRIE		5		/*! Error interrupt enable */
#define SPI_CR2_RXNEIE		6		/*! RX buffer not empty interrupt enable */
#define SPI_CR2_TXEIE		7		/*! Tx buffer empty interrupt enable */
#define SPI_CR2_DS			8		/*! Data Size */
#define SPI_CR2_FRXTH		12		/*! FIFO reception threshold */
#define SPI_CR2_LDMA_RX		13		/*! Last DMA transfer for reception */
#define SPI_CR2_LDMA_TX		14		/*! Last DMA transfer for transmission */
/****************************************************************CR2***********************************************************************/
/****************************************************************SR***********************************************************************/
/*
 * @SR - Status Register
 */
#define SPI_SR_RXNE			0		/*! Receive buffer not empty */
#define SPI_SR_TXE			1		/*! Transmit buffer empty */
#define SPI_SR_CRCERR		4		/*! CRC error flag */
#define SPI_SR_MODF			5		/*! Mode fault */
#define SPI_SR_OVR			6		/*! Overrun flag */
#define SPI_SR_BSY			7		/*! Busy flag */
#define SPI_SR_FRE			8		/*! Frame format error */
#define SPI_SR_FRLVL		9		/*! FIFO reception level */
#define SPI_SR_FTLVL		11		/*! FIFO transmission level */
/****************************************************************SR***********************************************************************/
/****************************************************************DR***********************************************************************/
/*
 * @DR - Data Register
 */
#define SPI_SR_DR		0		/*! Data register - Data received or to be transmitted */

/*!> Not using the below registers - CRCPR, RXCRCR, TXCRCR*/
/****************************************************************DR***********************************************************************/
/******************************************************************************************************************************************
 *  										Bit position definitons of the SPI peripherals - END
 ******************************************************************************************************************************************/


/******************************************************************************************************************************************
 *  										Bit position definitons of the I2C peripherals - START
 ******************************************************************************************************************************************/
/****************************************************************CR1***********************************************************************/
/*
 * @CR1 - Control Register 1
 */
#define I2C_CR1_PE			0		/*! Peripheral Enable */
#define I2C_CR1_SMBUS		1		/*! SMBus Mode */
#define I2C_CR1_SMBTYPE		3		/*! SMBus Type */
#define I2C_CR1_ENARP		4		/*! ARP Enable */
#define I2C_CR1_ENPEC		5		/*! PEC Enable */
#define I2C_CR1_ENGC		6		/*! General Call Enable */
#define I2C_CR1_NOSTRETCH	7		/*! Clock Stretching disable (slave mode) */
#define I2C_CR1_START		8		/*! Start generation */
#define I2C_CR1_STOP		9		/*! Stop generation */
#define I2C_CR1_ACK			10		/*! Acknowledgement enable */
#define I2C_CR1_POS			11		/*! Acknowledge/ PEC Position (for data reception */
#define I2C_CR1_PEC			12		/*! Packet Error Checking */
#define I2C_CR1_ALERT		13		/*! SMBus Alert */
#define I2C_CR1_SWRST		15		/*! Software Reset */
/****************************************************************CR1***********************************************************************/
/****************************************************************CR2***********************************************************************/
/*
 * @CR2 - Control Register 2
 */
#define I2C_CR2_FREQ		0		/*! Peripheral Clock frequency */
#define I2C_CR2_ITERREN		8		/*! Error Interrupt Enable */
#define I2C_CR2_ITEVTEN		9		/*! Event Interrupt Enable */
#define I2C_CR2_ITBUFEN		10		/*! Buffer Interrupt Enable */
#define I2C_CR2_DMAEN		11		/*! DMA Request Enable */
#define I2C_CR2_LAST		12		/*! DMA Last Transfer */
/****************************************************************CR2***********************************************************************/
/****************************************************************OAR1***********************************************************************/
/*
 * @OAR1 - own address 1 register
 */
#define I2C_OAR1_ADD0		0		/*! Interface Address */
#define I2C_OAR1_ADD71		1		/*! Interface Address */
#define I2C_OAR1_ADD98		8		/*! Interface Address */
#define I2C_OAR1_ADDMODE			/*! Addressing Mode */
/****************************************************************OAR1***********************************************************************/
/****************************************************************OAR2***********************************************************************/
/*
 * @OAR2 - own address 2 register
 */
#define I2C_OAR2_ENDUAL		0		/*! Dual Addressing mode enable */
#define I2C_OAR2_ADD271		8		/*! Interface Address */
/****************************************************************OAR2***********************************************************************/
/*************************************************************DATA REGISTER*****************************************************************/
/*
 * @DR - Data Register
 */
#define I2C_DR_DR70			0		/*! 8 bit data register */
/*************************************************************DATA REGISTER*****************************************************************/
/************************************************************STATUS REGISTER 1**************************************************************/
/*
 * @SR1 - Status Register 1
 */
#define I2C_SR1_SB			0		/*! Start Bit (Master Mode) */
#define I2C_SR1_ADDR		1		/*! Address sent(master mode)/matched(slave mode) */
#define I2C_SR1_BTF			2		/*! Byte Transfer Finished */
#define I2C_SR1_ADD10		3		/*! 10-bit header sent */
#define I2C_SR1_STOPF		4		/*! Stop Detection */
#define I2C_SR1_RxNE		6		/*! Data register not empty (receivers) */
#define I2C_SR1_TxE			7		/*! Data register empty (transmitters) */
#define I2C_SR1_BERR		8		/*! Bus Error */
#define I2C_SR1_ARLO		9		/*! Arbitration lost (master mode) */
#define I2C_SR1_AF			10		/*! Acknowledge failure */
#define I2C_SR1_OVR			11		/*! Overrun/Underrun */
#define I2C_SR1_PECERR		12		/*! PEC Error in reception */
#define I2C_SR1_TIMEOUT		14		/*! Timeout or Tlow Error */
#define I2C_SR1_SMBALERT	15		/*! SMBus Alert */
/*************************************************************STATUS REGISTER 1**************************************************************/
/*************************************************************STATUS REGISTER 2**************************************************************/
/*
 * @SR2 - Status Register 2
 */

#define I2C_SR2_MSL			0		/*! Master / slave */
#define I2C_SR2_BUSY		1		/*! Bus Busy */
#define I2C_SR2_TRA			2		/*! Transmitter/ Receiver */
#define I2C_SR2_GENCALL		4		/*! General Call Address */
#define I2C_SR2_SMBDEFAULT	5		/*! SMBus device default address (slave mode) */
#define I2C_SR2_SMBHOST		6		/*! SMBus host header (Slave mode) */
#define I2C_SR2_DUALF		7		/*! Dual Flag (slave mode) */
#define I2C_SR2_PEC70		8		/*! Packet Error Checking Register bit */
/************************************************************STATUS REGISTER 2*************************************************************/
/****************************************************************CCR***********************************************************************/
/*
 * @CCR - Clock control register
 */
#define I2C_CCR_CCR110			0	/*! Clock control register in Fm/Sm Mode (Master mode) */
#define I2C_CCR_DUTY			14	/*! FM Mode duty Cycle */
#define I2C_CCR_F_S				15  /*! I2C Master mode selection */
/****************************************************************CCR***********************************************************************/
/***************************************************************TRISE**********************************************************************/
/*
 * @TRISE - TRISE register
 */
#define I2C_TRISE_TRISE50		0	/*! Maximum rise time in Fm/Sm mode (Master mode) */
/***************************************************************TRISE**********************************************************************/
/****************************************************************FLTR**********************************************************************/
/*
 * @FLTR - FLTR register
 */
#define I2C_FLTR_DNF30			0	/*! Digital Noise filter */
#define I2C_FLTR_ANOFF			4	/*! Analog Noise filter */
/****************************************************************FLTR**********************************************************************/
/******************************************************************************************************************************************
 *  										Bit position definitons of the I2C peripherals - END
 ******************************************************************************************************************************************/


#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_i2c_driver.h"
#include "stm32f446xx_clock_driver.h"
#include "stm32f446xx_adc_driver.h"
#include "stm32f446xx_spi_driver.h"
/******************************************************************************************************************************************/
#endif /* INC_STM32F466XX_H_ */
