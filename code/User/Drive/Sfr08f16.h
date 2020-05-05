/**********************************************************************************
**********************************************************************************/

/*2016-12-1 Ver1.0 By Dean
1.修改REG定义与MCU1101P一致，方便后续快速移植
*/
#ifndef __SFR08F16P_H
#define __SFR08F16P_H

/*说明:
[2016.11.28]
  1 前面小x打头的寄存器表示需要由dptr来访问;
  2 符号ASM: 用户程序若使用的是汇编语言,应定义ASM为1,即#define	ASM 1, C语言应使ASM不为1;
  3 符号EXSFR: EXSFR定义为1,增加扩展的寄存器定义;
*/
#define	ASM 0      // =1,用户编译的是汇编语言
#define	EXSFR 0    // =1,表示使用扩展寄存器

//----------------------------------------------------------------------------------------------------------------------------

/******  MCU内核  ******/
sfr  P0 = 0x80;
sfr  P1 = 0x90;
sfr  P2 = 0xA0;
sfr  P3 = 0xB0;
sfr PSW    = 0xD0;    // 程序状态字
sfr ACC    = 0xE0;    // 累加器
sfr B      = 0xF0;    // B寄存器
sfr SP     = 0x81;    // 堆栈指针
sfr DPL    = 0x82;    // 数据指针低字节
sfr DPH    = 0x83;    // 数据指针高字节

sfr  PCON     = 0x87;    // 电源控制寄存器
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;

sfr IE      = 0xA8;    // 中断允许寄存器
sfr IP      = 0xB8;    // 中断优先级寄存器
sfr AUXR1  = 0xA2;    // DPTR选择寄存器
sfr MOVXRH = 0xA1;    // Ri间接寻址高8位地址寄存器
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
sfr  SCON0    = 0x98;    // UART0控制寄存器

sbit SM0   = SCON0^7;
sbit SM1   = SCON0^6;
sbit SM2   = SCON0^5;
sbit REN  = SCON0^4;
sbit TB8  = SCON0^3;
sbit RB8  = SCON0^2;
sbit TI   = SCON0^1;
sbit RI   = SCON0^0;


/*******************************INTC***********************/
sfr EIE1    = 0xA9;    // 扩展中断允许寄存器1
sfr EIE2    = 0xAA;    // 扩展中断允许寄存器2
sfr EIP1    = 0xB9;    // 扩展中断优先级寄存器1
sfr EIP2    = 0xBA;    // 扩展中断优先级寄存器2
sfr EINTCS0 = 0xAC;    // 外部中断控制与状态寄存器0
sfr EINTCS1 = 0xBC;    // 外部中断控制与状态寄存器1

/******************************PMU**************************************************************************/





//----------------------------------------------------------------------------------------------------------------------------

/******  以下寄存器有所变更  ******/
//sfr	 VMC0 	 = 0xA5;  // 低压控制			/*注意！！！ 寄存器有变动*/
sfr  LVDCON   = 0xA5;    // 低压检测控制寄存器		//LVREN LVRS位置调整	/*注意！！！ 寄存器有变动*/
sfr  LVRCON   = 0xA6;    // 低压复位控制寄存器	/*注意！！！ 寄存器有变动*/
//sfr  SPMC0	 = 0xA6;  // 系统电源管理	/*注意！！！ 寄存器有变动*/




#if  ASM == 1
	xSTOPCFG  EQU 0FFA0H   // 停机模式配置寄存器
	xBGPTRIM  EQU 0FFF2H		// 基准源校准寄存器 ===增加！	/*注意！！！ 寄存器有变动*/		
#else
	#define  xSTOPCFG  (*(volatile unsigned char xdata *)0xFFA0)    // 停机模式配置寄存器
	#define	xBGPTRIM (*(volatile unsigned char xdata *)0xFFF2)		// 基准源校准寄存器	===增加	/*注意！！！ 寄存器有变动*/
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  复位RESET  ******/

sfr  RSTSRC = 0xA7;    // 复位标志
	
	
sfr CPFRHS =0xAD;		//===增加	/*注意！！！ 寄存器有变动*/

