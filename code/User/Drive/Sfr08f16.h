/**********************************************************************************
**********************************************************************************/

/*2016-12-1 Ver1.0 By Dean
1.�޸�REG������MCU1101Pһ�£��������������ֲ
*/
#ifndef __SFR08F16P_H
#define __SFR08F16P_H

/*˵��:
[2016.11.28]
  1 ǰ��Сx��ͷ�ļĴ�����ʾ��Ҫ��dptr������;
  2 ����ASM: �û�������ʹ�õ��ǻ������,Ӧ����ASMΪ1,��#define	ASM 1, C����ӦʹASM��Ϊ1;
  3 ����EXSFR: EXSFR����Ϊ1,������չ�ļĴ�������;
*/
#define	ASM 0      // =1,�û�������ǻ������
#define	EXSFR 0    // =1,��ʾʹ����չ�Ĵ���

//----------------------------------------------------------------------------------------------------------------------------

/******  MCU�ں�  ******/
sfr  P0 = 0x80;
sfr  P1 = 0x90;
sfr  P2 = 0xA0;
sfr  P3 = 0xB0;
sfr PSW    = 0xD0;    // ����״̬��
sfr ACC    = 0xE0;    // �ۼ���
sfr B      = 0xF0;    // B�Ĵ���
sfr SP     = 0x81;    // ��ջָ��
sfr DPL    = 0x82;    // ����ָ����ֽ�
sfr DPH    = 0x83;    // ����ָ����ֽ�

sfr  PCON     = 0x87;    // ��Դ���ƼĴ���
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;

sfr IE      = 0xA8;    // �ж�����Ĵ���
sfr IP      = 0xB8;    // �ж����ȼ��Ĵ���
sfr AUXR1  = 0xA2;    // DPTRѡ��Ĵ���
sfr MOVXRH = 0xA1;    // Ri���Ѱַ��8λ��ַ�Ĵ���
/*  BIT Register  */
/*  P0  */
sbit  P00 = P0^0;
sbit  P01 = P0^1;
sbit  P02 = P0^2;
sbit  P03 = P0^3;
sbit  P04 = P0^4;
sbit  P05 = P0^5;
sbit  P06 = P0^6;
sbit  P07 = P0^7;

/*  P1  */
sbit  P10 = P1^0;
sbit  P11 = P1^1;
sbit  P12 = P1^2;
sbit  P13 = P1^3;
sbit  P14 = P1^4;
sbit  P15 = P1^5;
sbit  P16 = P1^6;
sbit  P17 = P1^7;

/*  P2  */
sbit  P20 = P2^0;
sbit  P21 = P2^1;
sbit  P22 = P2^2;
sbit  P23 = P2^3;
sbit  P24 = P2^4;
sbit  P25 = P2^5;
sbit  P26 = P2^6;
sbit  P27 = P2^7;

/*  P3  */
sbit  P30 = P3^0;
sbit  P31 = P3^1;
sbit  P32 = P3^2;
sbit  P33 = P3^3;
sbit  P34 = P3^4;
sbit  P35 = P3^5;
sbit  P36 = P3^6;
sbit  P37 = P3^7;

/*  PSW   */
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit F1   = PSW^1;
sbit P   = PSW^0;

/*  TCON  */
sbit TF1  = TCON^7;
sbit TR1  = TCON^6;
sbit TF0  = TCON^5;
sbit TR0  = TCON^4;
sbit IE1  = TCON^3;
sbit IT1  = TCON^2;
sbit IE0  = TCON^1;
sbit IT0  = TCON^0;

/*  IE   */
sbit EA   = IE^7;
sbit ET2  = IE^5;
sbit ES   = IE^4;
sbit ET1  = IE^3;
sbit EX1  = IE^2;
sbit ET0  = IE^1;
sbit EX0  = IE^0;

/*  IP   */ 
sbit PT2  = IP^5;
sbit PS  = IP^4;
sbit PT1  = IP^3;
sbit PX1  = IP^2;
sbit PT0  = IP^1;
sbit PX0  = IP^0;

/*  SCON  */
sfr  SCON0    = 0x98;    // UART0���ƼĴ���

sbit SM0   = SCON0^7;
sbit SM1   = SCON0^6;
sbit SM2   = SCON0^5;
sbit REN  = SCON0^4;
sbit TB8  = SCON0^3;
sbit RB8  = SCON0^2;
sbit TI   = SCON0^1;
sbit RI   = SCON0^0;


/*******************************INTC***********************/
sfr EIE1    = 0xA9;    // ��չ�ж�����Ĵ���1
sfr EIE2    = 0xAA;    // ��չ�ж�����Ĵ���2
sfr EIP1    = 0xB9;    // ��չ�ж����ȼ��Ĵ���1
sfr EIP2    = 0xBA;    // ��չ�ж����ȼ��Ĵ���2
sfr EINTCS0 = 0xAC;    // �ⲿ�жϿ�����״̬�Ĵ���0
sfr EINTCS1 = 0xBC;    // �ⲿ�жϿ�����״̬�Ĵ���1

