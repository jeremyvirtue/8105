#include "UHF.h" 
#include "System.h"
#include "Lcd.h"
#include "kt_0646m.h" 
#include "RCC.h"
#include "Flash.h"
#include "LcdDis.h"
#include "ADC.h"

UHFDATA xdata u_dat;

void UhfDataInit(void)
{
//	u_dat.channel = 1;
//	u_dat.vol	  = KT_FS_VOL;
//	u_dat.id 	  = 0;
	ReadData();
	if(AB)
		u_dat.ab = 1;
	else
		u_dat.ab = 0; 
}

void ChAdd(void)
{
	u_dat.channel++;
	if(u_dat.channel>CHMAX)
	{
		u_dat.channel = CHMIN;
	}
}

void ChLess(void)
{	
	if(u_dat.channel==CHMIN)
	{
		u_dat.channel = CHMAX;
	}
	else
		u_dat.channel--;

}

void VolAdd(void)
{
	u_dat.vol++;
	if(u_dat.vol  > VOLMAX)
	{
		u_dat.vol = VOLMAX;
	}
}

void VolLess(void)
{	
	if(u_dat.vol  == VOLMIN)
	{
		u_dat.vol = VOLMIN; 
	}
	else
		u_dat.vol--; 
	
}

void EqAdd(void)
{
	u_dat.eq++;
	if(u_dat.eq  > EQMAX)
	{
		u_dat.eq = EQMIN;
	}
}

void EqLess(void)
{	
	if(u_dat.eq  == EQMIN)
	{
		u_dat.eq = EQMAX; 
	}
	else
		u_dat.eq--; 
	
}

void SetEqApi(u8 eq)
{
	switch(eq)
	{
		case 0:
			
		break;
	}
}

u32 SetFreq(void)
{
	u32 freq;
	freq = ((u32)u_dat.channel * FREQ_INC) + FREQA_INIT;
	return freq; 
}

void FreqTune(u32 freq)
{ 
	KT_WirelessMicTx_Pilot(PILOT_DISABLE);  //关闭导频	
	Delay_ms(100);
	KT_WirelessMicTx_Tune(freq);
	KT_WirelessMicTx_Pilot(PILOT_ENABLE);	//开启导频
	AuxDataEnSw(Disable);					//关Aux数据发送使能
	AuxDataEnSw(Enable);					//开Aux数据发送使能
 
}

void SetPubFreq()
{
	FreqTune(FREQA_PUB);
	if(u_dat.ab)
	{
		FreqTune(FREQB_PUB); 
	}
	else
	{
		FreqTune(FREQA_PUB); 
	}
}


 void KT0646mInit(void)
{	
	uint32_t count;
	UhfDataInit();
	CHIP_EN_OUT;
	CHIP_EN = Enable; 
	count = 80000;
	while(KT_Bus_Read46(0x01) != 0x4B54) 		//Read Manufactory ID 
	{
		count--;
		if(!count)
		{ 
			ShowNumber(8888);
			break;
		}
	} 
	KT_WirelessMicTx_Init(SetFreq()); 
	KT_WirelessMicTx_Mic_Sens(u_dat.vol); 
	KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);		//开启声音
	BPSKMode(order1);	 
}

void ReadData(void)
{
	if(FlashCheck())
	{
		u_dat.channel = FlashRead(FLASH_ID_CHANNEL);
		u_dat.vol = FlashRead(FLASH_ID_VOLUME);
		u_dat.id = FlashRead(FLASH_ID_SYSTEMID);
		u_dat.automute =  FlashRead(FLASH_AUTOMUTE);
		u_dat.eq =  FlashRead(FLASH_ID_EQ);
	}
	else
	{
		u_dat.channel = 1;
		u_dat.vol = KT_FS_VOL;
		u_dat.id = 0;
		u_dat.automute = 1;
		u_dat.eq = 0;
		FlashWrite(FLASH_ID_MASK,FLASH_MASK);
		FlashWrite(FLASH_ID_MASK1,FLASH_MASK);
		SaveData();
	}
}

 

void SaveData(void)
{
	FlashWrite(FLASH_ID_CHANNEL,u_dat.channel);
	FlashWrite(FLASH_ID_VOLUME,u_dat.vol);
	FlashWrite(FLASH_ID_SYSTEMID,u_dat.id);
	FlashWrite(FLASH_AUTOMUTE,u_dat.automute);
	FlashWrite(FLASH_ID_EQ,u_dat.eq);
}


u16  xdata BPSKbuf[4]={0,0,0,0};

 

void CleanBPSK()
{
	BPSKbuf[0] = 0x0000;
	BPSKbuf[1] = 0x0000;
	BPSKbuf[2] = 0x0000;
	BPSKbuf[3] = 0x0000;	
}
void BPSKMode(BPSKOrder order)
{
	CleanBPSK();
	BPSKbuf[0] |= order<<12;
	if(u_dat.ab)
		BPSKbuf[0] |= 3<<8;//品牌号
	else     
		BPSKbuf[0] |= 2<<8;//品牌号
	BPSKbuf[0] |= u_dat.vol;//音量值 0-31
	BPSKbuf[1] |= ((SetFreq()/100)>>8)<<8;
	BPSKbuf[1] |= 0xff - ((SetFreq()/100)>>8);
	BPSKbuf[2] |= (SetFreq()/100)<<8;
	BPSKbuf[2] |= 0xff - ((SetFreq()/100)&0x00ff);
	BPSKbuf[3] |= ((u16)u_dat.id)<<8;
	BPSKbuf[3] |= 0xff - u_dat.id;
	KTWriteBPSK(BPSKbuf);
}

void AutoMute()
{	//1开0关
	if(u_dat.automute)
	{
		if(KT_WirelessMicTxCheckVolume() && Sdata.state == READY)
		{
			if(u_dat.automute_time > 300)//开导频
			{
				KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);
				KT_WirelessMicTx_PASW(PA_ON); 
				ChannelDis();
			}
			else if(u_dat.automute_time > 10)//开声音
			{
				KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);
				ChannelDis();
			}
			u_dat.automute_time = 0;
		}
		else if(Sdata.state != READY)
			u_dat.automute_time = 0;
	} 
}

void AutoMuteDelay(void)
{ 
	if(u_dat.automute)
	{
		u_dat.automute_time++; 
	}
	
 
	if(u_dat.automute_time == 10 && Sdata.state == READY)
	{
			KT_WirelessMicTx_MuteSel(AUDIO_MUTE);//静音
	}
	else if(u_dat.automute_time == 300 && Sdata.state == READY)
	{
		KT_WirelessMicTx_PASW(PA_OFF);//关导频
	}
	else if(u_dat.automute_time == 900 && Sdata.state == READY)
	{
		SysState(SHUTDOWN);//关机
	} 
	
}


void GetVat()
{
	u16 val;
	val = Adc_Read();
	ShowNumber(val);
}

