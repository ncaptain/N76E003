#ifndef TIME_H_
#define TIME_H_


#define CLOCK_SECOND 	1000

struct timer 
{
	int start;
	int interval;
};


void timer_set(struct timer *t, int interval);
void timer_reset(struct timer *t);
int timer_expired(struct timer *t);
void timer_restart(struct timer *t);

void Timer0_Init(void);
void Thread_Led(void);

#endif 