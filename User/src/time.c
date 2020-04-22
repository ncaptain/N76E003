#include <time.h>
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


uint32_t base_cnt = 0;

void timer_set(struct timer *t, int interval)
{
	t->interval = interval;
	t->start = base_cnt;
}
void timer_reset(struct timer *t)
{
	t->start += t->interval;
}
void timer_restart(struct timer *t)
{
	t->start = base_cnt;
}
//void timer_restartonce(struct timer *t,uint8_t *flag)
//{
//	if(!*flag)
//	{
//		*flag = 1;
//		t->start = base_cnt;
//	}
//}
int timer_expired(struct timer *t)
{
	return (int)(base_cnt - t->start) >= (int)t->interval;
}


void Timer0_Init(void)
{
	TMOD|=0x01;
	TH0 = 0xFA;
	TL0 = 0xCA;  
	TR0=1;
	
} 


void Timer0_ISR (void) interrupt 1  //interrupt address is 0x000B
{
    TH0 = 0xFA;
    TL0 = 0xCA;    
    base_cnt++;  
}



