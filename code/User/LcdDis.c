#include "LcdDis.h"
#include "Lcd.h"
#include "UHF.h"
#include "System.h" 
#include "kt_0646m.h"
#include "KeyBoard.h"
#include "ADC.h"
#include "RCC.h"

void ChannelDis(void)
{
	u8 ch;
	if(u_dat.ab)
	{
		ch = u_dat.channel + CHMAX;
		ShowChar(LCD_DIGITAL_1,CHAR_B);
		if(ch == 100)
			ShowChar(LCD_DIGITAL_2,CHAR__1);
		else
			ShowChar(LCD_DIGITAL_2,CHAR__);
		ShowChar(LCD_DIGITAL_3,ch%100/10);
		ShowChar(LCD_DIGITAL_4,ch%10); 
			
	}
	else
	{
		ShowChar(LCD_DIGITAL_1,CHAR_A);
		ShowChar(LCD_DIGITAL_2,CHAR__);
		ShowChar(LCD_DIGITAL_3,u_dat.channel%100/10);
		ShowChar(LCD_DIGITAL_4,u_dat.channel%10);
	}
}

void OffDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_XX);
	ShowChar(LCD_DIGITAL_2,CHAR_0);
	ShowChar(LCD_DIGITAL_3,CHAR_F);
	ShowChar(LCD_DIGITAL_4,CHAR_F);
}

void SetDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_5);
	ShowChar(LCD_DIGITAL_2,CHAR_E);
	ShowChar(LCD_DIGITAL_3,CHAR_L);
	ShowChar(LCD_DIGITAL_4,CHAR_XX);
}

void OkDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_XX);
	ShowChar(LCD_DIGITAL_2,CHAR_0);
	ShowChar(LCD_DIGITAL_3,CHAR_k);
	ShowChar(LCD_DIGITAL_4,CHAR_XX);
}

void IdDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_XX);
	ShowChar(LCD_DIGITAL_2,CHAR_1);
	ShowChar(LCD_DIGITAL_3,CHAR_d);
	ShowChar(LCD_DIGITAL_4,CHAR_XX);
}

void VolDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_U);
	ShowChar(LCD_DIGITAL_2,CHAR__);
	ShowChar(LCD_DIGITAL_3,CHAR_0);
	ShowChar(LCD_DIGITAL_4,u_dat.vol);
}

void EqDis(void)
{
	ShowChar(LCD_DIGITAL_1,CHAR_E);
	ShowChar(LCD_DIGITAL_2,CHAR_C);
	ShowChar(LCD_DIGITAL_3,CHAR__);
	ShowChar(LCD_DIGITAL_4,u_dat.eq);
}


void LockLconDis(void)
{
	if(u_dat.id)
		ShowIco(LCD_ICON_LOCK, SET);
	else
		ShowIco(LCD_ICON_LOCK, RESET);
}

void MuteLconDis(void)//亮关灭开
{
	if(u_dat.automute)
		ShowIco(LCD_ICON_SIGNAL,RESET);
	else
		ShowIco(LCD_ICON_SIGNAL,SET);
}

void AutoMuteSwDis(void)
{
	if(u_dat.automute)
	{
		ShowChar(LCD_DIGITAL_1,CHAR_A);
		ShowChar(LCD_DIGITAL_2,CHAR_0);
		ShowChar(LCD_DIGITAL_3,CHAR_n);
		ShowChar(LCD_DIGITAL_4,CHAR_XX);
	}
	else
	{
		ShowChar(LCD_DIGITAL_1,CHAR_A);
		ShowChar(LCD_DIGITAL_2,CHAR_0);
		ShowChar(LCD_DIGITAL_3,CHAR_F);
		ShowChar(LCD_DIGITAL_4,CHAR_F);
	}
}

void CheckDis(void)
{
	Sdata.check = ~Sdata.check;
	if(Sdata.check)
	{
		VolDis();
		ShowIco(LCD_ICON_DB,SET);
	}
	else
	{
		ChannelDis();
		ShowIco(LCD_ICON_DB,RESET);
	}
}
 
/*开机显示，100ms进入一次*/
void StartDis(void)
{
	static u8 xdata num = 0;
	if(Sdata.state == START)
	{
		num++;
		switch(num)
		{
			case 1:
				IO_Initailize();
				POWER = 1;
				KeyInit();
				LcdInit(); 
				AD_Init(CH7_P30);  
				 
				ShowChar(LCD_DIGITAL_1,CHAR_U);
				ShowChar(LCD_DIGITAL_2,CHAR_H);
				ShowChar(LCD_DIGITAL_3,CHAR_F);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);
			break;
			case 10:
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_H);
			break;
			case 12:
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_H);
				ShowChar(LCD_DIGITAL_4,CHAR_0);	
			break;
			case 14:
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_H);
				ShowChar(LCD_DIGITAL_3,CHAR_0);
				ShowChar(LCD_DIGITAL_4,CHAR_1);	
			break;
			case 16:
				ShowChar(LCD_DIGITAL_1,CHAR_H);
				ShowChar(LCD_DIGITAL_2,CHAR_0);
				ShowChar(LCD_DIGITAL_3,CHAR_1);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);	 
				 
			break;
			case 18:
				num = 0;
				KT0646mInit(); 
				SysState(READY);
			break;
		}
	}
}

 void RailDis(void)
 {
	static u8 xdata num = 0;
	if(Sdata.state == RAIL_DIS)
	{
		num++;
		switch(num)
		{	
			case 1:
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);
			break;
			case 2:
				ShowChar(LCD_DIGITAL_1,CHAR__);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);	
			break;
			case 5:
				ShowChar(LCD_DIGITAL_1,CHAR__);
				ShowChar(LCD_DIGITAL_2,CHAR__);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);	
			break;
			case 9:
				ShowChar(LCD_DIGITAL_1,CHAR__);
				ShowChar(LCD_DIGITAL_2,CHAR__);
				ShowChar(LCD_DIGITAL_3,CHAR__);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);	
			break;
			case 12:
				ShowChar(LCD_DIGITAL_1,CHAR__);
				ShowChar(LCD_DIGITAL_2,CHAR__);
				ShowChar(LCD_DIGITAL_3,CHAR__);
				ShowChar(LCD_DIGITAL_4,CHAR__);		
			break;
			case 15:
				num = 0;
				SysState(SET_OK);
			break;
		}
	}
 }
 

