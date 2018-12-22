/*
 * screenLCD.h
 */

#include "main.h"

#ifndef INC_SCREENLCD_H_
#define INC_SCREENLCD_H_


int screenLCD_Clear(void);
uint8_t	screenLCD_getID(void);
void screenLCD_SetBacklight(uint8_t value);
int screenLCD_ReadButtons(void);
void screenLCD_Write(char* string_to_write, uint8_t length, uint8_t x, uint8_t y);
void screenLCD_Test(void);







#endif /* INC_SCREENLCD_H_ */
