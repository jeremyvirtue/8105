//********************************************************************************
//  File Name:    KT_WirelessMicTxdrv.h
//  Function:    KT Wireless Mic Transmitter Products Driver For Customer
//                (KT064xM)
//*****************************************************************************

//----------------------------------------------------------
// Includes
//----------------------------------------------------------	
#ifndef  __kt0646m_h__             //�������ָ��
#define  __kt0646m_h__             //�����ظ�����	

#include "main.h"
 

/********************************WPBOBO**********************************/

#define       KT_SCL    P92
#define       KT_SDA    P93
#define		  CHIP_EN	P22	

 

#define SCL_SET    KT_SCL=1
#define SCL_RESET  KT_SCL=0

#define SDA_SET    KT_SDA=1
#define SDA_RESET  KT_SDA=0
#define SDA_READ   KT_SDA

#define SCL_OUT()  {GPIO_SET(xP9MDL,GPIO_PP,2);}

#define SDA_IN()   {GPIO_SET(xP9MDL,GPIO_UI,3);}
#define SDA_OUT()  {GPIO_SET(xP9MDL,GPIO_PP,3);}

#define CHIP_EN_OUT		{GPIO_SET(P2MDL,GPIO_PP,2);}
 
/**********************************
         KT0646Mָ��
***********************************/
#define KT0646M

#define  OPEN_EQ

#define DOUBLE_KVCO
//#define pll_unlock
#define AUX_CH
#define SILENCE_MUTE

//#define XTAL_DUAL
#define XTAL_24M_ONLY
//#define XTAL_24P576M_ONLY

#define RXISKT0616M

#ifdef     RXISKT0616M
    #define RXISKT0616M_BPSK
    #ifdef XTAL_DUAL
        #define RXISKT0616M_XTAL_DUAL
    #endif
#endif

#define KT_RX //ʹ��KTоƬ�Ľ��ջ�
//#define OTHER_RX //ʹ�����������Ľ��ջ�

#define KTWirelessMicTxw_address 0x6A
#define KTWirelessMicTxr_address 0x6B


#define XTAL_24M_FREQ 0
#define XTAL_24P576M_FREQ 1


#define INIT_FAIL_TH46	10

#ifdef OTHER_RX
	#define PILOT_FREQ		32768
#endif


#define PA_SEL 1

#define PA_OFF 0
#define PA_ON  1

#define	AUDIO_UNMUTE	0    //��������
#define	AUDIO_MUTE		1    //����

#define	WAKEUP	0
#define	STANDBY	1

#define	FDEV_MONITOR_TC_250ms	0
#define	FDEV_MONITOR_TC_500ms	1
#define	FDEV_MONITOR_TC_1s		2
#define	FDEV_MONITOR_TC_2s		3

#define	PRE_EMPHASIS_ENABLE		0
#define	PRE_EMPHASIS_DISABLE	1


#define	MIC_SENS_GAIN_0		0   //0db
#define	MIC_SENS_GAIN_1		1   //4db
#define	MIC_SENS_GAIN_2		2   //7db
#define	MIC_SENS_GAIN_3		3   //10db
#define	MIC_SENS_GAIN_4		4   //12db
#define	MIC_SENS_GAIN_5		5   //16db
#define	MIC_SENS_GAIN_6		6   //19db
#define	MIC_SENS_GAIN_7		7   //22db
#define	MIC_SENS_GAIN_8		8   //24db
#define	MIC_SENS_GAIN_9		9   //28db
#define	MIC_SENS_GAIN_10	10  //31db
#define	MIC_SENS_GAIN_11	11  //34db
#define	MIC_SENS_GAIN_12	12  //36db
#define	MIC_SENS_GAIN_13	13  //40db
#define	MIC_SENS_GAIN_14	14  //43db
#define	MIC_SENS_GAIN_15	15  //46db  
#define	KT_FS_VOL   		MIC_SENS_GAIN_8//16db
   
#define COMPANDOR_ENABLE    0
#define COMPANDOR_DISABLE   1
						  
