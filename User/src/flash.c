#include "flash.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"



#define  PAGE_ERASE_AP    0x22
#define  BYTE_PROGRAM_AP  0x21


volatile unsigned char code Data_Flash[10] _at_ APFlah_Page137;

//one page write,pageAdrr must be 128*n
void Flash_Write(uint16_t PageAdrr,uint8_t *dat,uint8_t num)  // num must <= 128   about 5ms
{
	uint8_t i;
	
	//close ISP,IAP
	
	TA = 0xAA;                         //CHPCON is TA protected
	TA = 0x55;
	CHPCON |= 0x01;                    //IAPEN = 1, enable IAP mode
	
	TA = 0xAA;                         //IAPUEN is TA protected
	TA = 0x55;
	IAPUEN |= 0x01;                    //APUEN = 1, enable APROM update
	
	//Erase Page
	
	IAPCN = PAGE_ERASE_AP;             //Erase page 
	IAPAH = (PageAdrr & 0xff00) >> 8;
	IAPAL =  PageAdrr & 0x00ff;
	IAPFD = 0xFF;
	TA = 0xAA;                         //IAPTRG is TA protected
	TA = 0x55;
	IAPTRG |= 0x01;                    //write 1 to IAPGO to trigger IAP process
	
	// write data to flash
	
	for(i=0;i<num;i++)
	{
		IAPCN = BYTE_PROGRAM_AP;           // Program 
		IAPAH = (PageAdrr & 0xff00) >> 8;
		IAPAL =  PageAdrr & 0x00ff;
		IAPFD = dat[i];
		TA = 0xAA;       //IAPTRG is TA protected
		TA = 0x55;
		IAPTRG |= 0x01;  //write 1 to IAPGO to trigger IAP process		
		PageAdrr++;
	}
	
	//reset ISP,IAP
	
	TA = 0xAA;       //IAPUEN is TA protected
	TA = 0x55;
	IAPUEN &= ~0x01; //APUEN = 0, disable APROM update
	
	TA = 0xAA;       //CHPCON is TA protected
	TA = 0x55;
	CHPCON &= ~0x01; //IAPEN = 0, disable IAP mode
}


void Flash_Read(void)
{
	Flash_Write(APFlah_Page137,0x08,1);
	if(Data_Flash[5] == 0x55)   //check  data
	{
		
	}
}