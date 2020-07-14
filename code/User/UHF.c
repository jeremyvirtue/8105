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
//	freq = ((u32)u_dat.channel * FREQ_INC) + FREQA_INIT;
	freq = FREQ[u_dat.ab][u_dat.channel  -1];
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
//	FreqTune(FREQA_PUB);
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
	AuxDataEnSw(Disable);					//关Aux数据发送使能
	AuxDataEnSw(Enable);					//开Aux数据发送使能
	KT_WirelessMicTx_Mic_Sens(KT_FS_VOL); 
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


u32 code FREQ[2][100] = {
730300,
730600,
730900,
731200,
731500,
731800,
732100,
732400,
732700,
733000,
733300,
733600,
733900,
734200,
734500,
734800,
735100,
735400,
735700,
736000,
736300,
736600,
736900,
737200,
737500,
737800,
738100,
738400,
738700,
739000,
739300,
739600,
739900,
740200,
740500,
740800,
741100,
741400,
741700,
742000,
742300,
742600,
742900,
743200,
743500,
743800,
744100,
744400,
744700,
745000,
745300,
745600,
745900,
746200,
746500,
746800,
747100,
747400,
747700,
748000,
748300,
748600,
748900,
749200,
749500,
749800,
750100,
750400,
750700,
751000,
751300,
751600,
751900,
752200,
752500,
752800,
753100,
753400,
753700,
754000,
754300,
754600,
754900,
755200,
755500,
755800,
756100,
756400,
756700,
757000,
757300,
757600,
757900,
758200,
758500,
758800,
759100,
759400,
759700,
760000,

  
790000,
789700,
789400,
789100,
788800,
788500,
788200,
787900,
787600,
787300,
787000,
786700,
786400,
786100,
785800,
785500,
785200,
784900,
784600,
784300,
784000,
783700,
783400,
783100,
782800,
782500,
782200,
781900,
781600,
781300,
781000,
780700,
780400,
780100,
779800,
779500,
779200,
778900,
778600,
778300,
778000,
777700,
777400,
777100,
776800,
776500,
776200,
775900,
775600,
775300,
775000,
774700,
774400,
774100,
773800,
773500,
773200,
772900,
772600,
772300,
772000,
771700,
771400,
771100,
770800,
770500,
770200,
769900,
769600,
769300,
769000,
768700,
768400,
768100,
767800,
767500,
767200,
766900,
766600,
766300,
766000,
765700,
765400,
765100,
764800,
764500,
764200,
763900,
763600,
763300,
763000,
762700,
762400,
762100,
761800,
761500,
761200,
760900,
760600,
760300,

};