/******************************PMU**************************************************************************/





//----------------------------------------------------------------------------------------------------------------------------

/******  ���¼Ĵ����������  ******/
//sfr	 VMC0 	 = 0xA5;  // ��ѹ����			/*ע�⣡���� �Ĵ����б䶯*/
sfr  LVDCON   = 0xA5;    // ��ѹ�����ƼĴ���		//LVREN LVRSλ�õ���	/*ע�⣡���� �Ĵ����б䶯*/
sfr  LVRCON   = 0xA6;    // ��ѹ��λ���ƼĴ���	/*ע�⣡���� �Ĵ����б䶯*/
//sfr  SPMC0	 = 0xA6;  // ϵͳ��Դ����	/*ע�⣡���� �Ĵ����б䶯*/




#if  ASM == 1
	xSTOPCFG  EQU 0FFA0H   // ͣ��ģʽ���üĴ���
	xBGPTRIM  EQU 0FFF2H		// ��׼ԴУ׼�Ĵ��� ===���ӣ�	/*ע�⣡���� �Ĵ����б䶯*/		
#else
	#define  xSTOPCFG  (*(volatile unsigned char xdata *)0xFFA0)    // ͣ��ģʽ���üĴ���
	#define	xBGPTRIM (*(volatile unsigned char xdata *)0xFFF2)		// ��׼ԴУ׼�Ĵ���	===����	/*ע�⣡���� �Ĵ����б䶯*/
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  ��λRESET  ******/

sfr  RSTSRC = 0xA7;    // ��λ��־
	
	
sfr CPFRHS =0xAD;		//===����	/*ע�⣡���� �Ĵ����б䶯*/

//----------------------------------------------------------------------------------------------------------------------------

/******  ���Ź���ʱ��WDT  ******/

sfr WDTCON   = 0xDD;    // WDT ��Ƶ����		//ADDR�仯��	/*ע�⣡���� �Ĵ����б䶯*/
sfr WDTCLR0  = 0xDE;    // WDT����Ĵ���0		//ADDR�仯��	/*ע�⣡���� �Ĵ����б䶯*/
sfr WDTCLR1  = 0xDF;    // WDT����Ĵ���1		//ADDR�仯��	/*ע�⣡���� �Ĵ����б䶯*/

//----------------------------------------------------------------------------------------------------------------------------

/******  ʱ�ӹ���CKM  ******/

sfr MCKSET   = 0x91;    // ϵͳ��ʱ��ѡ��Ĵ���

sfr	MCKDIV   = 0x91;

sfr WPKEY    = 0x92;    // ʱ��״̬�л�Կ�׼Ĵ���		//ADDR�仯��	/*ע�⣡���� �Ĵ����б䶯*/
//sfr  CLKEN   = 0x93;   	//��ɾ���˼Ĵ���	/*ע�⣡���� �Ĵ����б䶯*/
//sfr  PLLCON  = 0x96;		//��ɾ���˼Ĵ���	/*ע�⣡���� �Ĵ����б䶯*/


#if  ASM ==1
	xSYSCFG   EQU    0FFA2H    // ʱ������
	xLFCSCON  EQU    0FFEEH    // ��Ƶʱ�ӿ��ƼĴ���		//===����	/*ע�⣡���� �Ĵ����б䶯*/
	xTESTCON  EQU	 0FFAFH    // ���Կ��ƼĴ���
	xPCGC0    EQU	 0FF60H    // �����ſ�ʱ������0		//===����	/*ע�⣡���� �Ĵ����б䶯*/
//	xPCGC1    EQU	 0FF61H    // �����ſ�ʱ������1			
//	xCRYCFG   EQU	 0FFF0H    // CRYL��Ƶ��ģʽѡ��

#else
	#define  xSYSCFG   (*(volatile unsigned char xdata *)0xFFA2)    // ʱ������
	#define  xLFCSCON  (*(volatile unsigned char xdata *)0xFFEE)    // ��Ƶʱ�ӿ��ƼĴ���
	#define  xTESTCON  (*(volatile unsigned char xdata *)0xFFAF)    // ���Կ��ƼĴ���
	#define  xPCGC0    (*(volatile unsigned char xdata *)0xFF60)    // �����ſ�ʱ������0
//	#define  xPCGC1    (*(volatile unsigned char xdata *)0xFF61)    // �����ſ�ʱ������1
//	#define  xCRYCFG   (*(volatile unsigned char xdata *)0xFFF0)    // CRYL��Ƶ��ģʽѡ��
	#define xRCHTRIM	 (*(volatile unsigned char xdata *)0xFFF4)		//RCHУ׼�Ĵ���
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  ͨ��I/O��GPIO  ******/
/*ע�⣡���� �Ĵ����б䶯*/
/* P4/P5/P9λ�ñ䶯����Ϊ��λѰַ���ʣ�  */
sfr  P4 = 0xC0;
sfr  P5 = 0xC8;//changed for bit access.
sfr  P9 = 0xE8;