#define COMPANDOR_TC_6ms    0
#define COMPANDOR_TC_12ms   1
#define COMPANDOR_TC_24ms   2
#define COMPANDOR_TC_48ms   3
#define COMPANDOR_TC_93ms   4
#define COMPANDOR_TC_199ms  5
#define COMPANDOR_TC_398ms  6
#define COMPANDOR_TC_796ms  7

#define	PREEMPASIS_ENABLE	0  		//Ԥ���ؿ���
#define	PREEMPASIS_DISABLE	1		//Ԥ���عر�


			 
//
#define	PA_GAIN_STEP	1
#define	PA_Neg21dBm		1
#define	PA_Neg12dBm		3
#define	PA_Neg7dBm		11
#define	PA_Pos0dBm		15
#define	PA_Pos6dBm		25
#define	PA_Pos11dBm		30
#define	PA_Pos13dBm		35
#define	PA_Pos16dBm		40
#define	PA_Pos18dBm		42 //52
 
#define slnc_mute_50ms		    0x00 //50ms   MUTE offPA  �ȴ�ʱ��
#define slnc_mute_100ms		    0x01 //100ms
#define slnc_mute_200ms		    0x02 //200ms
#define slnc_mute_400ms		    0x03 //400ms
#define slnc_mute_1s		    0x04 //1s
#define slnc_mute_2s		    0x05 //2s
#define slnc_mute_4s		    0x06 //4s 
#define slnc_mute_8s		    0x07 //8s 
#define slnc_mute_16s		    0x08 //16s
#define slnc_mute_24s		    0x09 //24s
#define slnc_mute_32s		    0x0a //32s
#define slnc_mute_40s		    0x0b //40s 
#define slnc_mute_48s		    0x0c //48s 
#define slnc_mute_56s		    0x0d //56s 
#define slnc_mute_60s		    0x0e //60s 
#define slnc_mute_80s		    0x0f //80s  
#define slnc_mute_2min		    0x10 //2MIN 
#define slnc_mute_3min		    0x11 //3MIN 
#define slnc_mute_4min		    0x12 //4MIN 
#define slnc_mute_5min		    0x13 //5MIN 
#define slnc_mute_6min		    0x14 //6MIN 
#define slnc_mute_7min		    0x15 //7MIN 
#define slnc_mute_8min		    0x16 //8MIN 
#define slnc_mute_9min		    0x17 //9MIN 
#define slnc_mute_10min		    0x18 //10MIN
#define slnc_mute_11min		    0x19 //11MIN
#define slnc_mute_12min		    0x1A //12MIN
#define slnc_mute_13min		    0x1B //13MIN
#define slnc_mute_14min		    0x1C //14MIN
#define slnc_mute_15min		    0x1D //15MIN
#define slnc_mute_16min		    0x1E //16MIN
#define slnc_mute_17min		    0x1F //17MIN 

                              
#define slnc_exit_0_50mv	    0x00 //0.5mv �˳�MUTE ״̬������
#define slnc_exit_1mv		   		0x01 //1mv      
#define slnc_exit_2mv		    	0x02 //2mv      
#define slnc_exit_4mv		    	0x03 //4mv     
#define slnc_exit_8mv		    	0x04 //8mv     
#define slnc_exit_12mv		    0x05 //12mv      
#define slnc_exit_16mv		    0x06 //16mv     
#define slnc_exit_20mv		    0x07 //20mv     
#define slnc_exit_24mv		    0x08 //24mv     
#define slnc_exit_28mv		    0x09 //28mv    
#define slnc_exit_32mv		    0x0a //32mv    
#define slnc_exit_36mv		    0x0b //36mv      
#define slnc_exit_40mv		    0x0c //40mv     
#define slnc_exit_48mv		    0x0d //48mv     
#define slnc_exit_56mv		    0x0e //56mv     
#define slnc_exit_64mv		    0x0f //64mv  

            
#define slnc_in_0_25mv		  0x00 //0.25mv ����MUTE ״̬������
#define slnc_in_0_50mv		  0x01 //0.5mv   
#define slnc_in_1mv	    	  0x02 //1mv      
#define slnc_in_2mv 		    0x03 //2mv     
#define slnc_in_4mv 		    0x04 //4mv     
#define slnc_in_6mv 		    0x05 //6mv     
#define slnc_in_8mv 		    0x06 //8mv      
#define slnc_in_10mv 		    0x07 //10mv     
#define slnc_in_12mv 		    0x08 //12mv     
#define slnc_in_14mv 		    0x09 //14mv     
#define slnc_in_16mv 		    0x0a //16mv    
#define slnc_in_20mv 		    0x0b //20mv    
#define slnc_in_24mv 		    0x0c //24mv      
#define slnc_in_28mv 		    0x0d //28mv     
#define slnc_in_32mv 		    0x0e //32mv     
#define slnc_in_40mv 		    0x0f //40mv     

   
#ifdef SILENCE_MUTE
	#define SLNC_MUTE_DIS          0  	 				//0 = �źż�⹦�ܿ���  1 = �źż�⹦�ܹر�
	#define SLNC_MUTE_TIME         slnc_mute_400ms			//slnc_mute_400ms ����SLNC_MUTE �ĵȴ�ʱ�� (MAX = 00011111B = 17����) 
	#define SLNC_MUTE_LOW_LEVEL    slnc_in_1mv   		//����MUTE  ����
	#define SLNC_MUTE_HIGH_LEVEL   slnc_exit_2mv	  	//�˳�MUTE  ����
	
	#define SILENCE_MUTE_ACT_MCU   0		//1 = ʹ���Զ��ر�PA �����Զ�����  0=�޷�Ӧ 
