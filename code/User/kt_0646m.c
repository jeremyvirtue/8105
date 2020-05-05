//*****************************************************************************
//  File Name:    KT_WirelessMicTxdrv.c
//  Function:    KT Wireless Mic Transmitter Products Driver For Customer
//                (KT064xM)
//*****************************************************************************
//        Revision History
//  Version Date        Description
//  V0.1    2016-04-26  For KT0646M_VX
//  V0.2    2016-06-01  增加VX和VX2的编译选项    
//  V0.3    2016-08-18  For KT0646M_VX4
//  V0.3.1  2016-08-24  删除KT_WirelessMicTx_Init程序内一些重复配置
//  V0.4    2016-08-26  修正了XTAL_DUAL问题
//  V0.5    2016-10-11  修改了初始化函数中的一些配置，把0x25,0x26寄存器的配置加到了初始化函数里面，
//                  在初始化函数里面set pilot frequency
//  V0.5.1  2016-10-17  重新修改了一下里面的宏定义，定义了RXISKT0616M就用BPSK的旧模式，然后再根据
//                  是否是双晶振把KT0616M选晶振的程序加进去。
//  V0.5.2  2016-11-15  在tune台前把lo_fine_vref_sel改为3，tune完后改成0.
//  V0.5.3  2016-12-15  在初始化中把lo_fine_vref_sel改为3，不用在tune台的时候再来回修改了.为了温度
//                  变化不锁定的问题，详见被宏DOUBLE_KVCO包围的代码
//  V0.6    2017-02-08  格式规范化整理
//  V1.1    2017-04-27  删除了一些初始化函数里面没用的东西，把有些用小写字母定义的宏定义改成了大写的字母
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



/*        总线发送字节数据
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

/*        总线接收字节数据
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

/*        总线响应
* re:SET-有应答   RESET-无应答
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

/*        总线开始
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
/*        总线结束
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

/*        读设备的数据
* devAdd:设备地址
* regAdd:设备上的寄存器地址
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



/**       对KT0646M寄存器写入数据
	参数：Register 寄存器地址，Word_Data写入的数据
	返回值：无
*/ 
void KT_Bus_Write46(uint8_t Register_Address, uint16_t Word_Data)
{
	WriteDeviceWord(KTWirelessMicTxw_address,Register_Address,Word_Data);
}
/**       读KT芯片寄存器数据
	参数：Register_Address 寄存器地址
	返回值：读取到的数据
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
   // KT_WirelessMicTx_Mic_Sens(0);   //音量改为最小 
		//KT_WirelessMicTx_MuteSel(AUDIO_MUTE);	//关闭声音 
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

	/*************开启辅助信道******************/
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
	#ifdef OPEN_BAT	 	//使用KT内部电池检测功能
		KT_WirelessMicTx_BatteryMeter_SW(BATTERY_METER_ENABLE);	//打开电池检测功能
	#endif

	if(KT_WirelessMicTx_Tune(Freq))											//发射频率设置
	{
		KT_WirelessMicTx_PAGain(PA_Pos18dBm);								//PA增益设置
		KT_WirelessMicTx_PASW(PA_ON);										//PA打开	
		KT_WirelessMicTx_Pilot_Fdev(PILOT_FDEV_FREQ);						//倒频信号调制频偏大小设置	
		KT_WirelessMicTx_Pilot(PILOT_ENABLE);								//开启32.768KHz倒频信号	
//		SendAuxData(NORMAL_WORK,Msystem.Volume,Freq/100,Msystem.DevID);	//发正确的AUX 信号给接收
		return(1);//初始化正确
	}
	return(0);	//初始化错误
}


/******************************************************
  函 数 名：KT_WirelessMicTx_PASW												 	
  功能描述：PA打开、关闭程序														
  函数说明：用来控制芯片打开或者关闭PA												
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()											
  全局变量：																		
  输    入：bPA_Switch																
  返    回：正确：1					错误：0																										 	
*******************************************************/
uint8_t B_open_PA;
uint8_t KT_WirelessMicTx_PASW(uint8_t bPA_Switch)
{		   
//#define PA_OFF 0
//#define PA_ON  1
	uint16_t regF;
	B_open_PA = bPA_Switch;		//设置标记
	regF = KT_Bus_Read46(0x0F);	 
    KT_Bus_Write46(0x0F, (regF & 0xFFF7) | ( (uint8_t)bPA_Switch << 3 ));
	return(1);
}


