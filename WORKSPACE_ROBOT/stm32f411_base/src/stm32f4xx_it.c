
#include "main.h"
#include "stm32f4xx_it.h"

extern PCD_HandleTypeDef hpcd;

extern TIM_HandleTypeDef    TimHandle;
extern TIM_HandleTypeDef    TimHandle_period;
extern UART_HandleTypeDef 	Uart2Handle;
extern UART_HandleTypeDef 	Uart6Handle;
extern I2C_HandleTypeDef hi2c1;

extern void xPortSysTickHandler(void);

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}


void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*
void SVC_Handler(void)
{}
*/

void DebugMon_Handler(void)
{
}
/*
void PendSV_Handler(void)
{}
*/

void SysTick_Handler(void)
{
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	    {
	      xPortSysTickHandler();
	    }
  HAL_IncTick();
}


void OTG_FS_IRQHandler(void)
{
   //HAL_PCD_IRQHandler(&hpcd); // USB
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle_period);
}

//=======================================================
//		ENCODER INDEX LEFT
//=======================================================
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
//=======================================================
//		ENCODER INDEX RIGHT
//=======================================================

void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void I2C1_EV_IRQHandler(void)
{
	  HAL_I2C_EV_IRQHandler(&hi2c1);
}

void I2C1_ER_IRQHandler(void)
{
	  HAL_I2C_ER_IRQHandler(&hi2c1);
}

//=======================================================
// USER BUTTON INTERRUPT (PC13)
//=======================================================
void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}
//=======================================================
// STLINK USART RECEIVE HANDLER
//=======================================================
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&Uart2Handle);
}
//=======================================================
// ZIGBEE USART RECEIVE HANDLER
//=======================================================
void USART6_IRQHandler(void)
{
  HAL_UART_IRQHandler(&Uart6Handle);
}
//=======================================================