//----------------------------------------------------------------------------------------------------------------------------

/******  看门狗定时器WDT  ******/

sfr WDTCON   = 0xDD;    // WDT 分频控制		//ADDR变化！	/*注意！！！ 寄存器有变动*/
sfr WDTCLR0  = 0xDE;    // WDT清零寄存器0		//ADDR变化！	/*注意！！！ 寄存器有变动*/
sfr WDTCLR1  = 0xDF;    // WDT清零寄存器1		//ADDR变化！	/*注意！！！ 寄存器有变动*/

//----------------------------------------------------------------------------------------------------------------------------

/******  时钟管理CKM  ******/

sfr MCKSET   = 0x91;    // 系统主时钟选择寄存器

sfr	MCKDIV   = 0x91;

sfr WPKEY    = 0x92;    // 时钟状态切换钥匙寄存器		//ADDR变化！	/*注意！！！ 寄存器有变动*/
//sfr  CLKEN   = 0x93;   	//已删除此寄存器	/*注意！！！ 寄存器有变动*/
//sfr  PLLCON  = 0x96;		//已删除此寄存器	/*注意！！！ 寄存器有变动*/


#if  ASM ==1
	xSYSCFG   EQU    0FFA2H    // 时钟配置
	xLFCSCON  EQU    0FFEEH    // 低频时钟控制寄存器		//===增加	/*注意！！！ 寄存器有变动*/
	xTESTCON  EQU	 0FFAFH    // 测试控制寄存器
	xPCGC0    EQU	 0FF60H    // 外设门控时钟设置0		//===增加	/*注意！！！ 寄存器有变动*/
//	xPCGC1    EQU	 0FF61H    // 外设门控时钟设置1			
//	xCRYCFG   EQU	 0FFF0H    // CRYL低频振荡模式选择

#else
	#define  xSYSCFG   (*(volatile unsigned char xdata *)0xFFA2)    // 时钟配置
	#define  xLFCSCON  (*(volatile unsigned char xdata *)0xFFEE)    // 低频时钟控制寄存器
	#define  xTESTCON  (*(volatile unsigned char xdata *)0xFFAF)    // 测试控制寄存器
	#define  xPCGC0    (*(volatile unsigned char xdata *)0xFF60)    // 外设门控时钟设置0
//	#define  xPCGC1    (*(volatile unsigned char xdata *)0xFF61)    // 外设门控时钟设置1
//	#define  xCRYCFG   (*(volatile unsigned char xdata *)0xFFF0)    // CRYL低频振荡模式选择
	#define xRCHTRIM	 (*(volatile unsigned char xdata *)0xFFF4)		//RCH校准寄存器
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  通用I/O口GPIO  ******/
/*注意！！！ 寄存器有变动*/
/* P4/P5/P9位置变动，改为可位寻址访问！  */
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



sfr  P0MDL = 0xEC;    // P0.0~P0.3 IO模式控制，00:施密特输入，无上拉，01：输入，有上拉，10：推挽输出，11：开漏输出
sfr  P1MDL = 0xED;    // P1.0~P1.3
sfr  P2MDL = 0xEE;    // P2.0~P2.3
sfr  P3MDL = 0xEF;    // P3.0~P3.3
sfr  P0MDH = 0xFC;    // P0.4~P0.7
sfr  P1MDH = 0xFD;    // P1.4~P1.7
sfr  P2MDH = 0xFE;    // P2.4~P2.7
sfr  P3MDH = 0xFF;    // P3.4~P3.7


#if  ASM ==1
	xP4MDL   EQU  0FFA4H   // 端口4模式配置寄存器(低字节)
	xP4MDH   EQU  0FFB4H   // 端口4模式配置寄存器(高字节)
	xP5MDL   EQU  0FFA5H   // 端口5模式配置寄存器(低字节)
	xP5MDH   EQU  0FFB5H   // 端口5模式配置寄存器(高字节)
	xP9MDL   EQU  0FFA9H   // 端口9模式配置寄存器(低字节)
	xP9MDH   EQU  0FFB9H   // 端口9模式配置寄存器(高字节) P9.5(复位脚)不能作为输出
	xP1AEN   EQU  0FFC1H   // 端口1模拟通道允许寄存器 
	xP3AEN   EQU  0FFC3H   // 端口3模拟通道允许寄存器 
	xIOMUX0  EQU  0FFE0H   // IO复用控制寄存器0 
	xIOMUX1  EQU  0FFE1H   // IO复用控制寄存器1
	xIOMUX2  EQU  0FFE2H   // IO复用控制寄存器2
