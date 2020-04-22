#include "adc.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

void ADC_Init(void)
{
	Enable_ADC_AIN6;  //Enable IN6  P03
}