/*  P4  	*/
sbit  P40 = P4^0;
sbit  P41 = P4^1;
sbit  P42 = P4^2;
sbit  P43 = P4^3;
sbit  P44 = P4^4;
sbit  P45 = P4^5;
sbit  P46 = P4^6;
sbit  P47 = P4^7;

/*  P5 	*/
sbit  P50 = P5^0;
sbit  P54 = P5^4;
sbit  P55 = P5^5;
sbit  P56 = P5^6;


/*  P9  	*/
sbit  P90 = P9^0;
sbit  P91 = P9^1;
sbit  P92 = P9^2;
sbit  P93 = P9^3;
sbit  P94 = P9^4;
sbit  P95 = P9^5;



sfr  P0MDL = 0xEC;    // P0.0~P0.3 IOģʽ���ƣ�00:ʩ�������룬��������01�����룬��������10�����������11����©���
sfr  P1MDL = 0xED;    // P1.0~P1.3
sfr  P2MDL = 0xEE;    // P2.0~P2.3
sfr  P3MDL = 0xEF;    // P3.0~P3.3
sfr  P0MDH = 0xFC;    // P0.4~P0.7
sfr  P1MDH = 0xFD;    // P1.4~P1.7
sfr  P2MDH = 0xFE;    // P2.4~P2.7
sfr  P3MDH = 0xFF;    // P3.4~P3.7


#if  ASM ==1
	xP4MDL   EQU  0FFA4H   // �˿�4ģʽ���üĴ���(���ֽ�)
	xP4MDH   EQU  0FFB4H   // �˿�4ģʽ���üĴ���(���ֽ�)
	xP5MDL   EQU  0FFA5H   // �˿�5ģʽ���üĴ���(���ֽ�)
	xP5MDH   EQU  0FFB5H   // �˿�5ģʽ���üĴ���(���ֽ�)
	xP9MDL   EQU  0FFA9H   // �˿�9ģʽ���üĴ���(���ֽ�)
	xP9MDH   EQU  0FFB9H   // �˿�9ģʽ���üĴ���(���ֽ�) P9.5(��λ��)������Ϊ���
	xP1AEN   EQU  0FFC1H   // �˿�1ģ��ͨ������Ĵ��� 
	xP3AEN   EQU  0FFC3H   // �˿�3ģ��ͨ������Ĵ��� 
	xIOMUX0  EQU  0FFE0H   // IO���ÿ��ƼĴ���0 
	xIOMUX1  EQU  0FFE1H   // IO���ÿ��ƼĴ���1
	xIOMUX2  EQU  0FFE2H   // IO���ÿ��ƼĴ���2
//	xIOMUX3  EQU  0FFE3H   // IO���ÿ��ƼĴ���3 
#else
	#define  xP4MDL	     (*(volatile unsigned char xdata *)0xFFA4)    // �˿�4ģʽ���üĴ���(���ֽ�)
	#define  xP4MDH	     (*(volatile unsigned char xdata *)0xFFB4)    // �˿�4ģʽ���üĴ���(���ֽ�)
	#define  xP5MDL	     (*(volatile unsigned char xdata *)0xFFA5)    // �˿�5ģʽ���üĴ���(���ֽ�)
  #define  xP5MDH	     (*(volatile unsigned char xdata *)0xFFB5)    // �˿�5ģʽ���üĴ���(���ֽ�)
	#define  xP9MDL	     (*(volatile unsigned char xdata *)0xFFA9)    // �˿�9ģʽ���üĴ���(���ֽ�)
	#define  xP9MDH	     (*(volatile unsigned char xdata *)0xFFB9)    // �˿�9ģʽ���üĴ���(���ֽ�)	
	#define  xP1AEN      (*(volatile unsigned char xdata *)0xFFC1)    // �˿�1ģ��ͨ������Ĵ���
	#define  xP3AEN      (*(volatile unsigned char xdata *)0xFFC3)    // �˿�3ģ��ͨ������Ĵ���	
	#define  xIOMUX0     (*(volatile unsigned char xdata *)0xFFE0)    // IO���ÿ��ƼĴ���0 
	#define  xIOMUX1     (*(volatile unsigned char xdata *)0xFFE1)    // IO���ÿ��ƼĴ���1 
	#define  xIOMUX2     (*(volatile unsigned char xdata *)0xFFE2)    // IO���ÿ��ƼĴ���2 
