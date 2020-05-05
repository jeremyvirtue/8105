//*****************************************************************************
//  File Name:    KT_WirelessMicTxdrv.c
//  Function:    KT Wireless Mic Transmitter Products Driver For Customer
//                (KT064xM)
//*****************************************************************************
//        Revision History
//  Version Date        Description
//  V0.1    2016-04-26  For KT0646M_VX
//  V0.2    2016-06-01  ����VX��VX2�ı���ѡ��    
//  V0.3    2016-08-18  For KT0646M_VX4
//  V0.3.1  2016-08-24  ɾ��KT_WirelessMicTx_Init������һЩ�ظ�����
//  V0.4    2016-08-26  ������XTAL_DUAL����
//  V0.5    2016-10-11  �޸��˳�ʼ�������е�һЩ���ã���0x25,0x26�Ĵ��������üӵ��˳�ʼ���������棬
//                  �ڳ�ʼ����������set pilot frequency
//  V0.5.1  2016-10-17  �����޸���һ������ĺ궨�壬������RXISKT0616M����BPSK�ľ�ģʽ��Ȼ���ٸ���
//                  �Ƿ���˫�����KT0616Mѡ����ĳ���ӽ�ȥ��
//  V0.5.2  2016-11-15  ��tunęǰ��lo_fine_vref_sel��Ϊ3��tune���ĳ�0.
//  V0.5.3  2016-12-15  �ڳ�ʼ���а�lo_fine_vref_sel��Ϊ3��������tunę��ʱ���������޸���.Ϊ���¶�
//                  �仯�����������⣬�������DOUBLE_KVCO��Χ�Ĵ���
//  V0.6    2017-02-08  ��ʽ�淶������
//  V1.1    2017-04-27  ɾ����һЩ��ʼ����������û�õĶ���������Щ��Сд��ĸ����ĺ궨��ĳ��˴�д����ĸ
//----------------------------------------------------------
// Includes
//---------------------------------------------------------- 
#include "kt_0646m.h"
#include <intrins.h>
#include <stdlib.h> 
#include "System.h"
#include "Lcd.h"
#include "RCC.h"

 




//KTxxM kt0646;
u8 xdata displayTime=0;

static void KTNop()
{
//  os.DelayMS(1);
}



/*        ���߷����ֽ�����
* 
* 
* 
*/
static  void KTTxByte(u8 by)
{
	u8 i;
  u8 tem=0;
//  SDA_OUT();
	for (i=0;i<8;i++)
	{	
    KTNop();
    tem=by & 0x80;
		if (tem!=0x80)
			SDA_RESET;
		else
			SDA_SET;
    KTNop();
		by = by<<1;
    KTNop();
		SCL_SET;
    KTNop();
		SCL_RESET;
    KTNop();
	}
    KTNop();
}

/*        ���߽����ֽ�����
* 
* 
* 
*/
static u8 KTRxByte(void)
{
  u8 i,re=0;
  SDA_IN();
  for (i=0;i<8;i++)
  {
    re <<=1;
    KTNop();
    SCL_SET;
    KTNop();
    re |=SDA_READ;
    KTNop();
    SCL_RESET;
  }
    KTNop();
  SDA_OUT();
  return re;
}

/*        ������Ӧ
* re:SET-��Ӧ��   RESET-��Ӧ��
* 
* 
*/
static FlagStatus KTAck(void)
{
  FlagStatus re;
  SDA_IN();
  KTNop();
  SDA_SET;
  KTNop();
  SCL_SET;
  KTNop();
  KTNop();
  re =(FlagStatus)SDA_READ;
  KTNop();
  SCL_RESET;
  KTNop();
  SDA_OUT();
  return (FlagStatus)(!re);
}

/*        ���߿�ʼ
* 
* 
* 
*/
static void KTStart(void)
{
  SDA_OUT();
  SCL_OUT();
  KTNop();
	SDA_SET;
  KTNop();
	SCL_SET;
  KTNop();
	SDA_RESET;
  KTNop();
	SCL_RESET;
  KTNop();
}
/*        ���߽���
* 
* 
* 
*/
static void KTStop(void)
{
  SDA_OUT();
  KTNop();
  SCL_RESET;
  KTNop();
  SDA_RESET;
  KTNop();
  SCL_SET;
  KTNop();
  SDA_SET;
  KTNop();
}

/*        ���豸������
* devAdd:�豸��ַ
* regAdd:�豸�ϵļĴ�����ַ
* 
u8 ReadDeviceByte(u8 devAdd,u8 regAdd)
{
  u8 re=0;
  KTStart();
  KTTxByte(devAdd & 0xFE);
  if (KTAck())
  {
    KTTxByte(regAdd);
    if (KTAck())
    {
      KTStart();
      KTTxByte(devAdd & 01);
      if (KTAck())
      {
        re=KTRxByte();
        KTAck();
      }
    }
  }
  KTStop();
  return re;
}
*/

