#ifndef __ADC_H
#define __ADC_H			 
#include "OS.h"

#define ADC_BUF_LEN                5 //
#define ADC_EXCLUDE_COUNT						2							//ת�����Ҫ�ų������ֵ����Сֵ������

#define ADC_FAIL                8888U //
#define ADC_VALUE_MAX 4000U //


/**       ADCͨ����
Reg ADCON
Bit7~Bit4	ADCHS[3:0]��AD����ͨ��ѡ��λ��
	0000��ѡ��VRL(ģ��ο��͵�ƽ)
	0001��ѡ��ͨ�� 1��P1.0����
  0010��ѡ��ͨ�� 2��P1.1����
  0011��ѡ��ͨ�� 3��P1.2����
  0100��ѡ��ͨ�� 4��P1.3����
  0101��ѡ��ͨ�� 5��P2.4����
  0110��ѡ��ͨ�� 6��P2.5
  0111��ѡ��ͨ�� 7��P3.0����
1 1000: ѡ��ͨ�� 8��P3.1��
1 1001��ѡ��ͨ�� 9��P3.2����
1 1010��ѡ��ͨ�� 10��P3.3����
1 1011��ѡ���ⲿ�ο����� ADRVH����
1 1100��ѡ�� VRL (ģ��ο��͵�ƽ)��
1 1101��ѡ���׼��ѹ VBG
1 1110��ѡ���ڲ��ο���ѹ CVREF��
1 1111��ѡ�� VRL (ģ��ο��͵�ƽ)��
Bit3	ADEN��ADʹ��λ��
	0���رա�
	1��������
Bit2	ADGO��AD״̬����/��ѯλ��
	д��
		0����Ч��
		1������ADת����
	����
		0��ADת��������ǰû�н�������ת����
		1��AD���ڽ���ת����
Bit1	Interrupt Status
	0�� No Interrupt
	1:  Interrupt  
	Read Clear

*/	
typedef enum 
{
  ADC_CH0=0,
  ADC_CH1,
  ADC_CH2,
  ADC_CH3,
  ADC_CH4,
  ADC_CH5,
  ADC_CH6,
  ADC_CH7,
  ADC_CH8,
  ADC_CH9,
  ADC_CH10,
  ADC_CH11,
  ADC_CH12,
  ADC_CH13,
  ADC_CH14,
  ADC_CH15,
}ADCChannel;

/**       ��Ƶϵ��
*
*
typedef enum
{
	ADC_CLK_SYSCLKDIV2 =0,
	ADC_CLK_SYSCLKDIV4,
	ADC_CLK_SYSCLKDIV8,
	ADC_CLK_SYSCLKDIV16,
}ADCClkDiv;
*/

#define ADCFG_VREF_VDD		0x00
#define ADCFG_VREF_VRH_4V	bit5|bit6|bit2		//�����ڲ�4V
#define ADCFG_VREF_VRH_2V	bit5|bit6			//�����ڲ�2.5V
#define ADCFG_VREF_P50		bit5|bit7		//�����ⲿP5.0
#define ADCFG_VREF_ALL		bit5|bit6|bit7	//ͬʱ�򿪣����� VRH�� AD �ṩ��ѹԴʱ����ͨ���ⲿ�ܽŹ��� 


#define ADCFG_LSB		bit4
#define ADCFG_MSB		0

#define ADCFG_IRQ_EN		bit3
#define ADCFG_IRQ_DIS	0

typedef enum
{
	CLK_SYSCLKDIV2 =0,
	CLK_SYSCLKDIV4,
	CLK_SYSCLKDIV8,
	CLK_SYSCLKDIV16,
}ADCFG_CLK_DIV;

 

#define bit2 0x04
#define bit4 0x10
#define bit5 0x20
#define bit6 0x40
#define bit7 0x80
#define	CH0_VSS 		0x00
#define	CH1_P10		bit4
#define	CH2_P11		bit5
#define	CH3_P12		bit4|bit5
#define	CH4_P13		bit6
//#define	CH5_P14				/no
#define	CH5_P24		bit6|bit4
#define	CH6_P25		bit6|bit5
#define	CH7_P30		bit6|bit5|bit4
#define	CH8_P31		bit7
#define	CH9_P32		bit7|bit4
#define	CH10_P33		bit7|bit5
#define	CH11_P50		bit7|bit5|bit4
#define	CH12_VSS		bit7|bit6
#define	CH13_P94VBG	bit7|bit6|bit4		//ʹ��P94�����Vref
#define	CH14_CVREF		bit7|bit6|bit5		//�ڲ���׼(�Ƚ������ò���)
#define	CH15_VSS		0xf0

void ADC_CfgSet(u8 Vref,u8 Clk, u8 Mask_irq);
void AD_SelCH(u8 ADC_channel);
void AD_Init(u8 ADC_channel);
u16 Adc_Read(void);
void ADCSelectChannel(u8 channel);
void AD_DeInit(void);
#endif 



