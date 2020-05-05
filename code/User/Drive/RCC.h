#ifndef __RCC_H
#define __RCC_H			 
#include "main.h"

#define WDT_CLR0_RE  0x53 
#define WDT_CLR1_RE  0xAC 
#define WPKEY_WRITE_EN  0x37 



#define MASK_CRYIOEN_MCKS  0x08       //外部晶振。

#define MCLK_DIV1	0x03                //MCLK = SYSCLK
#define MCLK_DIV2	0x02                //MCLK 为 SYSCLK 的 2 分频
#define MCLK_DIV4	0x01                //MCLK 为 SYSCLK 的 4 分频
#define MCLK_DIV8	0x00                //MCLK 为 SYSCLK 的 8 分频



void IO_DeInit(void);
void IO_Initailize(void);
void T0_init(void);
void IO_init(void);
void Clr_wag(void);
void MCLKToRCH();
void Delay_ms(unsigned int i);
void USART_init(void);
void Extern0_init(void);
void Extern1_init(void);
void Delay_us(unsigned int i);
void Delay_ms(unsigned int i);
void stop_mode(void);

void SystemTimInit(void);
void Tim1Init(void);
#endif 