static u16 KTReadDeviceWord(u8 devAdd,u8 regAdd)
{
  u16 re=0;
  KTStart();
  KTTxByte(devAdd & 0xFE);
  if (KTAck())
  {
    KTTxByte(regAdd);
    if (KTAck())
    {
      KTStart();
      KTTxByte(devAdd | 0x01);
      if (KTAck())
      {
        re=KTRxByte()<<8;
        KTNop();
        SDA_RESET;
        KTNop();
        SCL_SET;
        KTNop();
        SCL_RESET;
        KTNop();
        SDA_SET;
        KTNop();
        re |=KTRxByte();
        KTNop();
      }
    }
  }
  
  KTStop();
  return re;
}


static void WriteDeviceWord(u8 devAdd,u8 regAdd,u16 da)
{
  u8 daL,daH;
  daL=da;
  daH=da>>8;
  KTStart();
  KTTxByte(devAdd & 0xFE);
  if (KTAck())
  {
    KTTxByte(regAdd);
    if (KTAck())
    {
      KTTxByte(daH);      
      if (KTAck())
      {
        KTTxByte(daL);
        KTAck();
      }
    }
  }  
  SCL_RESET;
  KTStop();
}



/**       ��KT0646M�Ĵ���д������
	������Register �Ĵ�����ַ��Word_Dataд�������
	����ֵ����
*/ 
void KT_Bus_Write46(uint8_t Register_Address, uint16_t Word_Data)
{
	WriteDeviceWord(KTWirelessMicTxw_address,Register_Address,Word_Data);
}
/**       ��KTоƬ�Ĵ�������
	������Register_Address �Ĵ�����ַ
	����ֵ����ȡ��������
*/
uint16_t KT_Bus_Read46(uint8_t Register_Address)
{
	return( KTReadDeviceWord(KTWirelessMicTxr_address, Register_Address) );
}


uint8_t KT_WirelessMicTx_Init(uint32_t Freq)
{
	uint16_t regx;		
    regx = KT_Bus_Read46(0x03);
    KT_Bus_Write46(0x03, (regx & 0x7FFF) | (WAKEUP << 15)); //Write Standby bit to 0
    Delay_ms(50);
    regx = KT_Bus_Read46(0x03);
    KT_Bus_Write46(0x03, (regx & 0xfffe) | PA_SEL);
    regx = KT_Bus_Read46(0x24);
    KT_Bus_Write46(0x24, (regx & 0xEFFF) | (BATTERY_METER_ENABLE << 12));
    //ref_vtr_vth_sel = 1
    regx=KT_Bus_Read46(0x47);                        
    KT_Bus_Write46(0x47,(regx | 0x0200));
    //vref_mon_en=1
    regx = KT_Bus_Read46(0x0a);
    KT_Bus_Write46(0x0a, regx | 0x0200);  
    regx = KT_Bus_Read46(0x1C);
    KT_Bus_Write46(0x1C, (regx & 0xF1E1) | ( FDEV_MONITOR_TC_250ms << 10 ) | (COMPANDOR_ENABLE<<4) | 
                 ( PRE_EMPHASIS_ENABLE << 9 ) | ( COMPANDOR_TC_12ms << 1 ));
   // KT_WirelessMicTx_Mic_Sens(0);   //������Ϊ��С 
		//KT_WirelessMicTx_MuteSel(AUDIO_MUTE);	//�ر����� 
    /*cic overflow detect enable*/
    regx = KT_Bus_Read46(0x1e); 
    KT_Bus_Write46(0x1e, (regx & 0xffdf)|(1<<5)); 

    regx=KT_Bus_Read46(0x30);
    KT_Bus_Write46(0x30, ( regx & 0x8000 ) | (AGC_VHIGH << 11) | (AGC_VLOW << 7) | (AGC_ATTACK << 4) | 
                 (AGC_RELEASE << 1) | AGC_DIS );
 
 
    regx=KT_Bus_Read46(0x31);
    KT_Bus_Write46( 0x31, ( regx & 0xff00 ) | (GAIN_SEL << 6) | (COMPEN_GAIN << 4) | 
                  (BLANK_EN << 3) | BLANK_TIME );

    regx=KT_Bus_Read46(0x39);
    KT_Bus_Write46(0x39,(regx & 0xFC00) | (HARD_LIMIT << 6) | (CPRS_1XLPF_BP << 5) | 
                 (CPRS_KNEE_DIS << 4) | CPRS_THRSH);

    KT_Bus_Write46( 0x3a,(ALC_DIS << 15) | (ALC_SOFTKNEE << 14) | (ALC_VMAX << 7) | 
                  (ALC_ATTACK << 4) | ALC_RELEASE );


	#ifdef SILENCE_MUTE
    regx=KT_Bus_Read46(0x25);
    KT_Bus_Write46( 0x25,(regx&0xc000)|(SLNC_MUTE_DIS << 13) | (SLNC_MUTE_TIME << 8) | 
                 (SLNC_MUTE_LOW_LEVEL << 4) | SLNC_MUTE_HIGH_LEVEL );
    regx=KT_Bus_Read46(0x26);
    KT_Bus_Write46( 0x26,(regx&0xfffb)|(SILENCE_MUTE_ACT_MCU << 2));
	#endif

	/*************���������ŵ�******************/
	regx=KT_Bus_Read46(0x1f);
	KT_Bus_Write46(0x1f,(regx&0x80f0)|(AUXDATA_EN << 14)|(AUX_REG_NUM << 12)|(AUX_CARRY_NUM46 << 9) | BPSK_NEW_MODE46); 
	KT_Bus_Write46(0x20,(AUX_ADDRB << 8) | AUX_ADDRA);
	KT_Bus_Write46(0x21,(AUX_ADDRD << 8) | AUX_ADDRC);  

			
    #ifdef OTHER_RX
        #ifdef XTAL_24M_ONLY
        KT_WirelessMicTx_Set_Pilot_Freq(XTAL_24M_FREQ); //set pilot frequency
        #endif
        #ifdef XTAL_24P576M_ONLY
        KT_WirelessMicTx_Set_Pilot_Freq(XTAL_24P576M_FREQ); //set pilot frequency
        #endif
    #endif
    //for VCO unlock because of temperature change
    regx=KT_Bus_Read46(0x10);
    KT_Bus_Write46(0x10,(regx|0x0010)); //vco_ldo_calicode=1.4v
    regx=KT_Bus_Read46(0x45);
    KT_Bus_Write46(0x45,((regx&0xfff0)|0x0007));

    regx=KT_Bus_Read46(0x2d);
    KT_Bus_Write46(0x2d,(regx&0xfff8)|3); //lofine_vref_sel=0.4v

    #ifdef pll_unlock 
        regx = KT_Bus_Read46(0x2f);                
        KT_Bus_Write46(0x2f, regx|0x0080); //pll_unlock_en
        regx = KT_Bus_Read46(0x44);                
        KT_Bus_Write46(0x44, (regx&0x1fff)|(1<<13)); //lo_lock_hth_vsel
        regx = KT_Bus_Read46(0x44);                
        KT_Bus_Write46(0x44, (regx&0xe3ff)|(3<<10)); //lo_lock_lth_vsel
        regx = KT_Bus_Read46(0x44);                
        KT_Bus_Write46(0x44, regx&0xfdff); //lo_lock_det_pd
    #endif
	//***************************************************************
	#ifdef OPEN_BAT	 	//ʹ��KT�ڲ���ؼ�⹦��
		KT_WirelessMicTx_BatteryMeter_SW(BATTERY_METER_ENABLE);	//�򿪵�ؼ�⹦��
	#endif

	if(KT_WirelessMicTx_Tune(Freq))											//����Ƶ������
	{
		KT_WirelessMicTx_PAGain(PA_Pos18dBm);								//PA��������
		KT_WirelessMicTx_PASW(PA_ON);										//PA��	
		KT_WirelessMicTx_Pilot_Fdev(PILOT_FDEV_FREQ);						//��Ƶ�źŵ���Ƶƫ��С����	
		KT_WirelessMicTx_Pilot(PILOT_ENABLE);								//����32.768KHz��Ƶ�ź�	
//		SendAuxData(NORMAL_WORK,Msystem.Volume,Freq/100,Msystem.DevID);	//����ȷ��AUX �źŸ�����
		return(1);//��ʼ����ȷ
	}
	return(0);	//��ʼ������
}


