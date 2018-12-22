
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/* Includes ------------------------------------------------------------------*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_nucleo.h"
#include "stm32f401xe.h"
#include "stm32f4xx_hal.h"
#include "captDistIR.h"
#include "captDistUltrason.h"
#include "config.h"

#include "drv_uart.h"
#include "drv_i2c.h"
#include "drv_spi.h"

#include "SystemClock.h"
#include "motorCommand.h"
#include "servoCommand.h"
#include "quadEncoder.h"
#include "tickTimer.h"
#include "screenLCD.h"

#include "FreeRTOS.h"
#include "pixyCam.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "util.h"

#endif /* __MAIN_H */


