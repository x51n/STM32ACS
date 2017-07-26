#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "stm32f10x.h"
#include"stdio.h"
#define DEVICE_ID "W5200"

#define FW_VER_HIGH  1
#define FW_VER_LOW    0

typedef  void (*pFunction)(void);

void set_network(void);
void write_config_to_eeprom(void);
void set_default(void);
void Reset_W5500(void);

void USART1_Init(void);
//int fputc(int ch, FILE *f);
void USART1_Putc(unsigned char c);
void USART1_Puts(char * str);
//void USART1_IRQHandler(void);
void reboot(void);
void get_config(void);
#endif