/******************************************************
  �� �� ����KT_WirelessMicTx_PASW												 	
  ����������PA�򿪡��رճ���														
  ����˵������������оƬ�򿪻��߹ر�PA												
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()											
  ȫ�ֱ�����																		
  ��    �룺bPA_Switch																
  ��    �أ���ȷ��1					����0																										 	
*******************************************************/
uint8_t B_open_PA;
uint8_t KT_WirelessMicTx_PASW(uint8_t bPA_Switch)
{		   
//#define PA_OFF 0
//#define PA_ON  1
	uint16_t regF;
	B_open_PA = bPA_Switch;		//���ñ��
	regF = KT_Bus_Read46(0x0F);	 
    KT_Bus_Write46(0x0F, (regF & 0xFFF7) | ( (uint8_t)bPA_Switch << 3 ));
	return(1);
}


/*******************************************************
  �� �� ����KT_WirelessMicTx_PAGain												 	
  ����������PA�������																
  ����˵����cPaGain��ΧΪ0-12����13��												
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()											
  ȫ�ֱ�����																		
  ��    �룺cPaGain																	
  ��    �أ���ȷ��1					����0																						 	
********************************************************/
uint8_t KT_WirelessMicTx_PAGain(uint8_t cPaGain)
{
	uint16_t reg11;
	reg11 = KT_Bus_Read46(0x11);
	KT_Bus_Write46(0x11, (reg11 & 0xFF00) | cPaGain );		

	return(1);	
}


/*********************************************************
  �� �� ����KT_WirelessMicTx_Mic_Sens											 	
  ����������Mic�����ȵ���															
  ����˵����cMicSensΧΪ0-15����16��												
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()											
  ȫ�ֱ�����																		
  ��    �룺cMicSens																
  ��    �أ���ȷ��1					����0																											 	
**********************************************************/
uint8_t KT_WirelessMicTx_Mic_Sens(uint8_t cMicSens)
{
	uint16_t reg1C;

	reg1C = KT_Bus_Read46(0x1C);
	KT_Bus_Write46(0x1C, (reg1C & 0xFE1F) | ( (uint16_t)cMicSens << 5 ));

	return(1);
}