/*******************************************************
  函 数 名：KT_WirelessMicTx_PAGain												 	
  功能描述：PA增益调整																
  函数说明：cPaGain范围为0-12，共13档												
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()											
  全局变量：																		
  输    入：cPaGain																	
  返    回：正确：1					错误：0																						 	
********************************************************/
uint8_t KT_WirelessMicTx_PAGain(uint8_t cPaGain)
{
	uint16_t reg11;
	reg11 = KT_Bus_Read46(0x11);
	KT_Bus_Write46(0x11, (reg11 & 0xFF00) | cPaGain );		

	return(1);	
}


/*********************************************************
  函 数 名：KT_WirelessMicTx_Mic_Sens											 	
  功能描述：Mic灵敏度调整															
  函数说明：cMicSens围为0-15，共16档												
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()											
  全局变量：																		
  输    入：cMicSens																
  返    回：正确：1					错误：0																											 	
**********************************************************/
uint8_t KT_WirelessMicTx_Mic_Sens(uint8_t cMicSens)
{
	uint16_t reg1C;

	reg1C = KT_Bus_Read46(0x1C);
	KT_Bus_Write46(0x1C, (reg1C & 0xFE1F) | ( (uint16_t)cMicSens << 5 ));

	return(1);
}

/**************************************************************
  函 数 名：KT_WirelessMicTx_MuteSel											 	
  功能描述：静音功能打开、关闭程序													
  函数说明：用来选择打开或者关闭静音功能											
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()											
  全局变量：																		
  输    入：bMute_Sel																
  返    回：正确：1					错误：0																								 	
***************************************************************/
uint8_t B_mute;
uint8_t KT_WirelessMicTx_MuteSel(uint8_t bMute_Sel)
{
	uint16_t reg1C;
//#define	AUDIO_UNMUTE	0    //开启声音
//#define	AUDIO_MUTE		1    //静音
	B_mute =  bMute_Sel;
	reg1C = KT_Bus_Read46(0x1C);
	KT_Bus_Write46(0x1C, (reg1C & 0xFFFE) | bMute_Sel);      				//Write Mute bit

	return(1);
}
/************************************************************************
  函 数 名：KT_WirelessMicTx_Calc_ChanReg                                    
  功能描述：晶体的频率控制字计算                                                
  函数说明：输入以KHz为单位的VCO震荡频率;                                            
            计算结果存在*chan_ptr,*chan_frac_ptr,*chan_frac_msb_ptr中                
  全局变量：                                                                        
  输    入：Freq （输入以KHz为单位的VCO频率）                                        
  返    回：正确：1    错误：0                                                            
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
    
    //lodiv 期望值
    lopa_div = vco_highth / Freq;

    //lodiv 实际值
    for(i=0; i<12; i++)
    {
        if(lopa_div < lopa_div_tab[i])
        {            
            break;                                                   
        }
    }
    //输出lopa_div1和lopa_div2
    *lopa_div1_ptr = lopa_div_tab2[i][1];
    *lopa_div2_ptr = lopa_div_tab2[i][0];
    
    //计算VCO 频率
    Fvco = Freq * lopa_div_tab[i];
    //整数
    *chan_ptr = Fvco / (xtal_freq * 7) + 1; //dll_mode : *7
    //小数
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
//函 数 名：KT_WirelessMicTx_Tune                                                     
//功能描述：发射频率设置函数                                                        
//函数说明：输入以KHz为单位的发射频率，                                                
//全局变量：                                                                        
//输    入：Freq （输入以KHz为单位的发射频率）                                        
//返    回：正确：1                 错误：0                                            
//设 计 者：Zhou Dongfeng           时间：2016-04-05                                         
//修 改 者：Zhou Dongfeng           时间：2016-08-26                                         
//版    本：V0.1    For KT0646M_VX
//          V0.2    修改了变量定义的方式并增加了VX和VX2的宏定义，
//                  修改了解决DLL不锁定部分程序的位置
//                  去掉了不用的chan_cfg2变量
//                  去掉了MCU_POWER_OK位的查询工作
//                  去掉了PLL锁定的判断
//          V0.4    统一了变量定义格式
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
    	KT_WirelessMicTx_EQSW(0);  //关闭EQ
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

    //dll未锁定，切换晶振后需要rst
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
    	SettingEQ();  //设置EQ
	#endif
	
//	regx=KT_Bus_Read46(0x1f);
//	KT_Bus_Write46(0x1f, regx & (~0x4000));	//bpsk data disable
//	regx=KT_Bus_Read46(0x1f);
//	KT_Bus_Write46(0x1f, regx | 0x4000);	//bpsk data Enable
			
  return(1);
}






#ifdef OPEN_BAT	 			//使用KT内部电池检测功能
/*****************************************************************
  函 数 名：KT_WirelessMicTx_BatteryMeter_SW									 	
  功能描述：电池电压检测功能打开、关闭程序											
  函数说明：选择打开或者关闭电池电压检测功能										
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()											  
  全局变量：																		
  输    入：bBatteryMeter_En														
  返    回：正确：1					错误：0											
******************************************************************/
uint8_t KT_WirelessMicTx_BatteryMeter_SW(uint8_t bBatteryMeter_En)
{
	uint16_t reg24;

	reg24 = KT_Bus_Read46(0x24);
	KT_Bus_Write46(0x24, (reg24 & 0xEFFF) | ( (uint16_t)bBatteryMeter_En << 12));

	return(1);
} 


