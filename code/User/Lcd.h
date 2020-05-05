#ifndef __LCD_H
#define __LCD_H 
#include "main.h"
 

#define	B_b0	0xfc	
#define	B_b1	0xf3	
#define	B_b2	0xcf	
#define	B_b3	0x3f

#define	out_b0	0x02	
#define	out_b1	0x08	
#define	out_b2	0x20	
#define	out_b3	0x80


#define       LCD1      P42 //P92--LCD1:推挽输出
#define       LCD2      P41 //P93--LCD2:推挽输出
#define       LCD3      P00 //P32--LCD3:推挽输出
#define       LCD4      P37 //P30--LCD4:推挽输出
#define       LCD5      P36 //P22--LCD5:推挽输出
#define       LCD6      P35 //P21--LCD6:推挽输出
#define       LCD7      P34 //P20--LCD7:推挽输出

#define LCD1_IN   GPIO_SET(xP4MDL,GPIO_OI,2)
#define LCD2_IN   GPIO_SET(xP4MDL,GPIO_OI,1)
#define LCD3_IN   GPIO_SET(P0MDL,GPIO_OI,0)
#define LCD4_IN   GPIO_SET(P3MDH,GPIO_OI,3)
#define LCD5_IN   GPIO_SET(P3MDH,GPIO_OI,2)
#define LCD6_IN   GPIO_SET(P3MDH,GPIO_OI,1)
#define LCD7_IN   GPIO_SET(P3MDH,GPIO_OI,0)

#define LCD1_OUT  GPIO_SET(xP4MDL,GPIO_PP,2)
#define LCD2_OUT  GPIO_SET(xP4MDL,GPIO_PP,1)
#define LCD3_OUT  GPIO_SET(P0MDL,GPIO_PP,0)
#define LCD4_OUT  GPIO_SET(P3MDH,GPIO_PP,3)
#define LCD5_OUT  GPIO_SET(P3MDH,GPIO_PP,2)
#define LCD6_OUT  GPIO_SET(P3MDH,GPIO_PP,1)
#define LCD7_OUT  GPIO_SET(P3MDH,GPIO_PP,0)




#define LCD_DIGITAL_AMOUTN  4 //数码管数量

typedef enum
{
	CHAR_0=0,//DIS_0
	CHAR_1,//DIS_1
	CHAR_2,//DIS_2
	CHAR_3,//DIS_3
	CHAR_4,//DIS_4
	CHAR_5,//DIS_5
	CHAR_6,//DIS_6
	CHAR_7,//DIS_7
	CHAR_8,//DIS_8
	CHAR_9,//DIS_9
	CHAR_A,//DIS_A
	CHAR_B,//DIS_B
	CHAR_C,//DIS_C
	CHAR_d,//DIS_d
	CHAR_E,//DIS_E
	CHAR_F,//DIS_F
	CHAR_c,//DIS_c
	CHAR_H,//DIS_H
	CHAR_h,//DIS_h
	CHAR_k,//DIS_k
	CHAR_L,//DIS_L
	CHAR_N,//DIS_N
	CHAR_n,//DIS_n
	CHAR_o,//DIS_o
	CHAR_P,//DIS_P
  CHAR_r,//r
	CHAR_U,//DIS_U
	CHAR__,//DIS_  
	CHAR_XX,//DIS_XX
	CHAR__1,
	CHAR_LL,
}LCDCharId;

typedef enum
{
	LCD_DIGITAL_1=0,
	LCD_DIGITAL_2,
	LCD_DIGITAL_3,
	LCD_DIGITAL_4,
}LCDDigitalId;

typedef enum
{
  LCD_BATTERY_0=0,
  LCD_BATTERY_1,        //
  LCD_BATTERY_2,        //
  LCD_BATTERY_3,        //
  LCD_BATTERY_4,        //
  LCD_BATTERY_5,        //
}LCDBatteryValue;



typedef enum 
{
	LCD_ICON_LOCK=    0x10,
	LCD_ICON_DB=      0x20,
	LCD_ICON_IR=      0x40,
	LCD_ICON_SIGNAL=  0x80,
}LcdIcon;


#define  LOW	   0
#define  HIGHT     1



