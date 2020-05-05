#ifndef __ADC_H
#define __ADC_H			 
#include "OS.h"

#define ADC_BUF_LEN                5 //
#define ADC_EXCLUDE_COUNT						2							//转换结果要排除的最大值和最小值的数量

#define ADC_FAIL                8888U //
#define ADC_VALUE_MAX 4000U //


/**       ADC通道号
Reg ADCON
Bit7~Bit4	ADCHS[3:0]：AD输入通道选择位。
	0000：选择VRL(模拟参考低电平)
	0001：选择通道 1（P1.0）。
  0010：选择通道 2（P1.1）。
  0011：选择通道 3（P1.2）。
  0100：选择通道 4（P1.3）。
  0101：选择通道 5（P2.4）。
  0110：选择通道 6（P2.5
  0111：选择通道 7（P3.0）。
1 1000: 选择通道 8（P3.1）
1 1001：选择通道 9（P3.2）。
1 1010：选择通道 10（P3.3）。
1 1011：选择外部参考点与 ADRVH。。
1 1100：选择 VRL (模拟参考低电平)。
1 1101：选择基准电压 VBG
1 1110：选择内部参考电压 CVREF。
1 1111：选择 VRL (模拟参考低电平)。
Bit3	ADEN：AD使能位。
	0：关闭。
	1：开启。
Bit2	ADGO：AD状态控制/查询位。
	写：
		0：无效。
		1：启动AD转换。
	读：
		0：AD转换结束或当前没有进行数据转换。
		1：AD正在进行转换。
Bit1	Interrupt Status
	0： No Interrupt
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

/**       分频系数
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
#define ADCFG_VREF_VRH_4V	bit5|bit6|bit2		//来自内部4V
#define ADCFG_VREF_VRH_2V	bit5|bit6			//来自内部2.5V
#define ADCFG_VREF_P50		bit5|bit7		//来自外部P5.0
#define ADCFG_VREF_ALL		bit5|bit6|bit7	//同时打开，用于 VRH给 AD 提供电压源时，可通过外部管脚挂容 


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
#define	CH13_P94VBG	bit7|bit6|bit4		//使用P94输出的Vref
#define	CH14_CVREF		bit7|bit6|bit5		//内部基准(比较器设置部分)
#define	CH15_VSS		0xf0

void ADC_CfgSet(u8 Vref,u8 Clk, u8 Mask_irq);
void AD_SelCH(u8 ADC_channel);
void AD_Init(u8 ADC_channel);
u16 Adc_Read(void);
void ADCSelectChannel(u8 channel);
void AD_DeInit(void);
#endif 