/*********************************************************************
   函 数 名：KT_WirelessMicTx_BatteryMeter_Read									 	
  功能描述：电池电压读取程序														
  函数说明：读取当前的电池电压，返回值为0-2047的整数								
  调用函数：KT_Bus_Read46()															
  全局变量：																		
  输    入：无																		
  返    回：reg7 & 0x07FF（为0-2047的整数）															
********************************************************************/
uint16_t KT_WirelessMicTx_BatteryMeter_Read(void)
{
	uint16_t reg7;
	reg7 = KT_Bus_Read46(0x07);
	return( reg7 & 0x07FF );
}


#endif
/*********************************************************************************************
  函 数 名：KT_WirelessMicTx_PowerDownProcedure											 	 	
  功能描述：关机处理程序														 	
  函数说明：																 	
  调用函数：KT_WirelessMicTx_MuteSel();KT_WirelessMicTx_Pilot();KT_WirelessMicTx_PAGain();
 			      KT_WirelessMicTx_PASW();KT_Bus_Read46();KT_Bus_Write46();Delay_ms();												 	
  全局变量：无																 	
  输    入：无;														 	
  返    回：无																 															 	
**********************************************************************************************/
void KT_WirelessMicTx_PowerDownProcedure(void)
{
	uint16_t regx;       	  
	//KT_WirelessMicTx_MuteSel(AUDIO_MUTE);	//关闭声音 
	KT_WirelessMicTx_PAGain(0); 
	KT_WirelessMicTx_PASW(PA_OFF);		    //PA关闭  
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



#ifdef	OPEN_ECHO		//是否打开混响功能
/***************************************************************************
  函 数 名：KT_WirelessMicTx_ECHO                                        
  功能描述：ECHO混响配置程序                                                
  函数说明：配置ECHO混响效果                
  全局变量：                                                                        
  输    入：bEcho_Dis    （ECHO开关）
             Echo_Ratio     （ECHO反馈）                                        
             Echo_Delay     （ECHO延时）
  返    回：无                                                                                                                   
***************************************************************************/
void KT_WirelessMicTx_ECHO(uint8_t bEcho_Dis,uint8_t Echo_Ratio,uint8_t Echo_Delay)
{
    uint16_t regx;

	//if(!Echo_Ratio)
	//	bEcho_Dis = 1;//关闭混响	

    KT_Bus_Write46( 0x32, (ECHO_MCU << 15) | ((uint8_t)bEcho_Dis << 14) | (ECHO_STRU << 13) | 
                 (Echo_Ratio << 8) | (Echo_Delay << 3) | ECHO_GAINUP );
    
    regx = KT_Bus_Read46(0x33);
    KT_Bus_Write46( 0x33, (regx & 0xFFFC) | ECHO_GAINDOWN );                          
}	
#endif



#ifdef	OPEN_EQ	 	//是否打开EQ功能
/******************************************************
  函 数 名：KT_WirelessMicTx_EQSW										
  功能描述：EQ均衡器开关程序												
  函数说明：配置EQ均衡器开启关闭				
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()								
  全局变量：																		
  输    入：bEq_Dis	（EQ开关）
  返    回：无															
*******************************************************/
void KT_WirelessMicTx_EQSW(uint8_t bEq_Dis)
{
	uint16_t regx;

	regx = KT_Bus_Read46(0x34);
	KT_Bus_Write46(0x34, ((regx & 0x7FFF) | (uint16_t)bEq_Dis << 15));
}


/***************************************************************
  函 数 名：KT_WirelessMicTx_EQGAIN										
  功能描述：EQ均衡器配置程序												
  函数说明：配置EQ均衡器各频率增益效果				
  调用函数：KT_Bus_Read46()、KT_Bus_Write46()								
  全局变量：																		
  输    入：Eq_Freq （EQ频率）										
 			Eq_Gain （EQ增益）
  返    回：无															
****************************************************************/
void KT_WirelessMicTx_EQGAIN(uint8_t Eq_Freq,uint8_t Eq_Gain)
{
	uint16_t regx;
	uint8_t temp1,temp2;	 
    //if(Eq_Gain > EQ_GAIN_Pos12dB)
     //   Eq_Gain = EQ_GAIN_Pos12dB;  //防止EQ 计算超过最大
	temp1=Eq_Freq/3+0x34;
	temp2=(2-(Eq_Freq%3))*5;
	regx = KT_Bus_Read46(temp1);
	KT_Bus_Write46(temp1, ((regx & ~(0x001f<<temp2)) | ( (uint16_t)Eq_Gain << temp2 )));
}  
#endif

   
#ifdef KT_RX   		//使用KT接收
/***********************************************************
  函 数 名：KT_WirelessMicTx_Pilot                                                     
  功能描述：32.768KHz导频信号打开、关闭程序                                            
  函数说明：用来选择是否使用32.768KHz导频信号                                        
  全局变量：                                                                        
  输    入：bPilot_Dis                                                                
  返    回：正确：1                 错误：0                                                                                                          
************************************************************/
uint8_t KT_WirelessMicTx_Pilot(uint8_t bPilot_Dis)
{
    uint16_t reg1F;

    reg1F = KT_Bus_Read46(0x1F);
#ifdef OTHER_RX	 	//不使用KT 接收 
    KT_Bus_Write46(0x1F, (reg1F & 0xFFBF) | ( (uint8_t)bPilot_Dis << 6 ));
#endif
#ifdef KT_RX	 	//使用KT接收
    KT_Bus_Write46(0x1F, (reg1F & 0x7FFF) | ( (uint16_t)bPilot_Dis << 15 ));
#endif
    Delay_ms(20);
    return(1);
}


/*********************************************************
  函 数 名：KT_WirelessMicTx_Pilot_Fdev                                                 
  功能描述：32.768KHz导频信号调制频偏大小设置程序                                    
  函数说明：cPilot_Fdev围为0-3，共4档                                                
  全局变量：                                                                        
  输    入：cPilot_Fdev                                                                
  返    回：正确：1                 错误：0                                            
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
  函 数 名：KT_WirelessMicTx_Calc_ChanReg                                    
  功能描述：晶体的频率控制字计算                                                
  函数说明：输入以KHz为单位的VCO震荡频率;                                            
             计算结果存在*chan_ptr,*chan_frac_ptr,*chan_frac_msb_ptr中                
  全局变量：                                                                        
  输    入：Freq （输入以KHz为单位的VCO频率）                                        
  返    回：正确：1    错误：0                                                            
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
//函 数 名：ZK_set_EQ
//功能描述:	设置EQ曲线
//设计公司：广州每芯科技有限公司
//设 计 者：周文波					时间：2018年1月6日
//修 改 者：						时间：	
//版    本：V1.0		
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
    KT_WirelessMicTx_EQSW(1);  //打开EQ
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

 /*自动静音开关  0 open 1 close*/
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

/*检查自动静音*/
FlagStatus KT_WirelessMicTxCheckVolume(void)
{
	if(!(0x4000&(KT_Bus_Read46(0x25))))//有声音
	{	
		return SET;
	}
	return RESET;
}
 