/**************************************************************
  �� �� ����KT_WirelessMicTx_MuteSel											 	
  �����������������ܴ򿪡��رճ���													
  ����˵��������ѡ��򿪻��߹رվ�������											
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()											
  ȫ�ֱ�����																		
  ��    �룺bMute_Sel																
  ��    �أ���ȷ��1					����0																								 	
***************************************************************/
uint8_t B_mute;
uint8_t KT_WirelessMicTx_MuteSel(uint8_t bMute_Sel)
{
	uint16_t reg1C;
//#define	AUDIO_UNMUTE	0    //��������
//#define	AUDIO_MUTE		1    //����
	B_mute =  bMute_Sel;
	reg1C = KT_Bus_Read46(0x1C);
	KT_Bus_Write46(0x1C, (reg1C & 0xFFFE) | bMute_Sel);      				//Write Mute bit

	return(1);
}
/************************************************************************
  �� �� ����KT_WirelessMicTx_Calc_ChanReg                                    
  ���������������Ƶ�ʿ����ּ���                                                
  ����˵����������KHzΪ��λ��VCO��Ƶ��;                                            
            ����������*chan_ptr,*chan_frac_ptr,*chan_frac_msb_ptr��                
  ȫ�ֱ�����                                                                        
  ��    �룺Freq ��������KHzΪ��λ��VCOƵ�ʣ�                                        
  ��    �أ���ȷ��1    ����0                                                            
*************************************************************************/
//lopa_div1 * lopa_div2
uint8_t code lopa_div_tab[13]=  
{
    6, 8, 10, 12,
      16, 20, 24,
      32, 40, 48,
      64, 80, 96
};

//reg0x08<bit9:8> and <bit7:6>
uint8_t code lopa_div_tab2[13][2]= 
{
     {0,0},{0,1}, {0,2}, {0,3},
           {1,1}, {1,2}, {1,3},
           {2,1}, {2,2}, {2,3},
           {3,1}, {3,2}, {3,3}
};


uint8_t KT_WirelessMicTx_Calc_ChanReg(int32_t Freq, uint8_t  *lopa_div1_ptr,uint8_t  *lopa_div2_ptr,
                                   uint16_t  *chan_ptr, uint16_t  *chan_frac_ptr, 
                                   uint8_t  *chan_frac_msb_ptr, uint32_t *chan_frac_temp_ptr,int32_t xtal_freq)
{
    uint32_t chan_frac;
    int32_t Fvco;
    uint32_t temp,tempMin=xtal_freq;
//    double chan_frac_d;
//    double chan_frac_temp_d;
    uint16_t i = 12;
    uint8_t lopa_div;
//    uint16_t chan_temp;
    long vco_highth = 4320000; //VCO Range:4.32G-5.76G
    
    //lodiv ����ֵ
    lopa_div = vco_highth / Freq;

    //lodiv ʵ��ֵ
    for(i=0; i<12; i++)
    {
        if(lopa_div < lopa_div_tab[i])
        {            
            break;                                                   
        }
    }
    //���lopa_div1��lopa_div2
    *lopa_div1_ptr = lopa_div_tab2[i][1];
    *lopa_div2_ptr = lopa_div_tab2[i][0];
    
    //����VCO Ƶ��
    Fvco = Freq * lopa_div_tab[i];
    //����
    *chan_ptr = Fvco / (xtal_freq * 7) + 1; //dll_mode : *7
    //С��
//    chan_frac_d = Fvco;
//    chan_frac_d = chan_frac_d / (xtal_freq * 7);     //31.1221
//    chan_frac_d = chan_frac_d - (*chan_ptr);
//    chan_frac_d = chan_frac_d * 65536;                 //-57532.95
//    chan_frac = chan_frac_d;
    chan_frac= (((Fvco % (xtal_freq * 7))-(xtal_freq * 7))<<12)/((xtal_freq * 7)>>4);

    *chan_frac_msb_ptr = (chan_frac & 0x00030000) >> 16 ; //reg0x08<bit1:0>
    *chan_frac_ptr = chan_frac & 0x0000ffff; //reg0x09

//    chan_temp = Freq / xtal_freq + 1;
//    chan_frac_temp_d = Freq;
//    chan_frac_temp_d = chan_frac_temp_d / xtal_freq - chan_temp;
//    *chan_frac_temp_ptr = chan_frac_temp_d;

//    *chan_frac_temp_ptr= ((xtal_freq>>1)-abs(((Freq%xtal_freq)-(xtal_freq>>1))))*(3072000/xtal_freq);
    
    for(i=1;i<4;i++)
    {
        temp = ((xtal_freq/(2*i))-abs(((Freq%(xtal_freq/i))-(xtal_freq/(2*i)))))*i;
        if(temp<tempMin)
        {
            tempMin=temp;
        }
    }
    i=8;
    temp = ((xtal_freq/(2*i))-abs(((Freq%(xtal_freq/i))-(xtal_freq/(2*i)))))*i;
    if(temp<tempMin)
    {
        tempMin=temp;
    }
    *chan_frac_temp_ptr=tempMin*(3072000/xtal_freq);        
    return(1);
}




