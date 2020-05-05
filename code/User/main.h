#ifndef __main_H
#define __main_H
 
 #include "Sfr08f16.h"
 
 typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
	Disable = 0,
	Enable = 1
		
}FunctionState;

#define MASK_EMPTY  0x00             //Çå¿Õ

typedef   signed char 				int8;
typedef   signed  int 				int16;
typedef   signed long 					int32;

typedef volatile int32  			vs32;
typedef volatile int16  			vs16;
typedef volatile int8   			vs8;


typedef unsigned long  				u32;
typedef unsigned  int 				u16;
typedef unsigned char  				u8;

typedef		u32			uint32_t;
typedef		u16         uint16_t;
typedef		u8			uint8_t;

typedef char			int8_t;
typedef int				int16_t;
typedef long			int32_t;


typedef volatile u32  				vu32;
typedef volatile u16 					vu16;
typedef volatile u8  					vu8;

#define	 B_b0	 0xfc	
#define	 B_b1	 0xf3	
#define	 B_b2	 0xcf	
#define	 B_b3	 0x3f
#define	 B_b4	 0xfc	
#define	 B_b5	 0xf3	
#define	 B_b6	 0xcf	
#define	 B_b7	 0x3f

#define  out_b0	 0x02	
#define	 out_b1	 0x08	
#define	 out_b2	 0x20	
#define	 out_b3	 0x80
#define	 out_b4	 0x02	
#define	 out_b5	 0x08	
#define	 out_b6	 0x20	
#define	 out_b7  0x80

#define  od_b0	 0x03	
#define	 od_b1	 0x0c	
#define	 od_b2	 0x30	
#define	 od_b3	 0xc0
#define	 od_b4	 0x03	
#define	 od_b5	 0x0c	
#define	 od_b6	 0x30	
#define	 od_b7   0xc0



#define	 in_b0	 0x01	
#define	 in_b1	 0x04	
#define	 in_b2	 0x10	
#define	 in_b3	 0x40
#define	 in_b4	 0x01	
#define	 in_b5	 0x04	
#define	 in_b6	 0x10	
#define	 in_b7	 0x40



#endif



