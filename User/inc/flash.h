#ifndef FLASH_H_
#define FLASH_H_

#define APFlah_Page137 0x4400   //17K
#define APFlah_Page138 0x4480

void Flash_Write(unsigned int PageAdrr,unsigned char *dat,unsigned char num);
void Flash_Read(void);

#endif 