#endif

#ifdef KT_RX					//ʹ��KTоƬ�Ľ��ջ�
	#define	PILOT_ENABLE			1
	#define	PILOT_DISABLE			0
#endif

#ifdef OTHER_RX				//ʹ�����������Ľ��ջ�
	#define	PILOT_ENABLE			0
	#define	PILOT_DISABLE			1
#endif
#define	PILOT_FDEV_2P5K			0
#define	PILOT_FDEV_5K			1
#define	PILOT_FDEV_7P5K			2
#define	PILOT_FDEV_10K			3

#define	PILOT_FDEV_FREQ			PILOT_FDEV_7P5K


#define	BATTERY_METER_DISABLE	0
#define	BATTERY_METER_ENABLE	1
//ZDF
#define	AGC_VHIGH				3		//AGC�����ޣ�0-15��ѡ
#define	AGC_VLOW				4		//AGC�����ޣ�0-15��ѡ
#define	AGC_ATTACK				3		//AGC ATTACKʱ�䣺0-7��ѡ
#define	AGC_RELEASE				4		//AGC RELEASEʱ�䣺0-7��ѡ
#define	AGC_DIS					1       //�趨PGA �����������ʽ
//0-ʹ���Զ����棻 ����������ֵ�Ѿ��ﵽ GAIN_SEL �趨ֵ  ������������
//1-��ʹ���Զ�����  PGA ������� MICPGA_GAIN_SEL  ���趨 

#define	GAIN_SEL				3		//PGA���棺0:��-6dB��,1:0dB,2:6dB,3:12dB
#define	COMPEN_GAIN				2//3	//���油������������棺0=0dB,1=6dB,2=12dB,3=18dB
#define	BLANK_EN				1		//BLANK���ƣ�0-DIS��1-EN
#define	BLANK_TIME				3		//BLANKʱ�䣺0-7��ѡ

#define	ECHO_MCU				1		//ECHO���Ʒ�ʽѡ��0-��ť����(�ⲿӲ������)��1-MCU����
#define	ECHO_ENABLE				0       //ECHO ���ؿ���  0=����ECHO   1=  �ر�ECHO
#define	ECHO_DISABLE			1       //    �ر�ECHO
#define	ECHO_STRU				1		//������С��0-������1-����С
#define	ECHO_GAINUP				7		//����źŽ������ţ�7-13.1dB
#define	ECHO_GAINDOWN			0		//�����źŽ������ţ�0-��-13dB��

#define	ECHO_RATIO_0			0		//�����С ����������0-�޷�����25-����25/32
#define	ECHO_RATIO_1			1
#define	ECHO_RATIO_2			2
#define	ECHO_RATIO_3			3
#define	ECHO_RATIO_4			4
#define	ECHO_RATIO_5			5
#define	ECHO_RATIO_6			6
#define	ECHO_RATIO_7			7
#define	ECHO_RATIO_8			8
#define	ECHO_RATIO_9			9
#define	ECHO_RATIO_10			10
#define	ECHO_RATIO_11			11
#define	ECHO_RATIO_12			12
#define	ECHO_RATIO_13			13
#define	ECHO_RATIO_14			14
#define	ECHO_RATIO_15			15
#define	ECHO_RATIO_16			16
#define	ECHO_RATIO_17			17
#define	ECHO_RATIO_18			18
#define	ECHO_RATIO_19			19
#define	ECHO_RATIO_20			20
#define	ECHO_RATIO_21			21
#define	ECHO_RATIO_22			22
#define	ECHO_RATIO_23			23
#define	ECHO_RATIO_24			24
#define	ECHO_RATIO_25			25

#define	ECHO_DELAY_22ms			0		//��ʱ��С �ź���ʱ��0-22ms��24-207ms
#define	ECHO_DELAY_24ms			1
#define	ECHO_DELAY_27ms			2
#define	ECHO_DELAY_29ms			3
#define	ECHO_DELAY_32ms			4
#define	ECHO_DELAY_35ms			5
#define	ECHO_DELAY_39ms			6
#define	ECHO_DELAY_43ms			7
#define	ECHO_DELAY_47ms			8
#define	ECHO_DELAY_52ms			9
#define	ECHO_DELAY_57ms			10
#define	ECHO_DELAY_63ms			11
#define	ECHO_DELAY_69ms			12
#define	ECHO_DELAY_76ms			13
#define	ECHO_DELAY_84ms			14
#define	ECHO_DELAY_92ms			15
#define	ECHO_DELAY_101ms		16
#define	ECHO_DELAY_111ms		17
#define	ECHO_DELAY_122ms		18
#define	ECHO_DELAY_135ms		19
#define	ECHO_DELAY_148ms		20
#define	ECHO_DELAY_163ms		21
#define	ECHO_DELAY_179ms		22
#define	ECHO_DELAY_197ms		23
#define	ECHO_DELAY_207ms		24

#define	EQ_ENABLE				1       //��������
#define	EQ_DISABLE				0       //�رվ���

#define	EQ_25H					0		//������Ƶ��
#define	EQ_40H					1
#define	EQ_63H					2
#define	EQ_100H					3
#define	EQ_160H					4

#define	EQ_250H					5
#define	EQ_400H					6
#define	EQ_630H					7
#define	EQ_1KH					8
#define	EQ_1K6H					9

#define	EQ_2K5H					10
#define	EQ_4KH					11
#define	EQ_6K3H					12
#define	EQ_10KH					13
#define	EQ_16KH					14


#define	EQ_GAIN_Neg12dB			0		//����������    -12db
#define	EQ_GAIN_Neg11dB			1
#define	EQ_GAIN_Neg10dB			2
#define	EQ_GAIN_Neg9dB			3
#define	EQ_GAIN_Neg8dB			4
#define	EQ_GAIN_Neg7dB			5
#define	EQ_GAIN_Neg6dB			6
#define	EQ_GAIN_Neg5dB			7
#define	EQ_GAIN_Neg4dB			8
#define	EQ_GAIN_Neg3dB			9
#define	EQ_GAIN_Neg2dB			10
#define	EQ_GAIN_Neg1dB			11
#define	EQ_GAIN_0dB				12      //���� 0db
#define	EQ_GAIN_Pos1dB			13
#define	EQ_GAIN_Pos2dB			14
#define	EQ_GAIN_Pos3dB			15
#define	EQ_GAIN_Pos4dB			16
#define	EQ_GAIN_Pos5dB			17
#define	EQ_GAIN_Pos6dB			18
#define	EQ_GAIN_Pos7dB			19
#define	EQ_GAIN_Pos8dB			20
#define	EQ_GAIN_Pos9dB			21
#define	EQ_GAIN_Pos10dB			22
#define	EQ_GAIN_Pos11dB			23
#define	EQ_GAIN_Pos12dB			24    //+12db