//-----------------------------------------------------------------------------
//�� �� ����KT_WirelessMicTx_Tune                                                     
//��������������Ƶ�����ú���                                                        
//����˵����������KHzΪ��λ�ķ���Ƶ�ʣ�                                                
//ȫ�ֱ�����                                                                        
//��    �룺Freq ��������KHzΪ��λ�ķ���Ƶ�ʣ�                                        
//��    �أ���ȷ��1                 ����0                                            
//�� �� �ߣ�Zhou Dongfeng           ʱ�䣺2016-04-05                                         
//�� �� �ߣ�Zhou Dongfeng           ʱ�䣺2016-08-26                                         
//��    ����V0.1    For KT0646M_VX
//          V0.2    �޸��˱�������ķ�ʽ��������VX��VX2�ĺ궨�壬
//                  �޸��˽��DLL���������ֳ����λ��
//                  ȥ���˲��õ�chan_cfg2����
//                  ȥ����MCU_POWER_OKλ�Ĳ�ѯ����
//                  ȥ����PLL�������ж�
//          V0.4    ͳһ�˱��������ʽ
//-----------------------------------------------------------------------------

uint8_t KT_WirelessMicTx_Tune(int32_t Freq)
{
	  uint16_t S_PLL_delay46;
    uint16_t chan0;
    uint16_t chan_frac0;
    uint8_t chan_frac_msb0;
    uint8_t lopa_div10,lopa_div20;
    volatile  uint16_t regx,regy;
    uint32_t chan_frac_temp0;    
    uint16_t state;	 
	
	
	#ifdef OPEN_EQ
    	KT_WirelessMicTx_EQSW(0);  //�ر�EQ
	#endif
    #ifdef DOUBLE_KVCO
        regx=KT_Bus_Read46(0x2d); //kvco_cali_bps=0
        KT_Bus_Write46(0x2d, (regx&0xf7ff));
    
        regx=KT_Bus_Read46(0x0a); //locpcali_bps=0
        KT_Bus_Write46(0x0a, (regx&0xffef));
        regx=KT_Bus_Read46(0x3d);
        KT_Bus_Write46(0x3d, (regx&0xffbf));              
    
        regx=KT_Bus_Read46(0x3c);
        KT_Bus_Write46(0x3c, (regx&0xfffd)); //loamp_cali_bps=0
    #endif    
	
//    regx = KT_Bus_Read46(0x2d);
//    KT_Bus_Write46(0x2d, (regx&0xfff8)|0x0003); //lo_fine_vref_sel
#ifdef XTAL_24M_ONLY
    KT_WirelessMicTx_Calc_ChanReg(Freq, &lopa_div10, &lopa_div20, &chan0, &chan_frac0, 
                                  &chan_frac_msb0,&chan_frac_temp0, 24000);
#endif
    KT_Bus_Write46(0x08,(chan0 << 10) | (lopa_div10 << 8) | (lopa_div20 << 6) | (0 << 5) | 
                 (0 << 4) | (0 <<2) | chan_frac_msb0); //
    KT_Bus_Write46(0x09, chan_frac0|0x0001);

    //dllδ�������л��������Ҫrst
    regx = KT_Bus_Read46(0x0e);
    KT_Bus_Write46(0x0e, regx | 0x0080); //dll_rst is from regbank
    regx = KT_Bus_Read46(0x0e);
    KT_Bus_Write46(0x0e, regx | 0x0100); //dll_rst=1
    Delay_ms(2);
    regx = KT_Bus_Read46(0x0e);
    KT_Bus_Write46(0x0e, regx & 0xfeff); //dll_rst=0

    regx=KT_Bus_Read46(0x0a);
    KT_Bus_Write46(0x0a,regx|0x0020); //tune

    regx=KT_Bus_Read46(0x0d);
    regx = (regx&0x0800)>>11;
		S_PLL_delay46 = 300;//2s
    while(!regx) //wait pll ready
    {
		Delay_ms(10);
        regx=KT_Bus_Read46(0x0d);
        regx = (regx&0x0800)>>11;  
				S_PLL_delay46--;
				if(!S_PLL_delay46) 
    		return(0);
    }
 
    #ifdef DOUBLE_KVCO
        regx=KT_Bus_Read46(0x2e); //double+16MHz/V locoarse_var_sel
        state=regx&0x1C00;
        state=state>>10;
        if(state >= 3)
        {
            state = 7;                                
        }
        else
        {
            state = (state<<1) + 3;
        }
        regx=(regx&0xe3ff)|(state<<10);
                                           
        regy=KT_Bus_Read46(0x2d); //kvco_cali_bps=1
        KT_Bus_Write46(0x2d, (regy|0x0800));              
    
        KT_Bus_Write46(0x2e, regx); //write locoarse/lofine_var_sel
    
        regx=KT_Bus_Read46(0x2a); //write cp_code
        state=(regx&0x007e)>>1;
        regx=KT_Bus_Read46(0x3d);
        KT_Bus_Write46(0x3d, (regx&0xff80)|(1<<6)|state);
    
        regx=KT_Bus_Read46(0x0a); //locpcali_bps=1
        KT_Bus_Write46(0x0a, (regx|0x0010));              
    
        regx=KT_Bus_Read46(0x3c);
        KT_Bus_Write46(0x3c, (regx|0x0002)); //loamp_cali_bps=1
    
        regx=KT_Bus_Read46(0x0a);
        KT_Bus_Write46(0x0a,regx|0x0020); //tune
    
        regx=KT_Bus_Read46(0x0d);
        regx = (regx&0x0800)>>11;
				S_PLL_delay46 = 300;//2s
        while(!regx) //wait pll ready
        {
					
					regx=KT_Bus_Read46(0x0d);
					regx = (regx&0x0800)>>11;
					Delay_ms(10);
					S_PLL_delay46--;
					if(!S_PLL_delay46) 
						return(0);
        }
    #endif
	Delay_ms(10);
	#ifdef OPEN_EQ
    	SettingEQ();  //����EQ
	#endif
	
//	regx=KT_Bus_Read46(0x1f);
//	KT_Bus_Write46(0x1f, regx & (~0x4000));	//bpsk data disable
//	regx=KT_Bus_Read46(0x1f);
//	KT_Bus_Write46(0x1f, regx | 0x4000);	//bpsk data Enable
			
  return(1);
}






