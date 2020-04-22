#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
 
void ISR_Init()	 
{
	EA=1;      //   all interrupt
	EX0=0;     //   exit0 
	ET0=1;     //   time0 
	EX1=0;     //   exit1 
	ET1=0;     //   time1 
	ES=1;      //   usart0
	set_ES_1;  //   usart1 interrupt
}

void main (void)
{
	Timer0_Init();
	USART0_Init(9600);
	USART1_Init(9600);
	GPIO_Init();
	WDT_Init();
	ISR_Init();
	Flash_Read();
  while(1)
	{
		Thread_Led();
		Thread_USART0();
		Thread_USART1();		
		Thread_FeedIWDG();
	}
}


// 222222222222222222
// 333333333333333333


