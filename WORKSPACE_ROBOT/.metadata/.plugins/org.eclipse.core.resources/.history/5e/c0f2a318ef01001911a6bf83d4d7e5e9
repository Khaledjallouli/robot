/*
 * screenLCD.c
 */

#include "screenLCD.h"
#include "drv_i2c.h"

#define	GET_PORT	0x03
#define	GET_BUT		0x05
#define GET_ID		0x20
#define GET_FRM     0x21
#define LCD_CLR		0x60
#define	LCD_WR		0x61
#define	SET_BL		0x62

/*************************************************************************
 *	DOCUMENTATON
 * https://www.olimex.com/Products/Duino/Shields/SHIELD-LCD16x2/open-source-hardware
**************************************************************************/

//=================================================================
//				LCD Clear
// 		Clears everything displayed on the lcd
//=================================================================
int screenLCD_Clear(void)
{
	uint8_t data_to_write;
	data_to_write=LCD_CLR;
	//i2c1_WriteRegBuffer(SCREEN_LCD_ADDRESS, LCD_CLR,  &data_to_write,1);
	i2c1_WriteBuffer(SCREEN_LCD_ADDRESS, &data_to_write, 1);
	HAL_Delay(100);
	screenLCD_getID();

	return 0;
}
//=================================================================
//				GET ID
//=================================================================
uint8_t	screenLCD_getID(void)
{
	uint8_t aRxBuffer = 0;
	 i2c1_ReadRegBuffer(SCREEN_LCD_ADDRESS, GET_ID, &aRxBuffer, 1);
	return aRxBuffer;
}
//=================================================================
//				SET BACK LIGHT
//=================================================================
void screenLCD_SetBacklight(uint8_t value)
{
	i2c1_WriteRegBuffer(SCREEN_LCD_ADDRESS, SET_BL,  &value,1);
}
//=================================================================
//				READ BUTTONS
//=================================================================
int screenLCD_ReadButtons(void)
{
	uint8_t buttons=0;
	 i2c1_ReadRegBuffer(SCREEN_LCD_ADDRESS, GET_BUT, &buttons, 1);
	return buttons;
}
//=================================================================
//				LCD Write
// Writes one character at time at position X, Y.
// X must be between 1 and 16. Y must be between 1 and 2.
//=================================================================
void screenLCD_Write(char* string_to_write, uint8_t length,  uint8_t X, uint8_t Y)
{
    uint8_t x, y;
    int i = 0;
    char message[3];
    x = X;
    y = Y;


    for(i=0 ; i<length ; i++)
    {
    	message[0]=y;
    	message[1]=x;
    	message[2]=string_to_write[i];
    	i2c1_WriteRegBuffer(SCREEN_LCD_ADDRESS, LCD_WR, (uint8_t*)message,3);
    	x++;
    	if(x > 15){
    	            x = 0;
    	            y++;
    	            if(y > 2)
    	                return;
    	        }
    	HAL_Delay(20);
    }

	screenLCD_getID();
}
//=================================================================
//		SCREEN LCD TEST
//=================================================================

void screenLCD_Test(void)
{
	uint8_t screen_id=0;
	uint8_t buttons=0;
	char mes[26]={"abcdefghijklmnopqrstuvwxyz"};

	screen_id=screenLCD_getID();
	term_printf("screen id = %d \n\r",screen_id);
	//screenLCD_Clear();
	buttons=screenLCD_ReadButtons();
	term_printf("buttons = %d \n\r",buttons);
	screenLCD_Write(mes, 26,  0, 0);
	screenLCD_SetBacklight(200);
	//screenLCD_Clear();
	screenLCD_Write(mes, 26,  0, 0);
}