//	xIOMUX3  EQU  0FFE3H   // IO复用控制寄存器3 
#else
	#define  xP4MDL	     (*(volatile unsigned char xdata *)0xFFA4)    // 端口4模式配置寄存器(低字节)
	#define  xP4MDH	     (*(volatile unsigned char xdata *)0xFFB4)    // 端口4模式配置寄存器(高字节)
	#define  xP5MDL	     (*(volatile unsigned char xdata *)0xFFA5)    // 端口5模式配置寄存器(低字节)
  #define  xP5MDH	     (*(volatile unsigned char xdata *)0xFFB5)    // 端口5模式配置寄存器(高字节)
	#define  xP9MDL	     (*(volatile unsigned char xdata *)0xFFA9)    // 端口9模式配置寄存器(低字节)
	#define  xP9MDH	     (*(volatile unsigned char xdata *)0xFFB9)    // 端口9模式配置寄存器(高字节)	
	#define  xP1AEN      (*(volatile unsigned char xdata *)0xFFC1)    // 端口1模拟通道允许寄存器
	#define  xP3AEN      (*(volatile unsigned char xdata *)0xFFC3)    // 端口3模拟通道允许寄存器	
	#define  xIOMUX0     (*(volatile unsigned char xdata *)0xFFE0)    // IO复用控制寄存器0 
	#define  xIOMUX1     (*(volatile unsigned char xdata *)0xFFE1)    // IO复用控制寄存器1 
	#define  xIOMUX2     (*(volatile unsigned char xdata *)0xFFE2)    // IO复用控制寄存器2 
//	#define  xIOMUX3     (*(volatile unsigned char xdata *)0xFFE3)    // IO复用控制寄存器3 
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

/******  串口UART ******/

sfr  SBUF0    = 0x99;    // UART0数据缓冲寄存器
//sfr  SCON0    = 0x98;    // UART0控制寄存器
sfr  BRCON0   = 0x8E;    // UART0波特率控制寄存器
sfr  BRTIM0   = 0x8F;    // 时钟发生器初值设置寄存器	

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

/******  钟表定时器WT ******/
sfr  WTCON    = 0xBF;    // 钟表定时器控制寄存器

#if  ASM ==1
	xT8   EQU  0FF9BH        // 8位下行定时器T8读寄存器计数值
	xT8RL   EQU  0FF9BH     //写寄存器初值
#else
	#define  xT8   (*(volatile unsigned char xdata *)0xFF9B)     // 8位下行定时器T8读寄存器计数值
	#define  xT8RL   (*(volatile unsigned char xdata *)0xFF9B)   //写寄存器初值
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  键盘中断KBI ******/

sfr  KBIFLG  = 0x9E;    // 键盘中断标志寄存器

#if  ASM ==1
	xKBICON  EQU  0FFDAH      // P0键盘中断控制寄存器
	xKBIWKP  EQU  0FFDBH      // P0键盘中断极性选择寄存器
	xP1KBICON  EQU  0FFDCH    // P1键盘中断控制寄存器
	xP1KBIWKP  EQU  0FFDDH    // P1键盘中断极性选择寄存器
	xP2KBICON  EQU  0FFDEH    // P2键盘中断控制寄存器
	xP2KBIWKP  EQU  0FFDFH    // P2键盘中断极性选择寄存器
	xP4KBICON  EQU  0FFECH    // P4键盘中断控制寄存器
	xP4KBIWKP  EQU  0FFEDH    // P4键盘中断极性选择寄存器
