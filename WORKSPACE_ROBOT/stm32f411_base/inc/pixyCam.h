/*
 * pixy.h
 */

#ifndef INC_PIXYCAM_H_
#define INC_PIXYCAM_H_

void pixyCam_Init(void);
int pixyCam_GetStart(void);
uint16_t pixyCam_GetBlocks(uint16_t maxBlocks);
void pixyCam_Get(uint16_t* tabXY, uint16_t* tabWH );
int pixyCam_SetServos(uint16_t s0, uint16_t s1);
int pixyCam_SetBrightness(uint8_t brightness);
int pixyCam_SetLED(unsigned char, unsigned char, unsigned char);
void pixyCam_Test(void);
uint8_t pixyCam_GetByte(uint8_t out);

#endif /* INC_PIXYCAM_H_ */
