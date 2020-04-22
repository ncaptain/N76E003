#ifndef USART0_H_
#define USART0_H_



void USART0_Init(unsigned long Baud);
void Thread_USART0(void);


void usart0_send(unsigned char *dat,unsigned char len);
void UartRxMonitor(void);

#endif 