#else
	#define  xKBICON    (*(volatile unsigned char xdata *)0xFFDA)    // P0键盘中断控制寄存器
	#define  xKBIWKP    (*(volatile unsigned char xdata *)0xFFDB)    // P0键盘中断极性选择寄存器
	#define  xP1KBICON  (*(volatile unsigned char xdata *)0xFFDC)    // P1键盘中断控制寄存器
	#define  xP1KBIWKP  (*(volatile unsigned char xdata *)0xFFDD)    // P1键盘中断极性选择寄存器
	#define  xP2KBICON  (*(volatile unsigned char xdata *)0xFFDE)    // P2键盘中断控制寄存器
	#define  xP2KBIWKP  (*(volatile unsigned char xdata *)0xFFDF)    // P2键盘中断极性选择寄存器
	#define  xP4KBICON  (*(volatile unsigned char xdata *)0xFFEC)    // P4键盘中断控制寄存器
	#define  xP4KBIWKP  (*(volatile unsigned char xdata *)0xFFED)    // P4键盘中断极性选择寄存器

#endif


//----------------------------------------------------------------------------------------------------------------------------

/******  定时器TIMER ******/


#if  ASM ==1
	xTIMPRS    EQU  0FFCAH    // Timer预分频控制寄存器
	xTIMCFG    EQU  0FFCDH    // 定时器TIMER扩展PWM配置位
#else
	#define xTIMPRS    (*(volatile unsigned char xdata *)0xFFCA)    // Timer预分频控制寄存器
	#define xTIMCFG    (*(volatile unsigned char xdata *)0xFFCD)    // Timer预分频控制寄存器
#endif

//----------------------------------------------------------------------------------------------------------------------------

/******  定时器TIMER2 ******/


sfr T2MOD    =  0xC1;//T2模式寄存器
sfr T2CPL1   =  0xC2;//T2捕获器1低字节
sfr T2CPH1   =  0xC3;//T2捕获器1高字节
sfr T2CPL2   =  0xC4;//T2捕获器1低字节
sfr T2CPH2   =  0xC5;//T2捕获器1高字节
sfr T2CAP    =  0xC6;//T2捕获设置寄存器
sfr T2CAPS   =  0xC7;//T2捕获状态寄存器
sfr T2CON    =  0xC9;// 定时器2控制寄存器
sfr T2L      =  0xCA;// 定时器2低字节
sfr T2H      =  0xCB;// 定时器2高字节
sfr T2EXS    = 0xCC;//T2外部触发源选择寄存器
sfr T2CPL3   = 0xCD;//T2捕获寄存器3低字节
sfr T2CPH3   = 0xCE;
sfr PPG2CON   = 0xCF;//PPG控制寄存器
 

//----------------------------------------------------------------------------------------------------------------------------

/******  载波定时器CRT  ******/

sfr  CRTCON1   = 0xE1;    // 载波定时器控制寄存器1
sfr  CRTCON2   = 0xE2;    // 载波定时器控制寄存器2
sfr  CRTCNT    = 0xE3;    // 载波定时器 
sfr  CRTDATA0  = 0xE4;    // 载波定时器初值寄存器0
sfr  CRTDATA1  = 0xE5;    // 载波定时器初值寄存器1

//----------------------------------------------------------------------------------------------------------------------------

/******  标准化SPI  ******/

sfr  SPICON0 = 0xF8;    // SPI控制器0
sfr  SPICON1 = 0xF9;    // SPI控制器1
sfr  SPIFLG  = 0xFA;    // SPI标志寄存器
sfr  SPIBUF  = 0xFB;    // SPI发送数据寄存器

sbit  SPIE    = SPICON0^0;
sbit  MSTEN   = SPICON0^1;
sbit  LSBF    = SPICON0^2;
sbit  SPC     = SPICON0^3;
sbit  BIDIROE = SPICON0^4;
sbit  MODFEN  = SPICON0^5;
sbit  SPTIE   = SPICON0^6;
sbit  SPRIE   = SPICON0^7;
//----------------------------------------------------------------------------------------------------------------------------

/******  模拟比较器ACMP  ******/

