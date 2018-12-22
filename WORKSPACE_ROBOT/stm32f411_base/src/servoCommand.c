/*
 * ServoCommand.C
 */

#include "servoCommand.h"

/****************************************************
 * servoCommand.c		(TIMER 3)
 *	PWM3 - CH1 - PB4	-	SERVO HIGH
 *	PWM3 - CH2 - PB5	- 	SERVO LOW
****************************************************/

// PERIODE : 20 ms
// positions min/mid/max : 0.4, 1.4, 2.4 ms --> 20/70/120

#define SERVO_POS_INIT_LOW 70
#define	SERVO_POS_INIT_HIGH	70


static TIM_HandleTypeDef    TimHandle;
static TIM_OC_InitTypeDef   sConfigOC;

static int servoPosLow = SERVO_POS_INIT_LOW;
static int servoPosHigh = SERVO_POS_INIT_HIGH;

void servoCommand_Init(void)
{

	unsigned int uwPrescalerValue = 0;

	/* Compute the prescaler value to have TIM4 counter clock equal to 50kHz */
	  uwPrescalerValue = (unsigned int) ((SystemCoreClock / 50000) - 1);
	  TimHandle.Instance = TIM3;
	  TimHandle.Init.Period = 1000 - 1; // 50kHz/1000=50Hz (T=20ms)
	  TimHandle.Init.Prescaler = uwPrescalerValue;
	  TimHandle.Init.ClockDivision = 0;
	  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

	  HAL_TIM_Base_Init(&TimHandle);

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = 0x5;// Specifies the pulse value to be loaded into the Capture Compare Register. This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

	  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	 HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfigOC, TIM_CHANNEL_1);
	 HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfigOC, TIM_CHANNEL_2);

	 // CHANGEMENT DU RAPPORT CYCLIQUE
	 __HAL_TIM_SetCompare(&TimHandle, TIM_CHANNEL_1, servoPosHigh);	// 100 : moteurs au repos
	 __HAL_TIM_SetCompare(&TimHandle, TIM_CHANNEL_2, servoPosLow);

	  HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);


}

void servoHigh_Set(int cons_pos)
{
	servoPosHigh=cons_pos;
	__HAL_TIM_SetCompare(&TimHandle, TIM_CHANNEL_1, cons_pos);
}

void servoLow_Set(int cons_pos)
{
	servoPosLow=cons_pos;
	__HAL_TIM_SetCompare(&TimHandle, TIM_CHANNEL_2, cons_pos);
}

int servoHigh_Get(void)
{
	return servoPosHigh;
}

int servoLow_Get(void)
{
	return servoPosLow;
}





