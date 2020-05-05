#include "main.h" 
#include "RCC.h"
#include "System.h" 
#include "OS.h"
#include "KeyBoard.h"
#include "UHF.h"
#include "ADC.h"
#include "Lcd.h"
#include "kt_0646m.h"
 
int main(void)
{
	LVRCON=0x85;	     //∑¿À¿ª˙
	Clr_wag();	
	MCLKToRCH();		 //…Ë÷√æßÃÂ
	IO_init(); 
	
	OSInit();
	SysInit();  
	LcdInit();
	KeyInit();
	AD_Init(CH7_P30); 
	CHIP_EN_OUT;
	CHIP_EN = Enable; 
	
	Sdata.stop_time = 5;	 
	SystemTimInit();
	Tim1Init(); 
	Extern0_init(); 

	while(1)
	{    
		OSTaskScan();
		SysStaDelay();	
		KeyMenu();
		
		
//		EnterStopMode(); 
	}
}