//电池
#define  J1_ON  LCD7_OUT;LCD3_OUT; LCD7=HIGHT;LCD3=LOW;
#define  J2_ON  LCD1_OUT;LCD6_OUT; LCD1=HIGHT;LCD6=LOW;
#define  J3_ON  LCD3_OUT;LCD6_OUT; LCD3=HIGHT;LCD6=LOW;
#define  J4_ON  LCD3_OUT;LCD7_OUT; LCD3=HIGHT;LCD7=LOW;
#define  K6_ON  LCD1_OUT;LCD7_OUT; LCD1=HIGHT;LCD7=LOW;
#define  K7_ON  LCD2_OUT;LCD7_OUT; LCD2=HIGHT;LCD7=LOW;
#define  K8_ON  LCD4_OUT;LCD7_OUT; LCD4=HIGHT;LCD7=LOW;
//信号，通道，频率
#define  K1_ON  LCD7_OUT;LCD1_OUT; LCD7=HIGHT;LCD1=LOW;
#define  K2_ON  LCD1_OUT;LCD5_OUT; LCD1=HIGHT;LCD5=LOW;
#define  K3_ON  LCD6_OUT;LCD2_OUT; LCD6=HIGHT;LCD2=LOW;
#define  K4_ON  LCD7_OUT;LCD2_OUT; LCD7=HIGHT;LCD2=LOW;
//DP，8字
#define  DP_ON  LCD7_OUT;LCD5_OUT; LCD7=HIGHT;LCD5=LOW;
#define  A1_ON  LCD1_OUT;LCD2_OUT; LCD1=HIGHT;LCD2=LOW;
#define  B1_ON  LCD1_OUT;LCD3_OUT; LCD1=HIGHT;LCD3=LOW;
#define  C1_ON  LCD4_OUT;LCD1_OUT; LCD4=HIGHT;LCD1=LOW;
#define  D1_ON  LCD5_OUT;LCD1_OUT; LCD5=HIGHT;LCD1=LOW;
#define  E1_ON  LCD1_OUT;LCD4_OUT; LCD1=HIGHT;LCD4=LOW;
#define  F1_ON  LCD2_OUT;LCD1_OUT; LCD2=HIGHT;LCD1=LOW;
#define  G1_ON  LCD3_OUT;LCD1_OUT; LCD3=HIGHT;LCD1=LOW;

#define  A2_ON  LCD2_OUT;LCD3_OUT; LCD2=HIGHT;LCD3=LOW;
#define  B2_ON  LCD2_OUT;LCD4_OUT; LCD2=HIGHT;LCD4=LOW;
#define  C2_ON  LCD5_OUT;LCD2_OUT; LCD5=HIGHT;LCD2=LOW;
#define  D2_ON  LCD2_OUT;LCD6_OUT; LCD2=HIGHT;LCD6=LOW;
#define  E2_ON  LCD2_OUT;LCD5_OUT; LCD2=HIGHT;LCD5=LOW;
#define  F2_ON  LCD3_OUT;LCD2_OUT; LCD3=HIGHT;LCD2=LOW;
#define  G2_ON  LCD4_OUT;LCD2_OUT; LCD4=HIGHT;LCD2=LOW;

#define  A3_ON  LCD5_OUT;LCD4_OUT; LCD5=HIGHT;LCD4=LOW;
#define  B3_ON  LCD3_OUT;LCD5_OUT; LCD3=HIGHT;LCD5=LOW;
#define  C3_ON  LCD4_OUT;LCD5_OUT; LCD4=HIGHT;LCD5=LOW;
#define  D3_ON  LCD6_OUT;LCD1_OUT; LCD6=HIGHT;LCD1=LOW;
#define  E3_ON  LCD6_OUT;LCD3_OUT; LCD6=HIGHT;LCD3=LOW;
#define  F3_ON  LCD4_OUT;LCD3_OUT; LCD4=HIGHT;LCD3=LOW;
#define  G3_ON  LCD5_OUT;LCD3_OUT; LCD5=HIGHT;LCD3=LOW;

#define  A4_ON  LCD7_OUT;LCD6_OUT; LCD7=HIGHT;LCD6=LOW;
#define  B4_ON  LCD6_OUT;LCD7_OUT; LCD6=HIGHT;LCD7=LOW;
#define  C4_ON  LCD5_OUT;LCD6_OUT; LCD5=HIGHT;LCD6=LOW;
#define  D4_ON  LCD6_OUT;LCD4_OUT; LCD6=HIGHT;LCD4=LOW;
#define  E4_ON  LCD4_OUT;LCD6_OUT; LCD4=HIGHT;LCD6=LOW;
#define  F4_ON  LCD6_OUT;LCD5_OUT; LCD6=HIGHT;LCD5=LOW;
#define  G4_ON  LCD5_OUT;LCD7_OUT; LCD5=HIGHT;LCD7=LOW;


//		
 
void LcdScan(void);
void ShowChar(LCDDigitalId id, LCDCharId ch);
void DpDis();
void ShowNumber(u16 val);
void ShowIco(LcdIcon icon, FlagStatus set);
void ShowBattery(LCDBatteryValue val);
void LcdInit(void);
void LcdClean(void);
void LcdClose();

 



#endif /* LCD_H */

