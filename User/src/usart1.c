#include "usart1.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#define rx1Size 20         // usart0 
#define tx1Size 20

uint8_t xdata rx1buf[rx1Size];
uint8_t xdata tx1buf[tx1Size];

uint8_t Tx1Cnt = 0;                 
uint8_t Rx1Cnt = 0;                 
 
bit rx1_flag = 0;

struct timer usart1_timer,checktimer1;  

void USART1_Init(unsigned long Baud)
{
		P02_Quasi_Mode;
		P16_Quasi_Mode;
	
	  SCON_1 = 0x52;   //UART1 Mode1,REN_1=1,TI_1=1
    T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)

		RH3    = HIBYTE(65536 - (1000000/Baud)-1);  		/*16 MHz */
		RL3    = LOBYTE(65536 - (1000000/Baud)-1);			/*16 MHz */

    set_TR3;         //Trigger Timer3
	
		timer_set(&usart1_timer,CLOCK_SECOND);
		timer_set(&checktimer1,CLOCK_SECOND/200);
} 	


void USART1_ISR() interrupt 15
{
	if (RI_1)
	{
		RI_1 = 0;
		rx1buf[Rx1Cnt++] = SBUF_1;            // mov data to rx0buf  
		rx1_flag = 1;                      // set rec flag
		timer_restart(&checktimer1);        // clear check time
	}
	if (TI_1)
	{
		TI_1 = 0;
		if (Tx1Cnt)
		{
			Tx1Cnt--;
			SBUF_1 = tx1buf[Tx1Cnt];           //mov data to SBUF until TxCnt = 0
		}
	}
}



void usart1_send(uint8_t *dat, uint8_t len)  
{
	uint8_t i;
	Tx1Cnt = len - 1;
	for (i = 0; i < len; i++)             // reversal the data buf to tx0buf
		tx1buf[i] = dat[Tx1Cnt - i];
	SBUF_1 = dat[0];                        // trigger the send interrupt
}


void Thread_USART1(void)
{
	if (timer_expired(&usart1_timer))
	{
		timer_reset(&usart1_timer);
		
//		usart1_send(sedd,5);
		/*
		do some usart things
		
		*/
	}	
	
	if (rx1_flag)
	{
		if (timer_expired(&checktimer1))
		{
			usart1_send(rx1buf,Rx1Cnt);     // do some data deal logic
			rx1_flag = 0;
			Rx1Cnt = 0;
		}
	}	
	
}