sfr  CP0CON     = 0xAE;     // 模拟比较器0控制寄存器
sfr  CP0VRCON   = 0xAF;     // 模拟比较器0内部参考电压控制寄存器  

//----------------------------------------------------------------------------------------------------------------------------

/******  模数转换器ADC  ******/

sfr  ADCON       = 0xD8;     // ADC控制寄存器
sfr  ADRESL      = 0xD9;     // ADC转换结果低8位  
sfr  ADRESH      = 0xDA;     // ADC转化结果高8位

sfr  CMPDATAL    = 0xD9;    //AD结果比较低8位寄存器，与ADRESL共用地址
sfr  CMPDATAH    = 0xDA;    //AD结果比较高8位寄存器，与ADRESH共用地址
/*  ADCON  */
sbit ADGO    = ADCON^2;
sbit ADEN    = ADCON^3;


#if  ASM ==1
  xADCMOD    EQU  0FFADH  //ADC 模式设定
	xADCFG     EQU  0FFAEH     // ADC配置寄存器
#else
	#define xADCFG    (*(volatile unsigned char xdata *) 0xFFAE)    // ADC配置寄存器
	#define xADCMOD   (*(volatile unsigned char xdata *) 0xFFAD)    // ADC模式设定寄存器
	#define xADGC     (*(volatile unsigned char xdata *) 0xFF60)    // ADC clock
#endif 

//----------------------------------------------------------------------------------------------------------------------------

/******  液晶显示LCD  ******/

#if  ASM == 1
	xLCDPEN0  EQU  0FF20H   // LCD驱动管脚允许位寄存器0  1816-->P0端口
	xLCDPEN1  EQU  0FF21H   // LCD驱动管脚允许位寄存器1  1816-->P1端口
	xLCDPEN2  EQU  0FF22H   // LCD驱动管脚允许位寄存器2  1816-->P2端口
	xLCDPEN3  EQU  0FF23H   // LCD驱动管脚允许位寄存器3  1816-->P3端口
	xLCDPEN4  EQU  0FF24H   // LCD驱动管脚允许位寄存器4  1816-->P4端口
	xLCDPEN5  EQU  0FF25H   // LCD驱动管脚允许位寄存器5  1816-->P5端口
#else
	#define  xLCDPEN0  (*(volatile unsigned char xdata *)0xFF20)   // LCD驱动管脚允许位寄存器0  1816-->P0端口
	#define  xLCDPEN1  (*(volatile unsigned char xdata *)0xFF21)   // LCD驱动管脚允许位寄存器1  1816-->P1端口
	#define  xLCDPEN2  (*(volatile unsigned char xdata *)0xFF22)   // LCD驱动管脚允许位寄存器2  1816-->P2端口
	#define  xLCDPEN3  (*(volatile unsigned char xdata *)0xFF23)   // LCD驱动管脚允许位寄存器3  1816-->P3端口
	#define  xLCDPEN4  (*(volatile unsigned char xdata *)0xFF24)   // LCD驱动管脚允许位寄存器4  1816-->P4端口
	#define  xLCDPEN5  (*(volatile unsigned char xdata *)0xFF25)   // LCD驱动管脚允许位寄存器5  1816-->P5端口

#endif

