#ifndef __UHF_H
#define __UHF_H			 
#include "main.h" 
 
#define FREQ_INC	300
#define FREQA_INIT	740000
#define FREQB_INIT	810000

#define FREQA_PUB	651000
#define FREQB_PUB	651800

#define CHMAX		50
#define CHMIN		1
#define VOLMAX		9
#define VOLMIN		1
#define	EQMAX		4
#define	EQMIN		0


 typedef enum
{
	order1 = 1,
	order2 = 2,
	order3 = 3,
	order4 = 4,
}BPSKOrder;
 
typedef struct{
	u8 channel;
	u8 id;
	u8 vol;
	u8 ramid;
	u8 ab; 
	u8 quickpress; 
	u8 automute;
	u16 automute_time;
	u8 eq; 
	u8 line_flag;
}UHFDATA;
extern UHFDATA xdata u_dat;
extern u32 code FREQ[2][100];

u32 SetFreq(void);
void KT0646mInit(void);
void SetPubFreq(void);
void FreqTune(u32 freq);
void ChAdd(void);
void ChLess(void);
void VolAdd(void);
void VolLess(void);
void ReadData(void);
void SaveData(void);
void BPSKMode(BPSKOrder order);

 void AutoMuteDelay(void);
void AutoMute();

void EqAdd(void);
void EqLess(void);
void SetEqApi(u8 eq);

void GetVat();
 
#endif













