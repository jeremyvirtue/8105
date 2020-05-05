#define _OS_C



#include "OS.h" 
#include "Lcd.h"
#include "LcdDis.h"
#include "UHF.h"
#include "System.h"
#include "KeyBoard.h"
#include "ADC.h"
#include "RCC.h"
#include "kt_0646m.h"
 
MyDelay  xdata taskDelay[MAXTASK];
OS 		 xdata os;

/***********************************************************多任务***********************************************************/

 void Test()
{
  static u16 i=1;
  ShowNumber(i++);
  if (i>9999)
    i=0;
}



/*------任务0------*/
static void Task0(void)
{	
	static u8 xdata num;
	AutoMuteDis();
	num++;
	if(num >= 2)
	{
		num = 0;
		AutoMuteDelay(); 
	} 
	if(Sdata.state != S_INIT)
		BatRead();  
	
	StopDelay();
	KeyMute();
	
	LedLampDelay();
} 

/*------任务1------*/
static void Task1(void)
{	
	static u8 xdata count = 0; 
	count++;
	if(count>=3)
	{
		count = 0;
		TwinkleDis();
	}
	StartDis();
	RailDis();
	AutoMute(); 
	
	u_dat.ramid++;
	if(u_dat.ramid == 255)
		u_dat.ramid = 1;
	
	if(u_dat.line_flag)
	{
		u_dat.line_flag = 0; 
		if(Sdata.state == S_INIT)
		{
			SysState(BAT_CHARGE);
			IO_Initailize();  
			POWER = 1;
			KeyInit();
			LcdInit(); 
			AD_Init(CH7_P30);  
			Sdata.stop_time = 5;
			CHIP_EN_OUT;
			CHIP_EN = Disable; 
		} 
	}
	
	if(Sdata.state == BAT_CHARGE)
	{
		if(!LINE_EN)
		{
			CHIP_EN_OUT;
			CHIP_EN = Enable; 
			Sdata.stop_time = 5;
			SysState(S_INIT);
		}
	}
} 

void OSTaskInit(void)
{
	//5ms
	u8   i=0;
	taskDelay[0].delay=100;		//1S
	taskDelay[1].delay=20;			//100ms	 
	
	for (i=0;i < MAXTASK;i++)
	{
	  taskDelay[i].counter=taskDelay[i].delay;
	}
	
}

/**         任务调度
*
*
*/
void OSTaskScan(void)
{
	u8  i=0;
  static   xdata void (*  Task[])()={&Task0,&Task1}; 

    for (i=0;i<MAXTASK;i++)
    {
      if (taskDelay[i].counter==0)
      {
        taskDelay[i].counter=taskDelay[i].delay;
        Task[i]();
      }
    }
}

void OSTick(void)
{ 
  u8 i; 
  for (i=0;i<MAXTASK;i++)
  {
    if (taskDelay[i].counter>0)
    {
      taskDelay[i].counter--;
    }				
  }
}


 
 

/**********************************************************功能任务*********************************************************/
/*        系统初始化
*   调用各子功能的初始化函数
*   
*/
void OSInit(void)
{	
  OSTaskScan();
  OSTick();  
  OSTaskInit(); 
}



