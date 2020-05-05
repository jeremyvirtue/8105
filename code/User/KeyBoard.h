#ifndef __KeyBoard_H
#define __KeyBoard_H
#include "main.h"
 
 
#define 			KEY_POWER 		P50 
#define 			KEY2			P13 
#define 			KEY3			P12
#define 			KEY4			P11
		
#define KEY_COUNT 4//��������		
#define KEY_DOWN 1

#define KEY_TIPS_TIME 10 //��ʾ��ʾ����
#define KEY_DURATION_TIME 50 //��ʾ��ʾ����

#define KEY_VALUE_INC 100 //AD����5
 

/**                           
  * @brief
  */  
typedef enum 
{
	KEY_1=0,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
}KeyId;	

typedef enum
{
	K__,
	
	K1_P ,
	K1_R ,
	K1_C0_3S,
	K1_C1S,
	K1_C10S,
	
	K2_P ,
	K2_R ,
	K2_C0_5S, 
	K2_C80MS, 
	
	K3_P ,
	K3_R ,
	K3_C0_5S,
	K3_C80MS, 	
	
	K4_P ,
	K4_R ,
	K4_C0_5S, 
	
	K1_K2_TWINS,
}KEY_N;
	
 

typedef struct
{
  u8 now:1;         //��ǰ��ֵ
  u8 press:1;       //����
  u8 release:1;     //�ͷ�
  u8 continued:1;   //��������
  u16 duration;    //��������ʱ��
}Key;
	
typedef struct
{
	Key       key[KEY_COUNT]; 
	u8 			key_num;
	u8 		  twins_tim;
	u8 			twins_flag;
	u8 mute;
	u8 mute_flag;
	u8 light;
}KeyData;	

 
extern KeyData keys;
 

void KeyInit(void); 
 void KeyScan(void);
void keyContinedClean(void);
void KeyMute(void);



void LedLampDelay();
 void LedLight(void);
void LedBlack(void);


#endif











