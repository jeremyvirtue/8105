#include "RCC.h" 
#include "System.h"
#include "Lcd.h"
#include "KeyBoard.h"
#include "OS.h"
#include <intrins.h>
#include "UHF.h"

void Delay_us(unsigned int i)
{		//��ʱUS ��׼ȷ  10 =37us
	unsigned int j;
	for(j=0;j<i;j++);
}

void Delay_ms(unsigned int i)
{//����׼ȷ
	u16	j;
	while(i)
	{
		for(j=0; j<=600; j++)
		{
			;
		}
		i--;
	}
}

 void Clr_wag(void)
{
	WDTCLR0 = 0X00;
    WDTCLR1 = 0X00;
	WDTCLR0 = 0X53;
    WDTCLR1 = 0XAC;		   
}


//------------------------------------------------------------------------
/*		ʱ������ 
*/
//	��Ƶѡ��
void MclkDiv1()		
{
	u8 data temp;
	temp = MCKDIV&0xfc;
	temp |= MCLK_DIV1;
   	WPKEY = 0x37;
   	MCKDIV = temp;  //����Ƶ
}


void MCLKToRCH()
{
	u8 data temp;
	temp = MCKDIV&0xfb;	//bit2 = 0 : ʹ���ڲ�RCH��Ϊϵͳʱ��Դ		
	WPKEY = 0x37;
	MCKDIV = temp; 	
	while((MCKDIV&0x04) != 0x00);		//�л���RCHʱ��ȡMCKS = 0,��ʾ�л��ɹ�
	Delay_us(10);
	MclkDiv1();
	
}


//----------------------------------------------------------
//�� �� ����PORT_Init
//����������MCU�˿ڳ�ʼ��
//����˵����Configure the Crossbar and GPIO ports.
//���ú�����
//ȫ�ֱ�������
//��    �룺
//��    �أ���
//�� �� �ߣ����Ĳ�				ʱ�䣺2016.01.12
//�� �� �ߣ�					ʱ�䣺
//��    ����V1.0				
//----------------------------------------------------------
void IO_init(void) 
{
	IO_DeInit();
	IO_Initailize();
	//***************************
	//��ʼ��E2
	//**************************
	FlashAddrH = 0x00;
	FlashCLKDiv = 25;		//MCLK 4MHz  
}
  

void Tim1Init(void)
{
	xTIMPRS &= 0x8f; 
	xTIMPRS |= 0xf0;   //111��T1 ����ʱ��Ϊ FCLK/256��Ĭ�ϣ���
	TMOD &= 0xcf;
	TMOD |= 0x20;		//8bit�Զ�����
	TR1 = 0;
	TH1 = 253;	//(256-253)*256/8M = 200us
	TL1 = 253;	
	IP |= 0x08;        //T1�����ȼ�
	TR1 = 1;
	ET1 = 1;
	EA = 1;
}



void Tim1IRQ(void) interrupt 3 
{		
	if(Sdata.state != S_INIT)
		LcdScan();
	else
		LcdClose();
}

/*        ϵͳ������ʱ��
*   ��TIM0��ʱ5MS��ϵͳ������ʱ��
*   SysClk = 8MHz
*/
void SystemTimInit(void)
{
	xTIMPRS &= 0xf8; 
	xTIMPRS |= 0x07;   //111��T0 ����ʱ��Ϊ FCLK/256��
	TMOD &= 0xf0;
	TMOD |= 0x02;		//8bit�Զ�����
	TR0 = 0;
	TH0 = 98;	//ֵ+ Time- LBS=0.032MS
	TL0 = 98;	
	IP &= 0xFD;      
	TF0 = 1;//��T0����ж��������
	TR0 = 1;//������ʱ��0
	ET0 = 1;
	EA = 1;//�����ж�
	
}

 
void SystemTimIRQ(void) interrupt 1 
{
	static u8 count = 0;
	count++;
	if(count == 4 )//20ms
	{
		count =0 ;
		  KeyScan();
	}
	if(Sdata.s_delay>0)
		Sdata.s_delay--;
	OSTick();
	Clr_wag();       //���Ź���λ
	 
}



