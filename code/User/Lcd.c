
#include "Lcd.h" 
#include "CharMatrix.h"
#include <intrins.h>

u8 lcdBuf[6]={0x00,0x00,0x00,0x00,0x00,0x00}; 


/**       显示数码管的某一段
*
*
*/
static void LcdBitScan(u8 bt)
{
	switch(bt)
	{
		case 0:  A1_ON; break;
		case 1:  B1_ON; break;
		case 2:  C1_ON; break;
		case 3:  D1_ON; break;
		case 4:  E1_ON; break; 
		case 5:  F1_ON; break;
		case 6:  G1_ON; break;
		case 7:  break;
		
		case 8:  A2_ON; break;
		case 9:  B2_ON; break;
		case 10: C2_ON; break;
		case 11: D2_ON; break;
		case 12: E2_ON; break; 
		case 13: F2_ON; break;
		case 14: G2_ON; break;
		case 15: break;
		
		case 16: A3_ON; break;
		case 17: B3_ON; break;
		case 18: C3_ON; break;
		case 19: D3_ON; break;
		case 20: E3_ON; break; 
		case 21: F3_ON; break;
		case 22: G3_ON; break;
		case 23: DP_ON; break;
		
		case 24: A4_ON; break;
		case 25: B4_ON; break;
		case 26: C4_ON; break;
		case 27: D4_ON; break;
		case 28: E4_ON; break; 
		case 29: F4_ON; break;
		case 30: G4_ON; break;
		case 31: break;
		
		case 32: J1_ON; break;
		case 33: J2_ON; break;
		case 34: J3_ON; break;
		case 35: J4_ON; break;
		case 36: K8_ON; break;
		case 37: K7_ON; break;
		case 38: K6_ON; break;
		case 39: break;
		
		case 40: K1_ON; break; 
		case 41: K2_ON; break;
		case 42: K3_ON; break;
		case 43: K4_ON; break;
	}					
}


/**       显示全部数据
*
*
*/
void LcdScan(void)
{	
	static u8 i,j;
	
	LCD1_IN;
	LCD2_IN;
	LCD3_IN;
	LCD4_IN;
	LCD5_IN;
	LCD6_IN;
	LCD7_IN;
	i++;
	if(i>7)
	{
		i=0;
		j++;
		if(j>5)
      j=0;
	}		
	if(lcdBuf[j] & 0x80>>i)
	{
		LcdBitScan(j*8+i);
	}
 
}	

	
/*        显示一个字符
* 
* 
* 
*/
void ShowChar(LCDDigitalId id, LCDCharId ch)
{
  lcdBuf[id] =lcdChar[ch];
}	

/*        显示小数点
* 
* 
* 
*/
void DpDis()
{
	lcdBuf[2] |=0x01;
}
	
/*        显示数字
* 
* 
* 
*/
void ShowNumber(u16 val)
{
  u8 len=0;
  u16 tem=0;
  if (val>9999)
    val=9999;
  tem=val;
  while (tem)
  {
    len++;
    tem /=10;
  } 
  switch (len)
  {
  	case 0:
    {
      ShowChar(0,CHAR_XX);
      ShowChar(1,CHAR_XX);
      ShowChar(2,CHAR_XX);
      ShowChar(3,CHAR_0);
    }
  		break;
  	case 1:
    {
      ShowChar(0,CHAR_XX);
      ShowChar(1,CHAR_XX);
      ShowChar(2,CHAR_XX);
      ShowChar(3,val%10);
    }
  		break;
  	case 2:
    {
      ShowChar(0,CHAR_XX);
      ShowChar(1,CHAR_XX);
      ShowChar(2,val/10%10);
      ShowChar(3,val%10);
    }
  		break;
  	case 3:
    {
      ShowChar(0,CHAR_XX);
      ShowChar(1,val/100%10);
      ShowChar(2,val/10%10);
      ShowChar(3,val%10);
    }
  		break;
  	case 4:
    {
      ShowChar(0,val/1000%10);
      ShowChar(1,val/100%10);
      ShowChar(2,val/10%10);
      ShowChar(3,val%10);
    }
  		break;
  	default:
  		break;
  }

}



/*        显示图标
* 
* 
* 
*/
void ShowIco(LcdIcon icon, FlagStatus set)
{
  if (set)
    lcdBuf[5]|=icon;
  else
    lcdBuf[5]&=~icon;
}


/*        电池电量图标
*   val:电量级别
*   set:1-充电模式;0-正常模式
*   
*/
void ShowBattery(LCDBatteryValue val)//,FlagStatus set)
{
  static  LCDBatteryValue tem=0;
      tem=val;

  lcdBuf[4]=lcdBattery[tem];
}


void LcdInit(void)
{
	LCD1_IN;
	LCD2_IN;
	LCD3_IN;
	LCD4_IN;
	LCD5_IN;
	LCD6_IN;
	LCD7_IN; 
 
} 
	
 

void LcdClose()
{
		LCD1_OUT;LCD2_OUT;LCD3_OUT;LCD4_OUT;LCD5_OUT;LCD6_OUT;LCD7_OUT;
		LCD1=0;LCD2=0;LCD3=0;LCD4=0;LCD5=0;LCD6=0;LCD7=0; 
}
	
void LcdClean(void)
{
	u8 i;
	for(i = 0;i<6;i++)
		lcdBuf[i]  = 0x00;
}





