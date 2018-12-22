/*
 * srf02.c
 */

#include "captDistUltrason.h"

/********************************************************
 	 	 	 	 DOCUMENTATION
http://www.robot-electronics.co.uk/htm/srf02techI2C.htm
http://www.robot-electronics.co.uk/htm/arduino_examples.htm#SRF02,%20SRF08,%20SRF10,%20SRF235
********************************************************/

extern I2C_HandleTypeDef hi2c1;

// Wait between captDistUS_Measure() and captDistUS_Get ()
//  datasheet suggests at least 65 milliseconds
/*
		captDistUS_Measure(0xE0);
		vTaskDelay(70);
		dist_L = captDistUS_Get(0xE0);
 */
//=================================================================
//			SRF02 GET DISTANCE
//=================================================================

void captDistUS_Measure(uint16_t addr_SRF02)
{
	uint8_t 	data_to_write;

	data_to_write=0x51;
	i2c1_WriteRegBuffer(addr_SRF02, 0,  &data_to_write, 1);
}
//=================================================================
uint16_t captDistUS_Get(uint16_t addr_SRF02)
{
	uint16_t	distance;
	uint8_t		dist_h,dist_l;

	i2c1_ReadRegBuffer(addr_SRF02, 0x02, &dist_h, 1);
	i2c1_ReadRegBuffer(addr_SRF02, 0x03, &dist_l, 1);

	distance=(uint16_t)(((uint16_t)(dist_h)<< 8)+ (uint16_t)dist_l);

	return distance;
}