#ifdef OPEN_BAT	 			//ʹ��KT�ڲ���ؼ�⹦��
/*****************************************************************
  �� �� ����KT_WirelessMicTx_BatteryMeter_SW									 	
  ������������ص�ѹ��⹦�ܴ򿪡��رճ���											
  ����˵����ѡ��򿪻��߹رյ�ص�ѹ��⹦��										
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()											  
  ȫ�ֱ�����																		
  ��    �룺bBatteryMeter_En														
  ��    �أ���ȷ��1					����0											
******************************************************************/
uint8_t KT_WirelessMicTx_BatteryMeter_SW(uint8_t bBatteryMeter_En)
{
	uint16_t reg24;

	reg24 = KT_Bus_Read46(0x24);
	KT_Bus_Write46(0x24, (reg24 & 0xEFFF) | ( (uint16_t)bBatteryMeter_En << 12));

	return(1);
} 


/*********************************************************************
   �� �� ����KT_WirelessMicTx_BatteryMeter_Read									 	
  ������������ص�ѹ��ȡ����														
  ����˵������ȡ��ǰ�ĵ�ص�ѹ������ֵΪ0-2047������								
  ���ú�����KT_Bus_Read46()															
  ȫ�ֱ�����																		
  ��    �룺��																		
  ��    �أ�reg7 & 0x07FF��Ϊ0-2047��������															
********************************************************************/
uint16_t KT_WirelessMicTx_BatteryMeter_Read(void)
{
	uint16_t reg7;
	reg7 = KT_Bus_Read46(0x07);
	return( reg7 & 0x07FF );
}


#endif
/*********************************************************************************************
  �� �� ����KT_WirelessMicTx_PowerDownProcedure											 	 	
  �����������ػ��������														 	
  ����˵����																 	
  ���ú�����KT_WirelessMicTx_MuteSel();KT_WirelessMicTx_Pilot();KT_WirelessMicTx_PAGain();
 			      KT_WirelessMicTx_PASW();KT_Bus_Read46();KT_Bus_Write46();Delay_ms();												 	
  ȫ�ֱ�������																 	
  ��    �룺��;														 	
  ��    �أ���																 															 	
**********************************************************************************************/
void KT_WirelessMicTx_PowerDownProcedure(void)
{
	uint16_t regx;       	  
	//KT_WirelessMicTx_MuteSel(AUDIO_MUTE);	//�ر����� 
	KT_WirelessMicTx_PAGain(0); 
	KT_WirelessMicTx_PASW(PA_OFF);		    //PA�ر�  
	regx=KT_Bus_Read46(0x0a);
	KT_Bus_Write46(0x0a,regx|0x1000);	   				//recali 
	regx = KT_Bus_Read46(0x03);
	KT_Bus_Write46(0x03, regx | (STANDBY << 15));   	//Write Standby bit to 1
//	Delay_ms(5);
	
	/*regx=KT_Bus_Read46(0x0a);
	KT_Bus_Write46(0x0a,regx|0x1000);	   				//recali

	regx = KT_Bus_Read46(0x03);
	KT_Bus_Write46(0x03, regx | (STANDBY << 15));   	//Write Standby bit to 1
//	Delay_ms(20);*/

}



#ifdef	OPEN_ECHO		//�Ƿ�򿪻��칦��
/***************************************************************************
  �� �� ����KT_WirelessMicTx_ECHO                                        
  ����������ECHO�������ó���                                                
  ����˵��������ECHO����Ч��                
  ȫ�ֱ�����                                                                        
  ��    �룺bEcho_Dis    ��ECHO���أ�
             Echo_Ratio     ��ECHO������                                        
             Echo_Delay     ��ECHO��ʱ��
  ��    �أ���                                                                                                                   
***************************************************************************/
void KT_WirelessMicTx_ECHO(uint8_t bEcho_Dis,uint8_t Echo_Ratio,uint8_t Echo_Delay)
{
    uint16_t regx;

	//if(!Echo_Ratio)
	//	bEcho_Dis = 1;//�رջ���	

    KT_Bus_Write46( 0x32, (ECHO_MCU << 15) | ((uint8_t)bEcho_Dis << 14) | (ECHO_STRU << 13) | 
                 (Echo_Ratio << 8) | (Echo_Delay << 3) | ECHO_GAINUP );
    
    regx = KT_Bus_Read46(0x33);
    KT_Bus_Write46( 0x33, (regx & 0xFFFC) | ECHO_GAINDOWN );                          
}	
#endif



