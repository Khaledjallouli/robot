#include "main.h"

#define PIXY_ARRAYSIZE              100
#define PIXY_START_WORD             0xaa55
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_START_WORDX            0x55aa
#define PIXY_SERVO_SYNC             0xff
#define PIXY_CAM_BRIGHTNESS_SYNC    0xfe
#define PIXY_LED_SYNC               0xfd
#define PIXY_OUTBUF_SIZE            64

#define PIXY_SYNC_BYTE              0x5a  // to sync SPI data
#define PIXY_SYNC_BYTE_DATA         0x5b  // to sync/indicate SPI send data
#define PIXY_OUTBUF_SIZE            64

/**************************************************************
 	 	 	 DOCUMENTATION

http://www.cmucam.org/projects/cmucam5/wiki/Porting_Guide
**************************************************************/

typedef enum
{
    NORMAL_BLOCK,
    CC_BLOCK // color code block
} BlockType;

typedef struct
{
  uint16_t signature;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t angle; // angle is only available for color coded blocks
} Block;

extern uint8_t spi1Transfer(uint8_t);	// src/drv/src_spi.c
// communication routines
static uint16_t pixyCam_GetWord(void);
static int pixyCam_Send(uint8_t *data, int len);

// variables for a little circular queue for SPI output data
static uint8_t g_outBuf[PIXY_OUTBUF_SIZE];
static uint8_t g_outLen = 0;
static uint8_t g_outWriteIndex = 0;
static uint8_t g_outReadIndex = 0;

static int g_skipStart = 0;
static BlockType g_blockType;
static Block *g_blocks;

//=================================================================
//						PIXY CAM INIT
//=================================================================

void pixyCam_Init()
{
	  g_blocks = (Block *)malloc(sizeof(Block)*PIXY_ARRAYSIZE);
}
//=================================================================
//						PIXY CAM TEST
//=================================================================

void pixyCam_Test(void)
{

/*	pixyCam_SetLED(0,100,200);
	pixyCam_SetBrightness(100);*/

while(1)
{
	pixyCam_SetLED(200,100,200);
 	pixyCam_GetBlocks(1);
	term_printf_stlink("signature = %d \n\r",g_blocks->signature);
	term_printf_stlink("x = %d \n\r",g_blocks->x);
	term_printf_stlink("y = %d \n\r",g_blocks->y);
	term_printf_stlink("width = %d \n\r",g_blocks->width);
	term_printf_stlink("height = %d \n\r",g_blocks->height);
	term_printf_stlink("angle = %d \n\r",g_blocks->angle);
	HAL_Delay(500);

}
}

void pixyCam_Get(uint16_t* tabXY,uint16_t* tabWH)
{
	pixyCam_GetBlocks(1);
	tabXY[0]=g_blocks->x;
	tabXY[1]=g_blocks->y;

	tabWH[0]=g_blocks->width;
	tabWH[1]=g_blocks->height;


}

//=================================================================
//						PIXY CAM GET WORD
//=================================================================

uint16_t pixyCam_GetWord()
{
  // ordering is big endian because Pixy is sending 16 bits through SPI
  uint16_t w;
  uint8_t c, cout = 0;

  if (g_outLen)
  {
 w = spi1Transfer(PIXY_SYNC_BYTE_DATA);
    cout = g_outBuf[g_outReadIndex++];
    g_outLen--;
    if (g_outReadIndex==PIXY_OUTBUF_SIZE)
      g_outReadIndex = 0;
  }
  else
 w = spi1Transfer(PIXY_SYNC_BYTE); // send out sync byte
  w <<= 8;
c = spi1Transfer(cout); // send out data byte
  w |= c;

  return w;
}

//=================================================================
//						PIXY CAM SEND
//=================================================================

int pixyCam_Send(uint8_t *data, int len)
{
  int i;

  // check to see if we have enough space in our circular queue
  if (g_outLen+len>PIXY_OUTBUF_SIZE)
    return -1;

  g_outLen += len;
  for (i=0; i<len; i++)
  {
    g_outBuf[g_outWriteIndex++] = data[i];
    if (g_outWriteIndex==PIXY_OUTBUF_SIZE)
      g_outWriteIndex = 0;
  }


  return len;
}

//=================================================================
//						PIXY CAM GET START
//=================================================================

int pixyCam_GetStart(void)
{
  uint16_t w, lastw;

  lastw = 0xffff;

  while(1)
  {
    w = pixyCam_GetWord();
    if (w==0 && lastw==0)
      return 0; // no start code
    else if (w==PIXY_START_WORD && lastw==PIXY_START_WORD)
    {
      g_blockType = NORMAL_BLOCK;
      return 1; // code found!
    }
    else if (w==PIXY_START_WORD_CC && lastw==PIXY_START_WORD)
    {
      g_blockType = CC_BLOCK; // found color code block
      return 1;
    }
    else if (w==PIXY_START_WORDX)

    	spi1Transfer(0); // we're out of sync! (backwards)

    lastw = w;
  }
}

//=================================================================
//						PIXY CAM GET BLOCKS
//=================================================================

uint16_t pixyCam_GetBlocks(uint16_t maxBlocks)
{
  uint8_t i;
  uint16_t w, blockCount, checksum, sum;
  Block *block;

  if (!g_skipStart)
  {
    if (pixyCam_GetStart()==0)
      return 0;
  }
  else
    g_skipStart = 0;

  for(blockCount=0; blockCount<maxBlocks && blockCount<PIXY_ARRAYSIZE;)
  {
    checksum = pixyCam_GetWord();
    if (checksum==PIXY_START_WORD) // we've reached the beginning of the next frame
    {
      g_skipStart = 1;
      g_blockType = NORMAL_BLOCK;
      return blockCount;
    }
    else if (checksum==PIXY_START_WORD_CC)
    {
      g_skipStart = 1;
      g_blockType = CC_BLOCK;
      return blockCount;
    }
    else if (checksum==0)
      return blockCount;

    block = g_blocks + blockCount;

    for (i=0, sum=0; i<sizeof(Block)/sizeof(uint16_t); i++)
    {
      if (g_blockType==NORMAL_BLOCK && i>=5) // no angle for normal block
      {
        block->angle = 0;
        break;
      }
      w = pixyCam_GetWord();
      sum += w;
      *((uint16_t *)block + i) = w;
    }

    // check checksum
    if (checksum==sum)
      blockCount++;
    else
      term_printf_stlink("checksum error!\n");

    w = pixyCam_GetWord();
    if (w==PIXY_START_WORD)
      g_blockType = NORMAL_BLOCK;
    else if (w==PIXY_START_WORD_CC)
      g_blockType = CC_BLOCK;
    else
      return blockCount;
  }

  return 0;
}

//=================================================================
//						PIXY CAM SET BRIGHTNESS
//=================================================================

int pixyCam_SetBrightness(uint8_t brightness)
{
  uint8_t outBuf[3];

  outBuf[0] = 0x00;
  outBuf[1] = PIXY_CAM_BRIGHTNESS_SYNC;
  outBuf[2] = brightness;

  return pixyCam_Send(outBuf, 3);
}

//=================================================================
//						PIXY CAM SET LED
//=================================================================

int pixyCam_SetLED(unsigned char r, unsigned char g, unsigned char b)
{
  uint8_t outBuf[5];

  outBuf[0] = 0x00;
  outBuf[1] = PIXY_LED_SYNC;
  outBuf[2] = r;
  outBuf[3] = g;
  outBuf[4] = b;

  return pixyCam_Send(outBuf, 5);
}

//=================================================================

