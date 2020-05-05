#include <intrins.h> 
#include "ADC.h"
#include  <stdlib.h>

 
/*************************************/
void ADC_CfgSet(u8 Vref,u8 Clk, u8 Mask_irq)
{	//all value ref adc.h,   #define ADCFG_*** 

	 xADCFG |= (Vref|Clk|Mask_irq|ADCFG_LSB);	
}
void AD_Init(u8 ADC_channel)
{
	xADCMOD = 0;	//Soft control start, disable adc in stop; ADC clk from MCLK
	LVRCON=0x85;	     //·ÀËÀ»ú
	ADC_CfgSet(ADCFG_VREF_VRH_2V,CLK_SYSCLKDIV4,ADCFG_IRQ_DIS);
	xADGC |= 0x80;			//enable adc clcok 
	ADCSelectChannel(ADC_channel);	//p1.1
	
	ADEN =1;
	_nop_();
	_nop_();
	_nop_();
	ADGO = 1;

}

void AD_DeInit(void)
{
	ADEN = 0;
	ADCON &= 0x38;
}

u16 Adc_Read()
{
	u16 adc_data;
	ADEN =1;
	_nop_();
	_nop_();
	_nop_();

	ADGO = 1;
	
	while( ADGO == 1);
	
	ADGO = 1;

	adc_data = ADRESH;
	adc_data = (adc_data<<8) | ADRESL;
	
	return adc_data;
}




void ADCSelectChannel(u8 channel)
{
	u8 data temp;
	
	switch(channel)
	{
		case CH0_VSS: break;
		case CH1_P10:  xP1AEN|=0x01; break;	 //p1.0
		case CH2_P11:  xP1AEN|=0x02; break;//p1.1
		case CH3_P12:  xP1AEN|=0x04; break;//p1.2
		case CH4_P13:  xP1AEN|=0x08; break;//p1.3
		case CH5_P24:  xP1AEN|=0x10; break;//p2.4
		case CH6_P25:  xP1AEN|=0x20; break;//p2.5
		case CH7_P30:  xP3AEN|=0x01; break;//p3.0
		case CH8_P31:  xP3AEN|=0x02; break;//p3.1		//LQFP-48Î´·â³ö 
		case CH9_P32:  xP3AEN|=0x04; break;//p3.2
		case CH10_P33: xP3AEN|=0x08; break;//p3.3
		case CH11_P50: xP3AEN|=0x10; break;//p5.0
		case CH13_P94VBG: LVRCON|=0x40;	break;//p9.4 set VROE(P9.4 AEN); 1:set 1.25 VBG out to P94 
		case CH14_CVREF:break;
		case CH15_VSS: break;
		default: break;
	}
	temp = ADCON&0x0f;
	ADCON = temp |channel;
}


