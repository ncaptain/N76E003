#include <led.h>
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


struct timer runledtimer;


void GPIO_Init(void)
{
	P12_PushPull_Mode;
//	P03_PushPull_Mode;	
	
	timer_set(&runledtimer,CLOCK_SECOND/2);
}


void Thread_Led(void)
{
	if(timer_expired(&runledtimer))
	{
		timer_reset(&runledtimer);
		P12 = !P12;
	}
}