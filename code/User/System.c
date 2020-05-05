#include "System.h"  
#include "Lcd.h"
#include "LcdDis.h"
#include "kt_0646m.h"
#include "UHF.h"
#include "Flash.h"
#include "KeyBoard.h"
#include "RCC.h"
#include "ADC.h"
 
 
S_DATA xdata Sdata;
 
 
void SysInit(void)
{
	POWER = 0;//初始化POWER = 0
	Sdata.state = S_INIT;
	Sdata.start_flag = 0;
}


 extern u8 tw_time;//递减闪烁
void KeyMenu(void)
{
	if(keys.mute_flag)
	{
		keys.mute_flag = 0;
		keys.mute = 2;
		KT_WirelessMicTx_MuteSel(AUDIO_MUTE);
	}
/*************************	key_1	******************************/
	switch(keys.key_num)
	{
		case K1_P:  
			keys.key_num = 0; 
			break;
		case K1_R: 
			keys.key_num = 0; 	
			if((Sdata.state == READY ||Sdata.state == START || Sdata.state == SET_AUTOMUTE)  && Sdata.start_flag == 0)///确认开机标志位
			{
				Sdata.start_flag = 1;
			}	
			else if(Sdata.state == SHUTDOWN )//|| Sdata.state == S_INIT)
			{  
				Sdata.stop_time = 12;
			}
			
			if(Sdata.state == READY )
			{
				Sdata.check = 0;
				SysState(CHECK_DIS);
			}
			else if(Sdata.state == CHECK_DIS)
			{
				SysState(CHECK_DIS);
			}
			
			break;
		case K1_C0_3S:  
			if(Sdata.state == S_INIT || Sdata.state ==BAT_CHARGE)//开机
			{
				SysState(START);
			}	
			break; 
		case K1_C1S:
			if(Sdata.state == READY && Sdata.start_flag )
			{
				Sdata.start_flag = 0;//关机标志位
				Sdata.stop_time = 12;
				SysState(SHUTDOWN);
			} 
		break;
		case K1_C10S:
			if(Sdata.state == S_INIT )//继续长按调节自动静音
			{ 
				SysState(SET_AUTOMUTE);
			}
		break;
/*******************************************************/
			
/*************************	key_2	******************************/
		case K2_P:  
			if(Sdata.state == UHF_SET)//进入CH模式
			{	
				tw_time = 4;
				SysState(UHF_CH);
			}
			else if(Sdata.state == UHF_CH)
			{	
				tw_time = 4;
				ChAdd();
				SysState(UHF_CH);
			}
			else if(Sdata.state == SET_VOL)
			{
				VolAdd();
				SysState(SET_VOL);
			}
			keys.key_num = 0; 
			break;
		case K2_R: 
			keys.key_num = 0; 
			if(Sdata.state == UHF_SET|| Sdata.state == UHF_CH )//快速调节初始化
			{
				u_dat.quickpress = 0;
			} 
			else if(Sdata.state == READY && Sdata.start_flag == 1)//进入调节音量模式
			{
				ShowIco(LCD_ICON_DB,SET);
				SysState(SET_VOL);
			}
			break;
		case K2_C0_5S:  
			keys.key_num = 0; 
			if(Sdata.state == READY)//开机长按进入调台
			{
				tw_time = 4;
				SysState(UHF_SET); 
			}  
			if(Sdata.state == UHF_CH)//确认进入快速调节
			{
				keyContinedClean();
				u_dat.quickpress = 1;
			}
			break; 
		case K2_C80MS:  
			keys.key_num = 0;  
			if(Sdata.state == UHF_CH && u_dat.quickpress)//快速调节
			{
				tw_time = 4;
				keyContinedClean();
				ChAdd();
				SysState(UHF_CH);	
			}
		break;
/*******************************************************/

/**********************		key3 	*********************************/
		case K3_P:  
			if(Sdata.state == UHF_SET)//进入CH模式
			{	
				tw_time = 4;
				SysState(UHF_CH);
			}
			else if(Sdata.state == UHF_CH)
			{	
				tw_time = 4;
				ChLess();
				SysState(UHF_CH);
			}
			else if(Sdata.state == SET_VOL)
			{
				VolLess();
				SysState(SET_VOL);
			}
			keys.key_num = 0; 
			break;
		case K3_R: 
			keys.key_num = 0; 
			if(Sdata.state == UHF_SET|| Sdata.state == UHF_CH )//快速调节初始化
			{
				u_dat.quickpress = 0;
			} 
			else if(Sdata.state == READY  )//进入调节音量模式
			{
				ShowIco(LCD_ICON_DB,SET);
				SysState(SET_VOL);
			}
			break;
			break;
		case K3_C0_5S: 
			keys.key_num = 0; 
			if(Sdata.state == READY)//开机长按进入调台
			{
				tw_time = 4;
				SysState(UHF_SET); 
			}
			if(Sdata.state == UHF_CH)//确认进入快速调节
			{
				keyContinedClean();
				u_dat.quickpress = 1;
			}
			break; 
		case K3_C80MS:  
			keys.key_num = 0;  
			if(Sdata.state == UHF_CH && u_dat.quickpress)//快速调节
			{
				tw_time = 4;
				keyContinedClean();
				ChLess();
				SysState(UHF_CH);	
			}
		break;
/*******************************************************/
			
/************************key_4*******************************/
		case K4_P:  
			keys.key_num = 0; 
//			if(Sdata.state == SET_EQ)
//			{
//				EqAdd();
//				SysState(SET_EQ);
//			} 
			break;
		case K4_R: 
			keys.key_num = 0; 
//			if(Sdata.state == READY && Sdata.start_flag == 1)//进入调节音量模式
//			{ 
//				SysState(SET_EQ);
//			}
			break;
		case K4_C0_5S: 
			if(Sdata.state == READY)
		    {
				SysState(SET_ID);
			}
			keys.key_num = 0; 
			break; 
/*******************************************************/
		
/**********************twins*********************************/
		case K1_K2_TWINS:
//			if(Sdata.state == READY)
//		    {
//				SysState(SET_ID);
//			}
			keys.key_num = 0; 
		break;
/*******************************************************/		
	}
}
 

 
void SysState(S_STATE state)
{
	Sdata.state = state;
	switch(state)
	{
		case S_INIT:  
			 
			break;  
		case START: 
		break;
		case READY:  
			BPSKMode(order1);
 			MuteLconDis();		
			LockLconDis();
			ChannelDis();
		break;
		case SHUTDOWN: 
			KT_WirelessMicTx_MuteSel(AUDIO_MUTE); 
			KT_WirelessMicTx_Pilot(PILOT_DISABLE);
			LcdClean(); 
			OffDis();
			SetSysDelay(200);
		break;
		case UHF_SET:
			SetPubFreq();
			BPSKMode(order2);	
			SetDis();
			SetSysDelay(1000);
		break;
		case UHF_CH:
			ChannelDis();
			BPSKMode(order2);	
			SetSysDelay(1000); 
		break;
		case SET_OK:  
			KT_WirelessMicTx_PAGain(PA_Pos18dBm);
			FreqTune(SetFreq());
			SaveData();
			OkDis(); 
			SetSysDelay(120);
		break;
		case SET_ID: 
			KT_WirelessMicTx_PASW(PA_ON);
			KT_WirelessMicTx_PAGain(PA_Neg7dBm);
			if(u_dat.id)
				u_dat.id = 0;
			else
				u_dat.id = u_dat.ramid;	
			LockLconDis();
			IdDis();
			SetPubFreq(); 
			BPSKMode(order3);
			SetSysDelay(800);
		break;
		case RAIL_DIS: 	
		break;
		case SET_ID_PRESS: 
			IdDis();
		break;
		case SET_VOL: 
			VolDis();
			BPSKMode(order1);	
			SetSysDelay(400);
		break;
		case SET_AUTOMUTE:
		{  
			Sdata.stop_time = 5;	
			KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);
			KT_WirelessMicTx_PASW(PA_ON);
			if(u_dat.automute)
				u_dat.automute = 0;
			else
				u_dat.automute = 1; 
			MuteLconDis();
			AutoMuteSwDis(); 
			SetSysDelay(400);
		}break;
		case SET_EQ:
			EqDis();
			SetEqApi(u_dat.eq);
			SetSysDelay(400);
		break;
		case BAT_CHARGE:
	 
		break;
		case CHECK_DIS:
			CheckDis();
			SetSysDelay(200);
		break;
	} 
}

