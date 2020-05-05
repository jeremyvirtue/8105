#ifndef __Flash_H
#define __Flash_H		 
 
 #include "main.h"

#define FLASH_START_ADD       0xf0   //开始地址
#define FLASH_MASK            0x12   //检验码

typedef enum
{
  FLASH_ID_MASK =0,					//识别码，不能修改或删除！！！
  FLASH_ID_MASK1,					//识别码，不能修改或删除！！！	
  FLASH_ID_CHANNEL,
  FLASH_ID_VOLUME,
  FLASH_ID_SYSTEMID,
	FLASH_AUTOMUTE,
	FLASH_ID_AB,
	FLASH_ID_EQ,
}FlashId;

void FlashInit(void);
unsigned char FlashRead(FlashId addId);
FlagStatus FlashWrite(FlashId addId, u8 value);
FlagStatus FlashCheck(void);


#endif 