//	#define  xIOMUX3     (*(volatile unsigned char xdata *)0xFFE3)    // IO���ÿ��ƼĴ���3 
  #define  xPT1DS0 		 (*(volatile unsigned char xdata *)0xFFD5)
	#define  xPT1DS1 		 (*(volatile unsigned char xdata *)0xFFD6)
  #define  xPT1DS2 		 (*(volatile unsigned char xdata *)0xFFD7)
	#define  xPT1DS3 		 (*(volatile unsigned char xdata *)0xFFD8)
	#define  xPT1DS4 		 (*(volatile unsigned char xdata *)0xFFE5)
  #define  xPT1DS5 		 (*(volatile unsigned char xdata *)0xFFE6)
	#define  xPT1DS9 		 (*(volatile unsigned char xdata *)0xFFE7)
  #define  xPTxSR 		 (*(volatile unsigned char xdata *)0xFFE8)

								
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  ����UART ******/

sfr  SBUF0    = 0x99;    // UART0���ݻ���Ĵ���
//sfr  SCON0    = 0x98;    // UART0���ƼĴ���
sfr  BRCON0   = 0x8E;    // UART0�����ʿ��ƼĴ���
sfr  BRTIM0   = 0x8F;    // ʱ�ӷ�������ֵ���üĴ���	

/*  SCON0  */
sbit S0M0    = SCON0^7;
sbit S0M1    = SCON0^6;
sbit S0M2    = SCON0^5;
sbit S0REN   = SCON0^4;
sbit S0TB8   = SCON0^3;
sbit S0RB8   = SCON0^2;
sbit S0TI    = SCON0^1;
sbit S0RI    = SCON0^0;
//----------------------------------------------------------------------------------------------------------------------------

/******  �ӱ�ʱ��WT ******/
sfr  WTCON    = 0xBF;    // �ӱ�ʱ�����ƼĴ���

#if  ASM ==1
	xT8   EQU  0FF9BH        // 8λ���ж�ʱ��T8���Ĵ�������ֵ
	xT8RL   EQU  0FF9BH     //д�Ĵ�����ֵ
#else
	#define  xT8   (*(volatile unsigned char xdata *)0xFF9B)     // 8λ���ж�ʱ��T8���Ĵ�������ֵ
	#define  xT8RL   (*(volatile unsigned char xdata *)0xFF9B)   //д�Ĵ�����ֵ
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  �����ж�KBI ******/

sfr  KBIFLG  = 0x9E;    // �����жϱ�־�Ĵ���

#if  ASM ==1
	xKBICON  EQU  0FFDAH      // P0�����жϿ��ƼĴ���
	xKBIWKP  EQU  0FFDBH      // P0�����жϼ���ѡ��Ĵ���
	xP1KBICON  EQU  0FFDCH    // P1�����жϿ��ƼĴ���
	xP1KBIWKP  EQU  0FFDDH    // P1�����жϼ���ѡ��Ĵ���
	xP2KBICON  EQU  0FFDEH    // P2�����жϿ��ƼĴ���
	xP2KBIWKP  EQU  0FFDFH    // P2�����жϼ���ѡ��Ĵ���
	xP4KBICON  EQU  0FFECH    // P4�����жϿ��ƼĴ���
	xP4KBIWKP  EQU  0FFEDH    // P4�����жϼ���ѡ��Ĵ���
#else
	#define  xKBICON    (*(volatile unsigned char xdata *)0xFFDA)    // P0�����жϿ��ƼĴ���
	#define  xKBIWKP    (*(volatile unsigned char xdata *)0xFFDB)    // P0�����жϼ���ѡ��Ĵ���
	#define  xP1KBICON  (*(volatile unsigned char xdata *)0xFFDC)    // P1�����жϿ��ƼĴ���
	#define  xP1KBIWKP  (*(volatile unsigned char xdata *)0xFFDD)    // P1�����жϼ���ѡ��Ĵ���
	#define  xP2KBICON  (*(volatile unsigned char xdata *)0xFFDE)    // P2�����жϿ��ƼĴ���
	#define  xP2KBIWKP  (*(volatile unsigned char xdata *)0xFFDF)    // P2�����жϼ���ѡ��Ĵ���
	#define  xP4KBICON  (*(volatile unsigned char xdata *)0xFFEC)    // P4�����жϿ��ƼĴ���
	#define  xP4KBIWKP  (*(volatile unsigned char xdata *)0xFFED)    // P4�����жϼ���ѡ��Ĵ���

#endif


//----------------------------------------------------------------------------------------------------------------------------

/******  ��ʱ��TIMER ******/


#if  ASM ==1
	xTIMPRS    EQU  0FFCAH    // TimerԤ��Ƶ���ƼĴ���
	xTIMCFG    EQU  0FFCDH    // ��ʱ��TIMER��չPWM����λ
#else
	#define xTIMPRS    (*(volatile unsigned char xdata *)0xFFCA)    // TimerԤ��Ƶ���ƼĴ���
	#define xTIMCFG    (*(volatile unsigned char xdata *)0xFFCD)    // TimerԤ��Ƶ���ƼĴ���
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  ��ʱ��TIMER2 ******/


