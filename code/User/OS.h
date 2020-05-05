#ifndef __OS_H
#define __OS_H		
#include "main.h"
 
 
 
#define MAXTASK    2               //������������







 

 
/**                                       											��ʱ
* @brief  
*/  
typedef struct
{
  u16                   counter;      //������
  u16                   delay;         //��ʱ
}MyDelay;

typedef struct
{
  void        (*Tick)();
  void        (*TaskScan)();   
}OS;

 

 

extern OS xdata os;
void OSInit(void);
void OSTaskScan(void);
void OSTick(void);

#endif