void SetSysDelay(u16 time)
{
	Sdata.s_delay = time;
}

void SysStaDelay(void)
{ 
	if(Sdata.s_delay > 0)
		Sdata.s_flag = 1;
	if(Sdata.s_flag && Sdata.s_delay == 0)
	{
		Sdata.s_flag = 0;
		switch(Sdata.state)
		{
			case S_INIT:   
 
				break; 
			case START:  
			break;		
			case READY:
				
			break;	
			case SHUTDOWN: 
				KT_WirelessMicTx_PASW(PA_OFF);
				LcdClean();
				LcdClose();
				if(LINE_EN)//如果此时插入充电线，那就进入充电状态，否则，INIT
				{
//					POWER= 0;
//					GPIO_SET(P2MDL,GPIO_OP,2);//chip_en
					SysState(BAT_CHARGE);
					CHIP_EN_OUT;
					CHIP_EN = Disable; 
				}
				else
					SysState(S_INIT); 
			break;
			case UHF_SET:
				FreqTune(SetFreq());
				SysState(RAIL_DIS);
			break;
			case UHF_CH:  
				BPSKMode(order4); 
				SysState(RAIL_DIS);	
			break;
			case SET_OK:  
				MuteLconDis();		
				LockLconDis();
				ChannelDis(); 
				SysState(READY); 
			break;
			case SET_ID:   
				BPSKMode(order4); 
				SysState(RAIL_DIS);
			break;
			case RAIL_DIS:

			break;
			case SET_VOL: 
				FlashWrite(FLASH_ID_VOLUME,u_dat.vol);
				ShowIco(LCD_ICON_DB,RESET);
				SysState(READY);
			break;
			case SET_AUTOMUTE:
				SysState(RAIL_DIS);
			break;
			case SET_ID_PRESS: 
				 
			break;
			case SET_EQ:
				FlashWrite(FLASH_ID_EQ,u_dat.eq);
				SysState(READY);
			break;
			case BAT_CHARGE:
				 
			break;
			case CHECK_DIS:
				ShowIco(LCD_ICON_DB,RESET);
				SysState(READY);
			break;
		}
	} 
}

 
 
 /*****************************************
          check enter stop mode 
******************************************/
void EnterStopMode(void)
{ 
		Delay_ms(100);
 
		IO_DeInit();  
 
 
	/*******************  key	**********************/
		GPIO_SET(xP5MDL,GPIO_UI,0);// 
		GPIO_SET(P1MDL,GPIO_UI,1);// 
		GPIO_SET(P1MDL,GPIO_UI,2);// 
		GPIO_SET(P1MDL,GPIO_UI,3);// 
	/*****************************************/
		
	/*******************  adc_bat	**********************/ 
		AD_DeInit();
		GPIO_SET(P3MDL,GPIO_OI,0);
	/*****************************************/
	
	 
	
	/*************		LED	***************/
		LcdClose();
	/*******************************/
		
/*************	0646	***************/
//	POWER = 1; 
	GPIO_SET(P2MDL,GPIO_PP,2);//chip_en
	CHIP_EN = Enable;  
	CHIP_EN = Disable;  
	/*******************************/
	
// 	/*************	other	***************/
 
	GPIO_SET(P2MDL,GPIO_PP,1);
	POWER = 0; 
		/*power
		  line_en
		*/
	GPIO_SET(P0MDL,GPIO_OI,1);//mcu15
//	GPIO_SET(P1MDL,GPIO_OI,1);
	/*******************************/	
 
//	if(!LINE_EN)
		stop_mode();
//	else
//		SysState(BAT_CHARGE);
 
}

void StopDelay(void)
{
	
	if(Sdata.stop_time > 0 && Sdata.state == S_INIT) 
	{
//		ShowNumber(Sdata.stop_time);
		Sdata.stop_time--;
		
		if(Sdata.stop_time == 0)
		{
			EnterStopMode();
		}
	}
 
}

