#include <wdt.h>
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"



void WDT_Init(void)
{
	TA=0xAA;
	TA=0x55;
	WDCON=0x07;						                //Setting WDT prescale 
	set_WDCLR;														//Clear WDT timer
	while((WDCON|~SET_BIT6)==0xFF);				//confirm WDT clear is ok before into power down mode
	set_WDTR;														
}