#ifdef	OPEN_EQ	 	//�Ƿ��EQ����
/******************************************************
  �� �� ����KT_WirelessMicTx_EQSW										
  ����������EQ���������س���												
  ����˵��������EQ�����������ر�				
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()								
  ȫ�ֱ�����																		
  ��    �룺bEq_Dis	��EQ���أ�
  ��    �أ���															
*******************************************************/
void KT_WirelessMicTx_EQSW(uint8_t bEq_Dis)
{
	uint16_t regx;

	regx = KT_Bus_Read46(0x34);
	KT_Bus_Write46(0x34, ((regx & 0x7FFF) | (uint16_t)bEq_Dis << 15));
}


/***************************************************************
  �� �� ����KT_WirelessMicTx_EQGAIN										
  ����������EQ���������ó���												
  ����˵��������EQ��������Ƶ������Ч��				
  ���ú�����KT_Bus_Read46()��KT_Bus_Write46()								
  ȫ�ֱ�����																		
  ��    �룺Eq_Freq ��EQƵ�ʣ�										
 			Eq_Gain ��EQ���棩
  ��    �أ���															
****************************************************************/
void KT_WirelessMicTx_EQGAIN(uint8_t Eq_Freq,uint8_t Eq_Gain)
{
	uint16_t regx;
	uint8_t temp1,temp2;	 
    //if(Eq_Gain > EQ_GAIN_Pos12dB)
     //   Eq_Gain = EQ_GAIN_Pos12dB;  //��ֹEQ ���㳬�����
	temp1=Eq_Freq/3+0x34;
	temp2=(2-(Eq_Freq%3))*5;
	regx = KT_Bus_Read46(temp1);
	KT_Bus_Write46(temp1, ((regx & ~(0x001f<<temp2)) | ( (uint16_t)Eq_Gain << temp2 )));
}  
#endif

   
#ifdef KT_RX   		//ʹ��KT����
/***********************************************************
  �� �� ����KT_WirelessMicTx_Pilot                                                     
  ����������32.768KHz��Ƶ�źŴ򿪡��رճ���                                            
  ����˵��������ѡ���Ƿ�ʹ��32.768KHz��Ƶ�ź�                                        
  ȫ�ֱ�����                                                                        
  ��    �룺bPilot_Dis                                                                
  ��    �أ���ȷ��1                 ����0                                                                                                          
************************************************************/
uint8_t KT_WirelessMicTx_Pilot(uint8_t bPilot_Dis)
{
    uint16_t reg1F;

    reg1F = KT_Bus_Read46(0x1F);
#ifdef OTHER_RX	 	//��ʹ��KT ���� 
    KT_Bus_Write46(0x1F, (reg1F & 0xFFBF) | ( (uint8_t)bPilot_Dis << 6 ));
#endif
#ifdef KT_RX	 	//ʹ��KT����
    KT_Bus_Write46(0x1F, (reg1F & 0x7FFF) | ( (uint16_t)bPilot_Dis << 15 ));
#endif
    Delay_ms(20);
    return(1);
}


/*********************************************************
  �� �� ����KT_WirelessMicTx_Pilot_Fdev                                                 
  ����������32.768KHz��Ƶ�źŵ���Ƶƫ��С���ó���                                    
  ����˵����cPilot_FdevΧΪ0-3����4��                                                
  ȫ�ֱ�����                                                                        
  ��    �룺cPilot_Fdev                                                                
  ��    �أ���ȷ��1                 ����0                                            
**********************************************************/
uint8_t KT_WirelessMicTx_Pilot_Fdev(uint8_t cPilot_Fdev)
{
    uint16_t reg1F;

    reg1F = KT_Bus_Read46(0x1F);
#ifdef OTHER_RX
    KT_Bus_Write46(0x1F, (reg1F & 0xFFCF) | (cPilot_Fdev << 4));
#endif
#ifdef KT_RX
    KT_Bus_Write46(0x1F, (reg1F & 0xFE7F) | ((uint16_t)cPilot_Fdev << 7));
#endif
    Delay_ms(20);
    return(1);
}
#endif


