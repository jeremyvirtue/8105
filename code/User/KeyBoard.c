
#include "KeyBoard.h"
#include "System.h" 
#include "kt_0646m.h"
 
KeyData   keys;   
void KeyPress(void);
void KeyRelease(void);
void KeyContinued(void);
void Twins(void);
 


/**       扫描按键状态
* @brief  
* @param  
* @param  
* @retval 
*/
void KeyScan(void)
{
	u8 i;  
	for (i=0;i<KEY_COUNT;i++)
	{
		keys.key[i].now=MASK_EMPTY;
	} 
	if (!KEY_POWER)
	{
		keys.key[KEY_1].now=KEY_DOWN; 
	}  
	if (!KEY2)
	{
		keys.key[KEY_2].now=KEY_DOWN; 
	}  
	if (!KEY3)
	{
		keys.key[KEY_3].now=KEY_DOWN; 
	}  
		if (!KEY4)
	{
		keys.key[KEY_4].now=KEY_DOWN; 
	}  
//	if(keys.key[KEY_1].now==MASK_EMPTY )
//	{	//松开时恢复状态，组合按键

//	}
//	else
//	{
//		 
//	}
	
	for (i=0;i<KEY_COUNT;i++)
	{
		keys.key[i].press=keys.key[i].now & (keys.key[i].now^keys.key[i].continued);
		keys.key[i].release=keys.key[i].now ^ keys.key[i].press ^ keys.key[i].continued;
		keys.key[i].continued=keys.key[i].now;
		if (keys.key[i].continued==0x00)
		  keys.key[i].duration =0;
	}
	
	if(!keys.key[KEY_1].now &&!keys.key[KEY_2].now &&\
			!keys.key[KEY_3].now && !keys.key[KEY_4].now)
	{
		keys.twins_tim = 0;
		keys.twins_flag = 0;
	}
	else
	{
		LedLightApi();
		keys.mute_flag = 1;
	}
	
	Twins(); 
	if(!keys.twins_flag)
	{
		 KeyPress();  
		 KeyRelease();  
		 KeyContinued();  
	}
 
}

void KeyMute(void)
{
	if(keys.mute>0 )
	{
		keys.mute--;
		if(keys.mute == 0 )
		{
			KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);
		}
	}
}


/**       按下
*
*
*/
void KeyPress(void)
{ 
	if (keys.key[KEY_1].press)// 
	{ 
		keys.key_num =  K1_P;
	} 
	if (keys.key[KEY_2].press)// 
	{ 
		keys.key_num = K2_P;
	} 
	if (keys.key[KEY_3].press)// 
	{ 
		keys.key_num = K3_P;
	} 
	if (keys.key[KEY_4].press)// 
	{ 
		keys.key_num = K4_P;
	} 
		 
}
/**       释放
*
*
*/
void KeyRelease(void)
{ 
	if (keys.key[KEY_1].release)// 
	{ 
		keys.key_num = K1_R; 
	}  
	if (keys.key[KEY_2].release)// 
	{ 
		keys.key_num = K2_R; 
	}  
	if (keys.key[KEY_3].release)// 
	{ 
		keys.key_num = K3_R; 
	}  
	if (keys.key[KEY_4].release)// 
	{ 
		keys.key_num = K4_R; 
	}  
	 
}

 
// 
/**       按下不放
*
*
*/
void KeyContinued(void)
{  
	if (keys.key[KEY_1].continued)// 
	{
		if (keys.key[KEY_1].duration<KEY_DURATION_TIME*10)
			keys.key[KEY_1].duration++;
		if(keys.key[KEY_1].duration==KEY_DURATION_TIME/3)
		{
			keys.key_num = K1_C0_3S;
		} 
		if(keys.key[KEY_1].duration==KEY_DURATION_TIME)
		{
			keys.key_num = K1_C1S;
		} 
		if(keys.key[KEY_1].duration==KEY_DURATION_TIME * 7)
		{
			keys.key_num = K1_C10S;
		} 
	} 
	if (keys.key[KEY_2].continued)// 
	{
		if (keys.key[KEY_2].duration<KEY_DURATION_TIME*10)
			keys.key[KEY_2].duration++;
		if(keys.key[KEY_2].duration==KEY_DURATION_TIME/2)
		{
			keys.key_num = K2_C0_5S;
		} 
		if(keys.key[KEY_2].duration==4)
		{
			keys.key_num = K2_C80MS;
		} 
	} 
	if (keys.key[KEY_3].continued)// 
	{
		if (keys.key[KEY_3].duration<KEY_DURATION_TIME*10)
			keys.key[KEY_3].duration++;
		if(keys.key[KEY_3].duration==KEY_DURATION_TIME/2)
		{
			keys.key_num = K3_C0_5S;
		} 
		if(keys.key[KEY_3].duration==4)
		{
			keys.key_num = K3_C80MS;
		} 
	} 
	if (keys.key[KEY_4].continued)// 
	{
		if (keys.key[KEY_4].duration<KEY_DURATION_TIME*10)
			keys.key[KEY_4].duration++;
		if(keys.key[KEY_4].duration==KEY_DURATION_TIME)
		{
			keys.key_num = K4_C0_5S;
		} 
	} 
 
	 
}

void Twins()
{
	if(keys.key[KEY_1].now && keys.key[KEY_2].now)
	{
		keys.twins_flag = 1;
		keys.twins_tim++;
		if(keys.twins_tim == KEY_DURATION_TIME)
		{
			keys.key_num = K1_K2_TWINS;
		}
	}
}


 

/**       执行按键命令
*   0^0=0,0^1=1   1^0=1,1^1=0
*
*/
void KeyExecute(void)
{	
	u8 i;
  for (i=0;i<KEY_COUNT;i++)
	{
    keys.key[i].press=keys.key[i].now & (keys.key[i].now^keys.key[i].continued);
    keys.key[i].release=keys.key[i].now ^ keys.key[i].press ^ keys.key[i].continued;
    keys.key[i].continued=keys.key[i].now;
    if (keys.key[i].continued==MASK_EMPTY)
      keys.key[i].duration =0;
	}
 
	
	KeyPress(); 
	KeyRelease();
	KeyContinued(); 
}

void KeyInit(void)
{		
	u8 i;
	for (i=0;i<KEY_COUNT;i++)
	{
    keys.key[i].now=0;
    keys.key[i].press=0;
    keys.key[i].release=0;
    keys.key[i].continued=0;
    keys.key[i].duration =0;
	}
 
	GPIO_SET(xP5MDL,GPIO_UI,0);// 
	GPIO_SET(P1MDL,GPIO_UI,1);// 
	GPIO_SET(P1MDL,GPIO_UI,2);// 
	GPIO_SET(P1MDL,GPIO_UI,3);// 
}


void keyContinedClean(void)
{
	keys.key[KEY_3].duration = 0;
	keys.key[KEY_2].duration = 0;
}

 void LedLight(void)
{
 xGPIODS0 |= 0x01;   
 xGPIODS3 |= 0xF0;  
 xGPIODS4 |= 0x06;  
}

void LedBlack(void)
{
 xGPIODS0 &= 0xFE; 
 xGPIODS3 &= 0x0F;
 xGPIODS4 &= 0xF9;
}

void LedLightApi()
{
 		LedLight();
		keys.light = 20;
}


 

void LedLampDelay()
{
	if(keys.light>0)
	{
		keys.light--;
		if(keys.light == 0)
		{
			LedBlack();
		}
	}
}

