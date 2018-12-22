#include "stm32f4xx_hal_msp.h"

#define USART2_IRQ_PRIO	9
#define USART6_IRQ_PRIO	10
#define EXTI1_IRQ_PRIO	7
#define EXTI0_IRQ_PRIO	6
#define EXTI15_10_IRQ_PRIO	5
#define I2C1_ER_IRQ_PRIO	2
#define I2C1_EV_IRQ_PRIO	11
#define TIM5_IRQ_PRIO		12

void HAL_MspInit(void)
{

	  __GPIOA_CLK_ENABLE();
	  __GPIOB_CLK_ENABLE();
	  __GPIOC_CLK_ENABLE();

	  HAL_UARTCOM_MspInit();
	  HAL_UARTZIGBEE_MspInit();
	  HAL_Encoder_Timer1_MspInit();
	  HAL_Encoder_Timer2_MspInit();

	  HAL_tickTimer_MspInit();
	  HAL_GPIO_LED_MspInit();
	  HAL_GPIO_BUTTON_MspInit();
	  HAL_i2c_MspInit();
	  HAL_spi_MspInit();
	  HAL_adcir_MspInit();

	  HAL_PWM_Timer3_MspInit();
	  HAL_PWM_Timer4_MspInit();
}
/******************************************************************
			USART2 : ST-LINK virtual Port
 TX --> PA2
 RX --> PA3
*******************************************************************/
void HAL_UARTCOM_MspInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  __GPIOA_CLK_ENABLE();

  __USART2_CLK_ENABLE();

  GPIO_InitStruct.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_LOW;	//GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate =  GPIO_AF7_USART2;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(USART2_IRQn, USART2_IRQ_PRIO, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
}
/******************************************************************
			USART6 : ZIGBEE PORT

  PC6     ------> USART6_TX
  PC7     ------> USART6_RX
******************************************************************/
void HAL_UARTZIGBEE_MspInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

    __USART6_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART6_IRQn, USART6_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
}
/******************************************************************
			ENCODER - TIMER1
PWM1/1	-->	PA8		-- Encodeur Voie A
PWM1/2	--> PA9		-- Encodeur Voie B
EXTI1	--> PC1		-- Index encodeur
******************************************************************/
void HAL_Encoder_Timer1_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  __TIM1_CLK_ENABLE(); // ATTENTION

	  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // hal_gpio.h
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	  GPIO_InitStruct.Alternate =  GPIO_AF1_TIM1 ; // hal_gpio_ex.h

	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  // Index moteur -- PC1

	  GPIO_InitStruct.Pin = GPIO_PIN_1;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;

	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	  HAL_NVIC_SetPriority(EXTI1_IRQn, EXTI1_IRQ_PRIO, 0);
	  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}
/******************************************************************
				ENCODER - TIMER2
PWM2/1	-->	PA0		-- Encodeur Voie A
PWM2/2	--> PA1		-- Encodeur Voie B
EXTI 	--> PB0		-- Index Moteur
******************************************************************/
void HAL_Encoder_Timer2_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  __TIM2_CLK_ENABLE(); // ATTENTION

	  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // hal_gpio.h
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	  GPIO_InitStruct.Alternate =  GPIO_AF1_TIM2 ; // hal_gpio_ex.h

	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_0;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;

	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	  HAL_NVIC_SetPriority(EXTI0_IRQn, EXTI0_IRQ_PRIO, 0);
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
//******************************************************************
//			GPIO BUTTON - PC13 (USER BUTTON)
//******************************************************************
void HAL_GPIO_BUTTON_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;

	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	  HAL_NVIC_SetPriority(EXTI15_10_IRQn, EXTI15_10_IRQ_PRIO, 0);
	  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}
//******************************************************************
//			GPIO LED PA5
//******************************************************************
void HAL_GPIO_LED_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

/* Configure PA05 IO in output push-pull mode to drive external LED */
	  GPIO_InitStruct.Pin = GPIO_PIN_5;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/******************************************************************
//			PWM - TIMER3 COMMANDE SERVOMOTEURS (Tourelle cam)

PB4 --> PWM3/1
PB5 --> PWM3/2
******************************************************************/
void HAL_PWM_Timer3_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  __TIM3_CLK_ENABLE();
	  GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	  GPIO_InitStruct.Alternate =  GPIO_AF2_TIM3 ; // hal_gpio_ex.h
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/******************************************************************
//			PWM - TIMER4 COMMANDE MOTEURS

PB6 --> PWM4/1
PB7 --> PWM4/2
PA15 --> ENABLE MOTEUR (actif état Bas)
******************************************************************/
void HAL_PWM_Timer4_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  __TIM4_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_6 |  GPIO_PIN_7;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	  GPIO_InitStruct.Alternate =  GPIO_AF2_TIM4 ; // hal_gpio_ex.h

	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  // ENABLE MOTEUR : SORTIE LOGIQUE PA15
	  GPIO_InitStruct.Pin = GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
}

/******************************************************************
			I2C - 1
I2C1_SCL	-->	PB8
I2C1_SDA	--> PB9
******************************************************************/
void HAL_i2c_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;
	  //-----------------------------------------------------------
	  // 						I2C1
	  //-----------------------------------------------------------
	  __I2C1_CLK_ENABLE();

	  	  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	  	  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	  	  GPIO_InitStruct.Alternate =   GPIO_AF4_I2C1 ; // hal_gpio_ex.h

	  	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  	  HAL_NVIC_SetPriority(I2C1_ER_IRQn, I2C1_ER_IRQ_PRIO, 0);
	  	  HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
	  	  HAL_NVIC_SetPriority(I2C1_EV_IRQn, I2C1_EV_IRQ_PRIO, 0);
	  	  HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
}

/******************************************************************
			TIMER 5 TickTimer
******************************************************************/
void HAL_tickTimer_MspInit(void)
{

	__TIM5_CLK_ENABLE();

 	 HAL_NVIC_SetPriority(TIM5_IRQn, TIM5_IRQ_PRIO, 0);
	 HAL_NVIC_EnableIRQ(TIM5_IRQn);
}


/******************************************************************
			SPI 1
SPI1_SCK	--> PA5
SPI1_MISO	--> PA6
SPI1_MOSI	--> PA7
SPI1 NSS	--> PA4
******************************************************************/
void HAL_spi_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;
	  /* Peripheral clock enable */
	   __SPI1_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_4;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;//GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;//GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	  GPIO_InitStruct.Alternate =   GPIO_AF5_SPI1 ; // hal_gpio_ex.h

	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
/******************************************************************
			ADC
ADC1_12	--> PC2
ADC1_13	--> PC3
http://stm32f4-discovery.com/2014/04/library-06-ad-converter-on-stm32f4xx/
******************************************************************/
void HAL_adcir_MspInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;
	  /* Peripheral clock enable */
	  __ADC1_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 ;
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;

	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

//=======================================================================

void HAL_MspDeInit(void)
{

}