sfr T2MOD    =  0xC1;//T2ģʽ�Ĵ���
sfr T2CPL1   =  0xC2;//T2������1���ֽ�
sfr T2CPH1   =  0xC3;//T2������1���ֽ�
sfr T2CPL2   =  0xC4;//T2������1���ֽ�
sfr T2CPH2   =  0xC5;//T2������1���ֽ�
sfr T2CAP    =  0xC6;//T2�������üĴ���
sfr T2CAPS   =  0xC7;//T2����״̬�Ĵ���
sfr T2CON    =  0xC9;// ��ʱ��2���ƼĴ���
sfr T2L      =  0xCA;// ��ʱ��2���ֽ�
sfr T2H      =  0xCB;// ��ʱ��2���ֽ�
sfr T2EXS    = 0xCC;//T2�ⲿ����Դѡ��Ĵ���
sfr T2CPL3   = 0xCD;//T2����Ĵ���3���ֽ�
sfr T2CPH3   = 0xCE;
sfr PPG2CON   = 0xCF;//PPG���ƼĴ���
 

//----------------------------------------------------------------------------------------------------------------------------

/******  �ز���ʱ��CRT  ******/

sfr  CRTCON1   = 0xE1;    // �ز���ʱ�����ƼĴ���1
sfr  CRTCON2   = 0xE2;    // �ز���ʱ�����ƼĴ���2
sfr  CRTCNT    = 0xE3;    // �ز���ʱ�� 
sfr  CRTDATA0  = 0xE4;    // �ز���ʱ����ֵ�Ĵ���0
sfr  CRTDATA1  = 0xE5;    // �ز���ʱ����ֵ�Ĵ���1

//----------------------------------------------------------------------------------------------------------------------------

/******  ��׼��SPI  ******/

sfr  SPICON0 = 0xF8;    // SPI������0
sfr  SPICON1 = 0xF9;    // SPI������1
sfr  SPIFLG  = 0xFA;    // SPI��־�Ĵ���
sfr  SPIBUF  = 0xFB;    // SPI�������ݼĴ���

sbit  SPIE    = SPICON0^0;
sbit  MSTEN   = SPICON0^1;
sbit  LSBF    = SPICON0^2;
sbit  SPC     = SPICON0^3;
sbit  BIDIROE = SPICON0^4;
sbit  MODFEN  = SPICON0^5;
sbit  SPTIE   = SPICON0^6;
sbit  SPRIE   = SPICON0^7;
//----------------------------------------------------------------------------------------------------------------------------

/******  ģ��Ƚ���ACMP  ******/

sfr  CP0CON     = 0xAE;     // ģ��Ƚ���0���ƼĴ���
sfr  CP0VRCON   = 0xAF;     // ģ��Ƚ���0�ڲ��ο���ѹ���ƼĴ���  

//----------------------------------------------------------------------------------------------------------------------------

/******  ģ��ת����ADC  ******/

sfr  ADCON       = 0xD8;     // ADC���ƼĴ���
sfr  ADRESL      = 0xD9;     // ADCת�������8λ  
sfr  ADRESH      = 0xDA;     // ADCת�������8λ

sfr  CMPDATAL    = 0xD9;    //AD����Ƚϵ�8λ�Ĵ�������ADRESL���õ�ַ
sfr  CMPDATAH    = 0xDA;    //AD����Ƚϸ�8λ�Ĵ�������ADRESH���õ�ַ
/*  ADCON  */
sbit ADGO    = ADCON^2;
sbit ADEN    = ADCON^3;


#if  ASM ==1
  xADCMOD    EQU  0FFADH  //ADC ģʽ�趨
	xADCFG     EQU  0FFAEH     // ADC���üĴ���
#else
	#define xADCFG    (*(volatile unsigned char xdata *) 0xFFAE)    // ADC���üĴ���
	#define xADCMOD   (*(volatile unsigned char xdata *) 0xFFAD)    // ADCģʽ�趨�Ĵ���
	#define xADGC     (*(volatile unsigned char xdata *) 0xFF60)    // ADC clock
#endif 

//----------------------------------------------------------------------------------------------------------------------------

/******  Һ����ʾLCD  ******/

#if  ASM == 1
	xLCDPEN0  EQU  0FF20H   // LCD�����ܽ�����λ�Ĵ���0  1816-->P0�˿�
	xLCDPEN1  EQU  0FF21H   // LCD�����ܽ�����λ�Ĵ���1  1816-->P1�˿�
	xLCDPEN2  EQU  0FF22H   // LCD�����ܽ�����λ�Ĵ���2  1816-->P2�˿�
	xLCDPEN3  EQU  0FF23H   // LCD�����ܽ�����λ�Ĵ���3  1816-->P3�˿�
	xLCDPEN4  EQU  0FF24H   // LCD�����ܽ�����λ�Ĵ���4  1816-->P4�˿�
	xLCDPEN5  EQU  0FF25H   // LCD�����ܽ�����λ�Ĵ���5  1816-->P5�˿�
#else
	#define  xLCDPEN0  (*(volatile unsigned char xdata *)0xFF20)   // LCD�����ܽ�����λ�Ĵ���0  1816-->P0�˿�
	#define  xLCDPEN1  (*(volatile unsigned char xdata *)0xFF21)   // LCD�����ܽ�����λ�Ĵ���1  1816-->P1�˿�
	#define  xLCDPEN2  (*(volatile unsigned char xdata *)0xFF22)   // LCD�����ܽ�����λ�Ĵ���2  1816-->P2�˿�
	#define  xLCDPEN3  (*(volatile unsigned char xdata *)0xFF23)   // LCD�����ܽ�����λ�Ĵ���3  1816-->P3�˿�
	#define  xLCDPEN4  (*(volatile unsigned char xdata *)0xFF24)   // LCD�����ܽ�����λ�Ĵ���4  1816-->P4�˿�
	#define  xLCDPEN5  (*(volatile unsigned char xdata *)0xFF25)   // LCD�����ܽ�����λ�Ĵ���5  1816-->P5�˿�

#endif

#if  ASM ==1
	xLCDCON     EQU  0FF80H   // LCD���ƼĴ���
	xLCDRCON    EQU  0FF81H   // LCD�������������ƼĴ���
	xLCDTKCON   EQU  0FF82H   // LCD��˸���ƼĴ���
	xLCDTKADDR  EQU  0FF84H   // LCD��˸��1��ַ
	xLCDSCDIV   EQU  0FF86H   // LCDɨ��ʱ��Դ��Ƶ�Ĵ���
	xLCDDATA0   EQU  0FF00H	  // LCDӳ��洢��0
	xLCDDATA1   EQU  0FF01H	  // LCDӳ��洢��1
	xLCDDATA2   EQU  0FF02H	  // LCDӳ��洢��2
	xLCDDATA3   EQU  0FF03H	  // LCDӳ��洢��3
	xLCDDATA4   EQU  0FF04H	  // LCDӳ��洢��4
	xLCDDATA5   EQU  0FF05H	  // LCDӳ��洢��5
	xLCDDATA6   EQU  0FF06H	  // LCDӳ��洢��6
	xLCDDATA7   EQU  0FF07H   // LCDӳ��洢��7
	xLCDDATA8   EQU  0FF08H	  // LCDӳ��洢��8
	xLCDDATA9   EQU  0FF09H	  // LCDӳ��洢��9
	xLCDDATA10  EQU  0FF0AH	  // LCDӳ��洢��10
	xLCDDATA11  EQU  0FF0BH	  // LCDӳ��洢��11
	xLCDDATA12  EQU  0FF0CH	  // LCDӳ��洢��12
	xLCDDATA13  EQU  0FF0DH	  // LCDӳ��洢��13
	xLCDDATA14  EQU  0FF0EH	  // LCDӳ��洢��14
	xLCDDATA15  EQU  0FF0FH   // LCDӳ��洢��15
	xLCDDATA16  EQU  0FF10H	  // LCDӳ��洢��16
	xLCDDATA17  EQU  0FF11H	  // LCDӳ��洢��17
	xLCDDATA18  EQU  0FF12H	  // LCDӳ��洢��18
	xLCDDATA19  EQU  0FF13H	  // LCDӳ��洢��19
	xLCDDATA20  EQU  0FF14H	  // LCDӳ��洢��20
	xLCDDATA21  EQU  0FF15H	  // LCDӳ��洢��21
	xLCDDATA22  EQU  0FF16H	  // LCDӳ��洢��22
	xLCDDATA23  EQU  0FF17H   // LCDӳ��洢��23
	xLCDDATA24  EQU  0FF18H	  // LCDӳ��洢��24
	xLCDDATA25  EQU  0FF19H	  // LCDӳ��洢��25
	xLCDDATA26  EQU  0FF1AH	  // LCDӳ��洢��26
	xLCDDATA27  EQU  0FF1BH	  // LCDӳ��洢��27
	xLCDDATA28  EQU  0FF1CH	  // LCDӳ��洢��28
	xLCDDATA29  EQU  0FF1DH	  // LCDӳ��洢��29
	xLCDDATA30  EQU  0FF1EH	  // LCDӳ��洢��30
	xLCDDATA31  EQU  0FF1FH   // LCDӳ��洢��31
	xLCDDATA32  EQU  0FF30H	  // LCDӳ��洢��32
	xLCDDATA33  EQU  0FF31H	  // LCDӳ��洢��33
	xLCDDATA34  EQU  0FF32H	  // LCDӳ��洢��34
	xLCDDATA35  EQU  0FF33H   // LCDӳ��洢��35
