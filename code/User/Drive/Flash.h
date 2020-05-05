#ifndef __Flash_H
#define __Flash_H		 
 
 #include "main.h"

#define FLASH_START_ADD       0xf0   //��ʼ��ַ
#define FLASH_MASK            0x12   //������

typedef enum
{
  FLASH_ID_MASK =0,					//ʶ���룬�����޸Ļ�ɾ��������
  FLASH_ID_MASK1,					//ʶ���룬�����޸Ļ�ɾ��������	
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

