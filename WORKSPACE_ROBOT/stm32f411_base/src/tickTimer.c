/*

 * TickTimer.c
 *
 *  Created on: Feb 24, 2015
 *      Author: kerhoas
 */

#include "tickTimer.h"

TIM_HandleTypeDef    TimHandle_period;

//================================================
//				TIMER 5 INIT
//================================================

void tickTimerInit(void)
{

	unsigned int uwPrescalerValue;

/* Compute the prescaler value to have TIM5 counter clock equal to 10 KHz */
  uwPrescalerValue = (unsigned int) ((SystemCoreClock / 10000) - 1);

  TimHandle_period.Instance = TIM5;
  TimHandle_period.Init.Period = 1000 - 1;
  TimHandle_period.Init.Prescaler = uwPrescalerValue;
  TimHandle_period.Init.ClockDivision = 0;
  TimHandle_period.Init.CounterMode = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&TimHandle_period);

  HAL_TIM_Base_Start_IT(&TimHandle_period);
}

//================================================
//			TIMER 5 CALLBACK PERIOD
//================================================

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);	// TOGGLE LED
/*
// SemGive From Interrupt Callback :
// REM : Interrupt Priority (cf stm32f4xx_hal_msp.c) > #define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY (cf FreeRTOSConfig.h)
static BaseType_t xHigherPriorityTaskWoken;
xSemaphoreGiveFromISR( xSemaphore,&xHigherPriorityTaskWoken );
portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
*/
}
//================================================