#define	HARD_LIMIT				14		//���Ƶƫ���ƣ�0-15��ѡ
#define	CPRS_1XLPF_BP			1		//ѹ���˲������ƣ�0-������1-�ر�
#define	CPRS_KNEE_DIS			0		//�������ƣ�0-������1-�ر�
#define	CPRS_THRSH				8		//�������ޣ�0-15��ѡ 18uV-14mV

#define	ALC_DIS					0//0		//ALC���ƣ�0-������1-�ر�       ����Ƶ�źŽ����޷�
#define	ALC_SOFTKNEE			1		//ALC�յ����ͣ�0-Ӳ�յ㣻1-��յ�  1Ϊ�����޷�ģʽ   0Ϊͻ���޷�ģʽ 
#define	ALC_VMAX				110//4		//ALC���ޣ�0-127��ѡ
#define	ALC_ATTACK				3		//ALC ATTACKʱ�䣺0-7��ѡ
#define	ALC_RELEASE				6		//ALC RELEASEʱ�䣺0-11��ѡ

#define BPSK_NEW_MODE46            1        //1:new mode  0:old mode	
#define AUXCH_EN				 1		  //BIT 15  0=�����ŵ��ر�   1=�����ŵ�����
#define AUXDATA_EN               1        //BIT 14	0 �������ݹر�   1 �������ݿ���
#define AUX_REG_NUM              3        //BIT 13:12 �������ݸ���  0=1��  1=2��    2=3��  3=4�� 
#define AUX_CARRY_NUM46            3        //BIT 11:9 
#define AUX_FDEV				 1		  //BIT 8:7  �����ŵ�Ƶƫ 
 
/*���ָ����ŵ����ݼĴ���*/ 
#define AUX_ADDRA				0x12		//ab
#define AUX_ADDRB				0x13		//cd]
#define AUX_ADDRC				0x14		//BIT 7:0
#define AUX_ADDRD				0x17		//BIT 15:8
#define AUX_ADDR_BAT			0x07		//battery data 

/*AUX DATA REG */
#define AUX_DATA_REGA				0x12	//ab
#define AUX_DATA_REGB				0x13	//cd]
#define AUX_DATA_REGC				0x14	//BIT 7:0
#define AUX_DATA_REGD				0x17	//BIT 15:8
#define AUX_DATA_REGBAT				0x07	//battery data 

/************************************************************************************************************************
                                              ԭdefine.h�еĶ�������
************************************************************************************************************************/
#define		OPEN_BAT			//�򿪵�ؼ�⹦��	



 void KT_Bus_Write46(uint8_t Register_Address, uint16_t Word_Data);
 uint16_t KT_Bus_Read46(uint8_t Register_Address);
 uint8_t KT_WirelessMicTx_Init(uint32_t Freq);
 uint8_t KT_WirelessMicTx_PASW(uint8_t bPA_Switch);
 uint8_t KT_WirelessMicTx_PAGain(uint8_t cPaGain);
 uint8_t KT_WirelessMicTx_Mic_Sens(uint8_t cMicSens);
 uint8_t KT_WirelessMicTx_MuteSel(uint8_t bMute_Sel); 
 uint8_t KT_WirelessMicTx_Tune(int32_t Freq);
 uint8_t KT_WirelessMicTx_BatteryMeter_SW(uint8_t bBatteryMeter_En);
 uint16_t KT_WirelessMicTx_BatteryMeter_Read(void);
 void KT_WirelessMicTx_PowerDownProcedure(void);
 void KT_WirelessMicTx_ECHO(uint8_t bEcho_Dis,uint8_t Echo_Ratio,uint8_t Echo_Delay);
 void KT_WirelessMicTx_EQSW(uint8_t bEq_Dis);
 void KT_WirelessMicTx_EQGAIN(uint8_t Eq_Freq,uint8_t Eq_Gain);
 uint8_t KT_WirelessMicTx_Pilot(uint8_t bPilot_Dis);
 uint8_t KT_WirelessMicTx_Pilot_Fdev(uint8_t cPilot_Fdev); 
 void SettingEQ(void); 
 void AuxDataEnSw(uint8_t State);
 void KTWriteBPSK(u16 * buf);
 void AutoMuteOn(u8 flag);
 FlagStatus KT_WirelessMicTxCheckVolume(void);

//********************************************************
#endif                           //����������		  
//********************************************************