#if  ASM ==1
	xLCDCON     EQU  0FF80H   // LCD控制寄存器
	xLCDRCON    EQU  0FF81H   // LCD电阻型驱动控制寄存器
	xLCDTKCON   EQU  0FF82H   // LCD闪烁控制寄存器
	xLCDTKADDR  EQU  0FF84H   // LCD闪烁点1地址
	xLCDSCDIV   EQU  0FF86H   // LCD扫描时钟源分频寄存器
	xLCDDATA0   EQU  0FF00H	  // LCD映射存储器0
	xLCDDATA1   EQU  0FF01H	  // LCD映射存储器1
	xLCDDATA2   EQU  0FF02H	  // LCD映射存储器2
	xLCDDATA3   EQU  0FF03H	  // LCD映射存储器3
	xLCDDATA4   EQU  0FF04H	  // LCD映射存储器4
	xLCDDATA5   EQU  0FF05H	  // LCD映射存储器5
	xLCDDATA6   EQU  0FF06H	  // LCD映射存储器6
	xLCDDATA7   EQU  0FF07H   // LCD映射存储器7
	xLCDDATA8   EQU  0FF08H	  // LCD映射存储器8
	xLCDDATA9   EQU  0FF09H	  // LCD映射存储器9
	xLCDDATA10  EQU  0FF0AH	  // LCD映射存储器10
	xLCDDATA11  EQU  0FF0BH	  // LCD映射存储器11
	xLCDDATA12  EQU  0FF0CH	  // LCD映射存储器12
	xLCDDATA13  EQU  0FF0DH	  // LCD映射存储器13
	xLCDDATA14  EQU  0FF0EH	  // LCD映射存储器14
	xLCDDATA15  EQU  0FF0FH   // LCD映射存储器15
	xLCDDATA16  EQU  0FF10H	  // LCD映射存储器16
	xLCDDATA17  EQU  0FF11H	  // LCD映射存储器17
	xLCDDATA18  EQU  0FF12H	  // LCD映射存储器18
	xLCDDATA19  EQU  0FF13H	  // LCD映射存储器19
	xLCDDATA20  EQU  0FF14H	  // LCD映射存储器20
	xLCDDATA21  EQU  0FF15H	  // LCD映射存储器21
	xLCDDATA22  EQU  0FF16H	  // LCD映射存储器22
	xLCDDATA23  EQU  0FF17H   // LCD映射存储器23
	xLCDDATA24  EQU  0FF18H	  // LCD映射存储器24
	xLCDDATA25  EQU  0FF19H	  // LCD映射存储器25
	xLCDDATA26  EQU  0FF1AH	  // LCD映射存储器26
	xLCDDATA27  EQU  0FF1BH	  // LCD映射存储器27
	xLCDDATA28  EQU  0FF1CH	  // LCD映射存储器28
	xLCDDATA29  EQU  0FF1DH	  // LCD映射存储器29
	xLCDDATA30  EQU  0FF1EH	  // LCD映射存储器30
	xLCDDATA31  EQU  0FF1FH   // LCD映射存储器31
	xLCDDATA32  EQU  0FF30H	  // LCD映射存储器32
	xLCDDATA33  EQU  0FF31H	  // LCD映射存储器33
	xLCDDATA34  EQU  0FF32H	  // LCD映射存储器34
	xLCDDATA35  EQU  0FF33H   // LCD映射存储器35
