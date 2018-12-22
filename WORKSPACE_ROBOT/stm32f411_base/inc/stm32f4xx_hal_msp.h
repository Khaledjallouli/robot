/*
 * stm32f4xx_hal_msp.h
 */

#ifndef INC_STM32F4XX_HAL_MSP_H_
#define INC_STM32F4XX_HAL_MSP_H_



#include "stm32f4xx_hal.h"
#include "main.h"
#include "stm32f4xx_hal_gpio_ex.h"

void HAL_MspInit(void);

void HAL_UARTCOM_MspInit(void);
void HAL_UARTZIGBEE_MspInit(void);
void HAL_Encoder_Timer1_MspInit(void);
void HAL_Encoder_Timer2_MspInit(void);

void HAL_PWM_Timer3_MspInit(void);
void HAL_PWM_Timer4_MspInit(void);
void HAL_tickTimer_MspInit(void);
void HAL_GPIO_LED_MspInit(void);
void HAL_GPIO_BUTTON_MspInit(void);
//static void EXTILine0_Config(void);
//static void EXTILine1_Config(void);
void HAL_i2c_MspInit(void);
void HAL_spi_MspInit(void);
void HAL_adcir_MspInit(void);


#endif /* INC_STM32F4XX_HAL_MSP_H_ */
