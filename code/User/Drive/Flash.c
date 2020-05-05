/*        E2PROM 256 字节
*
*
*/ 
#include "Flash.h"
#include "RCC.h"




void FlashTest(void);
void FlashStart(void);

void FlashInit(void)
{	
	FlashCLKDiv = 25;			//MCLK 4MHz

 
}


void FlashTimer1Init(void)
{
  ET1=0;
  TR1=0;
  TH1=0x05;
  TL1=0x05;
  ET1=1;
  TR1=1;
}


void FlashTimer1Close(void)
{
  ET1=0;
  TR1=0;
  
	TH1 = 253;	//(256-253)*256/8M = 200us
	TL1 = 253;	
  TR1=1;
  Tim1Init();
}

unsigned char FlashRead(FlashId addId)
{
  u8 re;
  u8 add=FLASH_START_ADD+addId;
  FlashAddrL = add<<1;
	FlashAddrH = add>>7;
  FlashCtrl= 0x0b;      //读E2PROM区 
  re=FlashDataL;
  return re;
}

static FlagStatus FlashWriteInside(FlashId addId, u8 value)
{
  u8 tem;
  FlagStatus re =SET;
  u8 add=FLASH_START_ADD+addId;
//  ET0 = 0;
  FlashAddrL = add<<1;
	FlashAddrH = add>>7; 
  FlashCtrl= 0x0b;      //读E2PROM区 
  tem =FlashDataL;
  if (tem!=value)
  {
    FlashAddrL = add<<1;
    FlashAddrH = add>>7; 
    FlashDataL = value;
    FlashTimer1Init();
    FlashKey = 0xA5;
    FlashKey = 0xF1;
    FlashCtrl= 0x09;      //写E2PROM区  
    FlashTimer1Close();
    FlashAddrL = add<<1;
    FlashAddrH = add>>7; 
    FlashCtrl= 0x0b;      //读E2PROM区 
    tem=FlashDataL;
    if (tem!=value)
      re = RESET;
  }
//  ET0 = 1;
  return re;
}

FlagStatus FlashWrite(FlashId addId, u8 value)
{
  u8 i=10;
  FlagStatus re =RESET;
  do
  {
    re=FlashWriteInside(addId,value);
  }while(!re && i>0);
  return re;
}

FlagStatus FlashCheck(void)
{
  if (FlashRead(FLASH_ID_MASK)==FLASH_MASK && FlashRead(FLASH_ID_MASK1)==FLASH_MASK)
    return SET;
  else
    return RESET;
}