#ifdef RXISKT0616M_XTAL_DUAL
/****************************************************************************
  �� �� ����KT_WirelessMicTx_Calc_ChanReg                                    
  ���������������Ƶ�ʿ����ּ���                                                
  ����˵����������KHzΪ��λ��VCO��Ƶ��;                                            
             ����������*chan_ptr,*chan_frac_ptr,*chan_frac_msb_ptr��                
  ȫ�ֱ�����                                                                        
  ��    �룺Freq ��������KHzΪ��λ��VCOƵ�ʣ�                                        
  ��    �أ���ȷ��1    ����0                                                            
*****************************************************************************/
uint8_t KT_WirelessMicTx_Calc_ChanReg_Old(int32_t Freq, uint16_t *chan_ptr, INT16 *chan_frac_ptr, 
                                       uint8_t *chan_frac_msb_ptr, uint16_t xtal_freq)
{
    *chan_ptr = Freq / xtal_freq;
    Freq = Freq % xtal_freq; 
    *chan_frac_ptr = (Freq << 16) / xtal_freq;
    if ((Freq <= 40) && (Freq >= 0))
    {
        *chan_frac_ptr = 0xffff;
        *chan_frac_msb_ptr =3;
    }
    else if ((Freq < xtal_freq ) && (Freq >= xtal_freq - 40))
    {
        (*chan_ptr)++; 
        *chan_frac_ptr = 0xffff;
        *chan_frac_msb_ptr = 3;
    }
    else if ( (Freq >= (xtal_freq / 2 - 40)) && (Freq <= (xtal_freq / 2 + 40)) )
    {
        *chan_frac_ptr = 0x7fff;
        *chan_frac_msb_ptr = 0;
    }
    else if ( Freq > (xtal_freq >> 1) )
    {
        (*chan_ptr)++; 
        *chan_frac_msb_ptr = 3;
    }
    else    
    {
        *chan_frac_msb_ptr = 0;
    }
    return(1);
}

bit selectXtalOld(int32_t Freq)
{
    uint16_t chan0,chan1;
    INT16 chan_frac0,chan_frac1;
    uint8_t chan_frac_msb0,chan_frac_msb1;
    INT16 mod0,mod1,mod2,mod3;

    Freq<<=1;
    KT_WirelessMicTx_Calc_ChanReg_Old(Freq, &chan0, &chan_frac0, &chan_frac_msb0,24000);
    KT_WirelessMicTx_Calc_ChanReg_Old(Freq, &chan1, &chan_frac1, &chan_frac_msb1,24576);
    mod0 = chan_frac0;
    mod1 = chan_frac1;
    mod2 = chan_frac0 << 1;
    mod3 = chan_frac1 << 1;
    if(mod0 < 0)
        mod0=~mod0;             //mod0=abs(mod0);
    if(mod1 < 0)
        mod1=~mod1;             //mod1=abs(mod1);
    if(mod2 < 0)
        mod2=~mod2;             //mod2=abs(mod2);
    if(mod3 < 0)
        mod3=~mod3;             //mod3=abs(mod3);
    if(mod2 < mod0)
        mod0 = mod2;
    if(mod3 < mod1)
        mod1 = mod3;
    if(mod0<mod1)
    {
        return(XTAL_24P576M_FREQ);
    }
    else 
        return(XTAL_24M_FREQ);
}
#endif

 


//------------------------------------------------------------------------------------
//�� �� ����ZK_set_EQ
//��������:	����EQ����
//��ƹ�˾������ÿо�Ƽ����޹�˾
//�� �� �ߣ����Ĳ�					ʱ�䣺2018��1��6��
//�� �� �ߣ�						ʱ�䣺	
//��    ����V1.0		
//-----------------------------------------------------------------------------------
#ifdef OPEN_EQ			
uint8_t code EqTable[15] = 
{
	12,12,10,11,11,
	11,11,12,12,12,
	12,13,14,13,12
};
void SettingEQ(void)
{
	uint8_t i;
    KT_WirelessMicTx_EQSW(1);  //��EQ
	for(i=0;i < 15;i++)
	{	 
    	KT_WirelessMicTx_EQGAIN(i,EqTable[i]);
	}

}

#endif
void AuxDataEnSw(uint8_t State)
{
	uint16_t regx;
	
	if(State)
	{
		/*enable send aux Data*/
		regx  = KT_Bus_Read46(0x1f);
		regx |= (0x01 << 14);
		KT_Bus_Write46(0x1f,regx);
		Delay_ms(20);
	}
	else
	{
		/*disable send aux Data*/
		regx  = KT_Bus_Read46(0x1f);
		regx &= ~(0x01 << 14);
		KT_Bus_Write46(0x1f,regx);
		Delay_ms(20);
	}
}

 void KTWriteBPSK(u16 * buf)
{
//  KT_SetAuxDataState(RESET);
//  KT_SetAuxDataState(SET);
	KT_Bus_Write46(AUX_ADDRA,buf[0]);
	KT_Bus_Write46(AUX_ADDRB,buf[1]);
	KT_Bus_Write46(AUX_ADDRC,buf[2]);
	KT_Bus_Write46(AUX_ADDRD,buf[3]);
//  KT_SetAuxDataState(RESET);
//  KT_SetAuxDataState(SET);
}

 /*�Զ���������  0 open 1 close*/
void AutoMuteOn(u8 flag)
{
	u16 regx;
	regx = KT_Bus_Read46(0x25);
	regx = regx & 0xdfff;//1101 1111 1111 1111
//	regx = regx | 0x0000;
	regx = regx | (u16)~flag<<13;
	KT_Bus_Write46(0x25,regx);
//	KT_Bus_Write( 0x25,(regx&0xc000)|(flag << 13) | (SLNC_MUTE_TIME << 8) | 
//	             (SLNC_MUTE_LOW_LEVEL << 4) | SLNC_MUTE_HIGH_LEVEL );
	
}

/*����Զ�����*/
FlagStatus KT_WirelessMicTxCheckVolume(void)
{
	if(!(0x4000&(KT_Bus_Read46(0x25))))//������
	{	
		return SET;
	}
	return RESET;
}
 