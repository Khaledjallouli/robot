/*
 * config.h
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

//========================================================
// USART : CHOIX DE LA LIAISON SERIE
// USART2 : USART_STLINK (cable)
// USART6 : USART_ZIGBEE (sans fil)
//========================================================
//#define	USE_USART_STLINK 1			// A Commenter pour utiliser stlink dans term_printf !! faire une clean
#define	USE_USART_ZIGBEE 1

#define NB_CAR_TO_RECEIVE		1		// nombre de caractères à recevoir pour déclencher une interruption

#define USART2_BAUDRATE			115200
#define USART6_BAUDRATE			9600
//========================================================
//					LIAISON I2C
//========================================================
#define I2C1_CLOCKSPEED			100000
#define I2C2_CLOCKSPEED			100000

// CAPTEUR I2C DISTANCE ULTRASON SRF02
#define	CAPT_US_LEFT_ADDRESS	0xE0
#define	CAPT_US_RIGHT_ADDRESS	0xE2

// IMU MPU9250
#define    MPU9250_ADDRESS      0x68
#define    AK8963_ADDRESS       0x0C

// ECRAN LCD
#define SCREEN_LCD_ADDRESS		(0x30<<1)

// SAMPLING PERIOD in ms
#define SAMPLING_PERIOD_ms		5

#endif /* INC_CONFIG_H_ */

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