#else
	#define  xLCDCON     (*(volatile unsigned char xdata *)0xFF80)   //	LCD控制寄存器
	#define  xLCDRCON    (*(volatile unsigned char xdata *)0xFF81)   //	LCD电阻型驱动控制寄存器
	#define  xLCDTKCON   (*(volatile unsigned char xdata *)0xFF82)   //	LCD闪烁控制寄存器
	#define  xLCDTKADDR  (*(volatile unsigned char xdata *)0xFF84)   //	LCD闪烁点1地址
	#define  xLCDSCDIV   (*(volatile unsigned char xdata *)0xFF86)  //LCD扫描时钟源分频寄存器
	#define  xLCDDATA0   (*(volatile unsigned char xdata *)0xFF00)	 //	LCD映射存储器0
	#define  xLCDDATA1   (*(volatile unsigned char xdata *)0xFF01)	 //	LCD映射存储器1
	#define  xLCDDATA2   (*(volatile unsigned char xdata *)0xFF02)	 //	LCD映射存储器2
	#define  xLCDDATA3   (*(volatile unsigned char xdata *)0xFF03)	 //	LCD映射存储器3
	#define  xLCDDATA4   (*(volatile unsigned char xdata *)0xFF04)	 //	LCD映射存储器4
	#define  xLCDDATA5   (*(volatile unsigned char xdata *)0xFF05)	 //	LCD映射存储器5
	#define  xLCDDATA6   (*(volatile unsigned char xdata *)0xFF06)	 //	LCD映射存储器6
	#define  xLCDDATA7   (*(volatile unsigned char xdata *)0xFF07) 	 //	LCD映射存储器7
	#define  xLCDDATA8   (*(volatile unsigned char xdata *)0xFF08)	 //	LCD映射存储器8
	#define  xLCDDATA9   (*(volatile unsigned char xdata *)0xFF09)	 //	LCD映射存储器9
	#define  xLCDDATA10  (*(volatile unsigned char xdata *)0xFF0A)	 //	LCD映射存储器10
	#define  xLCDDATA11  (*(volatile unsigned char xdata *)0xFF0B)	 //	LCD映射存储器11
	#define  xLCDDATA12  (*(volatile unsigned char xdata *)0xFF0C)	 //	LCD映射存储器12
	#define  xLCDDATA13  (*(volatile unsigned char xdata *)0xFF0D)	 //	LCD映射存储器13
	#define  xLCDDATA14  (*(volatile unsigned char xdata *)0xFF0E)	 //	LCD映射存储器14
	#define  xLCDDATA15  (*(volatile unsigned char xdata *)0xFF0F) 	 //	LCD映射存储器15
	#define  xLCDDATA16  (*(volatile unsigned char xdata *)0xFF10)	 //	LCD映射存储器16
	#define  xLCDDATA17  (*(volatile unsigned char xdata *)0xFF11)	 //	LCD映射存储器17
	#define  xLCDDATA18  (*(volatile unsigned char xdata *)0xFF12)	 //	LCD映射存储器18
	#define  xLCDDATA19  (*(volatile unsigned char xdata *)0xFF13)	 //	LCD映射存储器19
	#define  xLCDDATA20  (*(volatile unsigned char xdata *)0xFF14)	 //	LCD映射存储器20
	#define  xLCDDATA21  (*(volatile unsigned char xdata *)0xFF15)	 //	LCD映射存储器21
	#define  xLCDDATA22  (*(volatile unsigned char xdata *)0xFF16)	 //	LCD映射存储器22
	#define  xLCDDATA23  (*(volatile unsigned char xdata *)0xFF17) 	 //	LCD映射存储器23
	#define  xLCDDATA24  (*(volatile unsigned char xdata *)0xFF18)	 //	LCD映射存储器24
	#define  xLCDDATA25  (*(volatile unsigned char xdata *)0xFF19)	 //	LCD映射存储器25
	#define  xLCDDATA26  (*(volatile unsigned char xdata *)0xFF1A)	 //	LCD映射存储器26
	#define  xLCDDATA27  (*(volatile unsigned char xdata *)0xFF1B)	 //	LCD映射存储器27
	#define  xLCDDATA28  (*(volatile unsigned char xdata *)0xFF1C)	 //	LCD映射存储器28
	#define  xLCDDATA29  (*(volatile unsigned char xdata *)0xFF1D)	 //	LCD映射存储器29
	#define  xLCDDATA30  (*(volatile unsigned char xdata *)0xFF1E)	 //	LCD映射存储器30
	#define  xLCDDATA31  (*(volatile unsigned char xdata *)0xFF1F) 	 //	LCD映射存储器31
	#define  xLCDDATA32  (*(volatile unsigned char xdata *)0xFF30)   //	LCD映射存储器32
	#define  xLCDDATA33  (*(volatile unsigned char xdata *)0xFF31)	 //	LCD映射存储器33
	#define  xLCDDATA34  (*(volatile unsigned char xdata *)0xFF32)	 //	LCD映射存储器34
	#define  xLCDDATA35  (*(volatile unsigned char xdata *)0xFF33) 	 //	LCD映射存储器35
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
  GPIO_OI=0,//输入悬空。
  GPIO_UI,//输入上拉。
  GPIO_PP,//推挽输出。
  GPIO_OP,//开漏输出。
}GPIOType; 


#define GPIO_SET(IO,TYPE,BIT) (IO=(IO&(~(0x03<<(BIT<<1))))|(TYPE<<(BIT<<1))) 
//#define GPIO_RESET(IO,BIT) (IO &=~(0x11<<(2*BIT))} 
  
#endif	