#else
	#define  xLCDCON     (*(volatile unsigned char xdata *)0xFF80)   //	LCD���ƼĴ���
	#define  xLCDRCON    (*(volatile unsigned char xdata *)0xFF81)   //	LCD�������������ƼĴ���
	#define  xLCDTKCON   (*(volatile unsigned char xdata *)0xFF82)   //	LCD��˸���ƼĴ���
	#define  xLCDTKADDR  (*(volatile unsigned char xdata *)0xFF84)   //	LCD��˸��1��ַ
	#define  xLCDSCDIV   (*(volatile unsigned char xdata *)0xFF86)  //LCDɨ��ʱ��Դ��Ƶ�Ĵ���
	#define  xLCDDATA0   (*(volatile unsigned char xdata *)0xFF00)	 //	LCDӳ��洢��0
	#define  xLCDDATA1   (*(volatile unsigned char xdata *)0xFF01)	 //	LCDӳ��洢��1
	#define  xLCDDATA2   (*(volatile unsigned char xdata *)0xFF02)	 //	LCDӳ��洢��2
	#define  xLCDDATA3   (*(volatile unsigned char xdata *)0xFF03)	 //	LCDӳ��洢��3
	#define  xLCDDATA4   (*(volatile unsigned char xdata *)0xFF04)	 //	LCDӳ��洢��4
	#define  xLCDDATA5   (*(volatile unsigned char xdata *)0xFF05)	 //	LCDӳ��洢��5
	#define  xLCDDATA6   (*(volatile unsigned char xdata *)0xFF06)	 //	LCDӳ��洢��6
	#define  xLCDDATA7   (*(volatile unsigned char xdata *)0xFF07) 	 //	LCDӳ��洢��7
	#define  xLCDDATA8   (*(volatile unsigned char xdata *)0xFF08)	 //	LCDӳ��洢��8
	#define  xLCDDATA9   (*(volatile unsigned char xdata *)0xFF09)	 //	LCDӳ��洢��9
	#define  xLCDDATA10  (*(volatile unsigned char xdata *)0xFF0A)	 //	LCDӳ��洢��10
	#define  xLCDDATA11  (*(volatile unsigned char xdata *)0xFF0B)	 //	LCDӳ��洢��11
	#define  xLCDDATA12  (*(volatile unsigned char xdata *)0xFF0C)	 //	LCDӳ��洢��12
	#define  xLCDDATA13  (*(volatile unsigned char xdata *)0xFF0D)	 //	LCDӳ��洢��13
	#define  xLCDDATA14  (*(volatile unsigned char xdata *)0xFF0E)	 //	LCDӳ��洢��14
	#define  xLCDDATA15  (*(volatile unsigned char xdata *)0xFF0F) 	 //	LCDӳ��洢��15
	#define  xLCDDATA16  (*(volatile unsigned char xdata *)0xFF10)	 //	LCDӳ��洢��16
	#define  xLCDDATA17  (*(volatile unsigned char xdata *)0xFF11)	 //	LCDӳ��洢��17
	#define  xLCDDATA18  (*(volatile unsigned char xdata *)0xFF12)	 //	LCDӳ��洢��18
	#define  xLCDDATA19  (*(volatile unsigned char xdata *)0xFF13)	 //	LCDӳ��洢��19
	#define  xLCDDATA20  (*(volatile unsigned char xdata *)0xFF14)	 //	LCDӳ��洢��20
	#define  xLCDDATA21  (*(volatile unsigned char xdata *)0xFF15)	 //	LCDӳ��洢��21
	#define  xLCDDATA22  (*(volatile unsigned char xdata *)0xFF16)	 //	LCDӳ��洢��22
	#define  xLCDDATA23  (*(volatile unsigned char xdata *)0xFF17) 	 //	LCDӳ��洢��23
	#define  xLCDDATA24  (*(volatile unsigned char xdata *)0xFF18)	 //	LCDӳ��洢��24
	#define  xLCDDATA25  (*(volatile unsigned char xdata *)0xFF19)	 //	LCDӳ��洢��25
	#define  xLCDDATA26  (*(volatile unsigned char xdata *)0xFF1A)	 //	LCDӳ��洢��26
	#define  xLCDDATA27  (*(volatile unsigned char xdata *)0xFF1B)	 //	LCDӳ��洢��27
	#define  xLCDDATA28  (*(volatile unsigned char xdata *)0xFF1C)	 //	LCDӳ��洢��28
	#define  xLCDDATA29  (*(volatile unsigned char xdata *)0xFF1D)	 //	LCDӳ��洢��29
	#define  xLCDDATA30  (*(volatile unsigned char xdata *)0xFF1E)	 //	LCDӳ��洢��30
	#define  xLCDDATA31  (*(volatile unsigned char xdata *)0xFF1F) 	 //	LCDӳ��洢��31
	#define  xLCDDATA32  (*(volatile unsigned char xdata *)0xFF30)   //	LCDӳ��洢��32
	#define  xLCDDATA33  (*(volatile unsigned char xdata *)0xFF31)	 //	LCDӳ��洢��33
	#define  xLCDDATA34  (*(volatile unsigned char xdata *)0xFF32)	 //	LCDӳ��洢��34
	#define  xLCDDATA35  (*(volatile unsigned char xdata *)0xFF33) 	 //	LCDӳ��洢��35