/**********************************************
         Extern interrupt0 initailize
***********************************************/
void Extern0_init(void)
{
//	xIOMUX1  &= 0xFE;		//INT0RMP=0;	select P00 as INT0 sourc
	xIOMUX1  |= 0x01;		//INT0RMP=1;	select P50 as INT0 sourc
	EX0 = 1;
	IT0 = 1;		//ex1�½��ش��� 
	EX1 = 1;
	IT1 = 1;
//	EINTCS0  = 0x10;		//en ex0, ex0�½��ش��� 
	EINTCS0  = 0x38;
//	00101000
//	00010000
}

void Extern1_init(void)
{
	EX1 = 1;
	IT1 = 1;		//ex1�ߵ�ƽ����
	EINTCS0	= 0x28;	//  ex0�½��ش��� 
	EA = 1;
}


/**********************************************
         Extern interrupt0 sever funtion 
***********************************************/
void Extint0(void) interrupt 0
{
	if(EINTCS0 & 0x01 )
	{ 
		EINTCS0 = 0x38;	//bit 4 Disable INT0 intterrup	 
		Sdata.stop_time = 5;
		 
		_nop_();
	}
}

void Extint1(void) interrupt 2
{
	if(EINTCS0 & 0x02 )
	{
		EINTCS0	= 0x38;	//en ex0, ex0�½��ش���  
		Sdata.stop_time = 5; 
		u_dat.line_flag = 1;
		_nop_();
	}
}

void Stop_Cfg(void)
{
	u8 Read;
	Read = xSYSCFG;
	Read &= ~(1<<4|1);//WDTCFG,RCLCFG
	Read |= (0<<4)|1;
	xSYSCFG = Read;
	
	Read = xSTOPCFG;
	Read &= ~(1<<3|1<<1);
	Read |= (1<<3) | (1<<1);
	xSTOPCFG = Read;
}

void stop_mode(void)
{
	LVRCON &= ~(1<<7); // close VBG
	//WTCON = 0x80; // enable WT
//	xVREGCFG |= 1<<3; //enable LDO
	Stop_Cfg(); // open RCL in stop mode
	WPKEY = 0x37;	//disable write protect
	PCON |= 1<<1; // enter stop mode
	
}


void IO_DeInit(void)
{
	//------------------------------	
	xGPIODS0 = 0xFF;	
	P0MDH = 0xFF;	
	P0MDL = 0xFF;
	P0 	  = 0x00;  
//------------------------------	
	xGPIODS1 = 0xFF;	
	P1MDH = 0xFF;
	P1MDL = 0xFF;
	P1    = 0x00;	
//------------------------------
	xGPIODS2 = 0xFF;	
	P2MDH = 0xFF;
	P2MDL = 0xFF;	
	P2    = 0x00;
	
//------------------------------
	xGPIODS3 = 0xFF;	
	P3MDH = 0xFF;
	P3MDL = 0xFF;
	P3    = 0x00;	


//------------------------------
	xGPIODS4 = 0xFF;		
	xP4MDH = 0xFF;	
	xP4MDL = 0xFF;	
	P4     = 0x00;

//------------------------------
//	xGPIODS5 = 0xFF;		
//	xP5MDH = 0xFF;	
//	xP5MDL = 0xFF;	
//	P5     = 0x00;
	
//------------------------------
	xGPIODS9 = 0xFF;
	xP9MDH = 0xFF;
	xP9MDL = 0xFF;
	P9     = 0x00;
	
//	xSYSCFG &= 0x7F;	//RTS change to general IO

}

void IO_Initailize(void)
{
 
	GPIO_SET(P2MDL,GPIO_PP,1);// POWER		
	GPIO_SET(P3MDL,GPIO_OI,0);// BAT_V		
//	GPIO_SET(P2MDL,GPIO_UI,0);// CHARGE_EN	
	GPIO_SET(P0MDL,GPIO_OI,1);// LINE_EN	
	GPIO_SET(P1MDL,GPIO_UI,0);// AB		
	GPIO_SET(P2MDL,GPIO_PP,0);// LED P20
}