/**/
void BatRead(void)
{
	static u8 twbat;
	float bat_v;
	u16 ad;
//	u16 bat_v;
	if(Sdata.state != SHUTDOWN && Sdata.state != START )
	{
		if(!LINE_EN)
		{ 
			ad = Adc_Read();
			bat_v = ad/(8.19);
//			 
			bat_v = bat_v-20;
//			ShowNumber(bat_v); 
			if(bat_v > 380) // 
			{ 
				ShowBattery(LCD_BATTERY_4);
			}
			else if(bat_v > 360)// 
			{ 
				ShowBattery(LCD_BATTERY_3);
			}
			else if(bat_v > 340)// 
			{ 
				ShowBattery(LCD_BATTERY_2);
			}
//			else if(bat_v > 2900)//3.5
//			{ 
//				ShowBattery(LCD_BATTERY_1);
//			}
			else if(bat_v > 320)//3.3
			{
				twbat = ~twbat;
				if(twbat) { 
					ShowBattery(LCD_BATTERY_1);	
				}
				else  
					ShowBattery(LCD_BATTERY_0);
			}
			else if(bat_v>0)
			{ 
				ShowBattery(LCD_BATTERY_0);
				SysState(SHUTDOWN);
			}
			else
			{ 
//				KT0646mInit(); 
			} 
		}
	
		else if(LINE_EN)
		{//+10
			 
			ad = Adc_Read();
			bat_v = ad/(8.18); 
//	     	ShowNumber(bat_v);
			if(bat_v > 413) //4.1
			{ 
				ShowBattery(LCD_BATTERY_4);
			}
			else if(bat_v > 390)//3.8
			{ 
				twbat = ~twbat;
				if(twbat)
					ShowBattery(LCD_BATTERY_3);
				else
					ShowBattery(LCD_BATTERY_4);
			}
			else if(bat_v > 370)//3.6 2格闪烁
			{ 
				twbat = ~twbat;
				if(twbat)
					ShowBattery(LCD_BATTERY_2);
				else
					ShowBattery(LCD_BATTERY_3);
			}
			else if(bat_v > 0)//3.5  1格闪烁
			{ 
				twbat = ~twbat;
				if(twbat)
					ShowBattery(LCD_BATTERY_1);
				else
					ShowBattery(LCD_BATTERY_2);
			}  
			else
			{ 
//				KT0646mInit(); 
			} 
		}
	}
}	

u8 tw_time;
void TwinkleDis(void)
{
	static u8 num = 0;  
	if(tw_time)
	{
		tw_time--; 
	}
	if(!tw_time)
	{
		num = ~num;
		if(Sdata.state == UHF_SET )
		{  
			if(num)
			{
				SetDis();
			}
			else
			{ 
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);
			}
		}
		if(Sdata.state == UHF_CH )
		{ 
			if(num)
			{
				ChannelDis();
			}
			else
			{ 
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);
			}
		}
		if(Sdata.state == SET_ID )
		{ 
			if(num)
			{
				IdDis();
			}
			else
			{ 
				ShowChar(LCD_DIGITAL_1,CHAR_XX);
				ShowChar(LCD_DIGITAL_2,CHAR_XX);
				ShowChar(LCD_DIGITAL_3,CHAR_XX);
				ShowChar(LCD_DIGITAL_4,CHAR_XX);
			}
		}
	}
}


void AutoMuteDis(void)
{
	static u8 xdata a  =0;
	if(u_dat.automute_time>10 && Sdata.state == READY &&u_dat.automute) 
	{ 
		a++;
		if(a == 1 )
		{
			ShowChar(LCD_DIGITAL_1,CHAR_XX);
			ShowChar(LCD_DIGITAL_2,CHAR_0);
			ShowChar(LCD_DIGITAL_3,CHAR_0);
			ShowChar(LCD_DIGITAL_4,CHAR_XX);
		}
		else if(a == 2)
		{
			ShowChar(LCD_DIGITAL_1,CHAR_XX);
			ShowChar(LCD_DIGITAL_2,CHAR_XX);					
			ShowChar(LCD_DIGITAL_3,CHAR_XX);
			ShowChar(LCD_DIGITAL_4,CHAR_XX);
			a = 0;
		}	
	}
}


