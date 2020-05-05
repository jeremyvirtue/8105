#ifndef __OS_H
#define __OS_H		
#include "main.h"
 
 
 
#define MAXTASK    2               //定义任务数量







 

 
/**                                       											延时
* @brief  
*/  
typedef struct
{
  u16                   counter;      //计数器
  u16                   delay;         //延时
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