#endif
	
//----------------------------------------------------------------------------------------------------------------------------
	


/******  MTP******/ 
	
sfr FlashCtrl = 0xD1;
sfr FlashAddrH  = 0xD2;
sfr FlashAddrL  = 0xD3;
sfr FlashDataH  = 0xD4;
sfr FlashDataL  = 0xD5;
sfr FlashCLKDiv = 0xD6;
sfr FlashKey		= 0xD7;
	
	
	#if  ASM ==1

	  xBGPTRIM 	EUQ    0FFF2H
		xRCHPT			EUQ		 0FFF3H
		xRCHTRIM		EUQ		 0FFF4H
//		VBGOFFSET EUQ		 0FFF5H
//		VREFOFFSET EUQ	 0FFF6H
//		VTEMPL		EUQ		 0FFF7H
//		VTEMPH		EUQ		 0FFF8H

#else

	#define 	xBGPTRIM			(*(volatile unsigned char xdata *)0xFFF2) 
	#define 	xRCHPT  		  (*(volatile unsigned char xdata *)0xFFF3)
	#define   xRCHTRIM     (*(volatile unsigned char xdata *)0xFFF4)
//	#define 	VBGOFFSET	  (*(volatile unsigned char xdata *)0xFFF5)
//	#define 	VREFOFFSET	(*(volatile unsigned char xdata *)0xFFF6)		
//	#define   VTEMPL      (*(volatile unsigned char xdata *)0xFFF7)
//	#define 	VTEMPH      (*(volatile unsigned char xdata *)0xFFF8)
	
#endif
	
	#if  ASM ==1

	xIAPKey0   EQU    0FF62H
	xIAPKey1   EQU    0FF63H
	xIAPKey2   EQU    0FF64H
	xIAPKey3   EQU    0FF65H
	
	#else

	#define 	xIAPKey0			(*(volatile unsigned char xdata *)0xFF62)
	#define 	xIAPKey1			(*(volatile unsigned char xdata *)0xFF63)
	#define 	xIAPKey2			(*(volatile unsigned char xdata *)0xFF64)
	#define 	xIAPKey3			(*(volatile unsigned char xdata *)0xFF65)
	#endif
	
	
	
		#if  ASM ==1
	xGPIODS0   EQU    0FFD5H
	xGPIODS1   EQU    0FFD6H
	xGPIODS2   EQU    0FFD7H
	xGPIODS3   EQU    0FFD8H
	xGPIODS4   EQU    0FFE5H
	xGPIODS5   EQU    0FFE6H
	xGPIODS9		EQU    0FFE7H
	xGPIOSR		EQU    0FFE8H
	#else
	#define 	xGPIODS0			(*(volatile unsigned char xdata *)0xFFD5)
	#define 	xGPIODS1			(*(volatile unsigned char xdata *)0xFFD6)
	#define 	xGPIODS2			(*(volatile unsigned char xdata *)0xFFD7)
	#define 	xGPIODS3			(*(volatile unsigned char xdata *)0xFFD8)
	#define 	xGPIODS4			(*(volatile unsigned char xdata *)0xFFE5)
	#define 	xGPIODS5			(*(volatile unsigned char xdata *)0xFFE6)
	#define 	xGPIODS9			(*(volatile unsigned char xdata *)0xFFE7)
	#define 	xGPIOSR			(*(volatile unsigned char xdata *)0xFFE8)

	#endif
  
  
typedef enum
{
  GPIO_0=0,
  GPIO_1,
  GPIO_2,
  GPIO_3,
  GPIO_4,
  GPIO_5,
  GPIO_9,
}GPIOPort;  

typedef enum
{
  GPIO_PIN_0=0,
  GPIO_PIN_1,
  GPIO_PIN_2,
  GPIO_PIN_3,
  GPIO_PIN_4,
  GPIO_PIN_5,
  GPIO_PIN_6,
  GPIO_PIN_7,
}GPIOPin; 

typedef enum
{
  GPIO_OI=0,//�������ա�
  GPIO_UI,//����������
  GPIO_PP,//���������
  GPIO_OP,//��©�����
}GPIOType; 


#define GPIO_SET(IO,TYPE,BIT) (IO=(IO&(~(0x03<<(BIT<<1))))|(TYPE<<(BIT<<1))) 
//#define GPIO_RESET(IO,BIT) (IO &=~(0x11<<(2*BIT))} 
  
#endif	