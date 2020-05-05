#ifndef __System_H
#define __System_H
#include "main.h"
 
#define POWER		P21	//mcu17
#define CHARGE_EN	P20  //3
#define BAT_V		P30	//mcu20
#define LINE_EN		P01	//muc10
#define AB			P10


typedef enum
{
	S_INIT,  
	START, 
	READY,
	SHUTDOWN,
	UHF_SET,
	UHF_CH,
	SET_OK,
	SET_ID,
	RAIL_DIS,
	SET_ID_PRESS,
	SET_VOL,
	SET_AUTOMUTE,
	SET_EQ,
	BAT_CHARGE,
	CHECK_DIS,
}S_STATE;


typedef struct{ 
	u16 s_delay; 
	u8 s_flag;
	u8 state; 
	u8 keymutetime;
	u8	start_flag;
	u16 stop_time; 
	u8 check;
}S_DATA;

extern S_DATA xdata Sdata;


 
void EnterStopMode(void);
void SysInit(void);
void SysStaDelay(void);
void SetSysDelay(u16 time);
void SysState(S_STATE state);
void StopDelay(void);

 void KeyMenu(void);

#endif
