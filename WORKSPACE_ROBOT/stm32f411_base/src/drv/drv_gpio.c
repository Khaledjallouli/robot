/*
 * drv_gpio.c
 */

#include "drv_gpio.h"

extern void quadEncoder_CallbackIndexL(void);
extern void quadEncoder_CallbackIndexR(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case GPIO_PIN_0 :
		quadEncoder_CallbackIndexR();
					break;

	case GPIO_PIN_1 :
		quadEncoder_CallbackIndexL();
					break;

	case GPIO_PIN_3:
					break;

	case GPIO_PIN_10:


	case GPIO_PIN_13 :		// USER BUTTON
					break;

	default : 		break;


	}
}

