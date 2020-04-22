#include <usart0.h>
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


#define rx0Size 20 // usart0
#define tx0Size 20

uint8_t xdata rx0buf[rx0Size];
uint8_t xdata tx0buf[tx0Size];

uint8_t Tx0Cnt = 0;
uint8_t Rx0Cnt = 0;

bit rx0_flag = 0;

struct timer usart0_timer, checktimer0;

uint8_t xdata sendbuf[20];

void USART0_Init(unsigned long Baud)
{
	P06_Quasi_Mode;
	P07_Quasi_Mode;

	SCON = 0x52;  //UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20; //Timer1 Mode1

	set_SMOD; //UART0 Double Rate Enable
	set_T1M;
	clr_BRCK; //Serial port 0 baud rate clock source = Timer1

	TH1 = 256 - (1000000 / Baud + 1); /*16 MHz */
	set_TR1;

	timer_set(&usart0_timer, CLOCK_SECOND);
	timer_set(&checktimer0, CLOCK_SECOND / 200); // check receive end  //5ms
}

uint8_t xdata tete[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 3, 4, 5};

void USART0_ISR() interrupt 4
{
	if (RI)
	{
		RI = 0;
		rx0buf[Rx0Cnt++] = SBUF;	 // mov data to rx0buf
		rx0_flag = 1;				 // set rec flag
		timer_restart(&checktimer0); // clear check time
	}
	if (TI)
	{
		TI = 0;
		if (Tx0Cnt)
		{
			Tx0Cnt--;
			SBUF = tx0buf[Tx0Cnt]; //mov data to SBUF until TxCnt = 0
		}
	}
}

void usart0_send(uint8_t *dat, uint8_t len)
{
	uint8_t i;
	Tx0Cnt = len - 1;
	for (i = 0; i < len; i++) // reversal the data buf to tx0buf
		tx0buf[i] = dat[Tx0Cnt - i];
	SBUF = dat[0]; // trigger the send interrupt
}

void Thread_USART0(void)
{
	if (timer_expired(&usart0_timer))
	{
		timer_reset(&usart0_timer);
		
//		sprintf((char *)sendbuf,"innov-energy");
//		usart0_send(sendbuf,strlen((char *)sendbuf));
		/*
		do some usart things
		
		*/
	}

	if (rx0_flag)
	{
		if (timer_expired(&checktimer0))
		{
			usart0_send(rx0buf, Rx0Cnt); // do some data deal logic
			rx0_flag = 0;
			Rx0Cnt = 0;
		}
	}
}
