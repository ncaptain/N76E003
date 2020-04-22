#ifndef WDT_H_
#define WDT_H_

#define Thread_FeedIWDG()  BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=SET_BIT6;EA=BIT_TMP;

void WDT_Init(void);

#endif 