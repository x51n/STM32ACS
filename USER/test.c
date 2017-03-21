#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "flash.h"
#include "key.h"
#include "led.h"
#include "exti.h"
#include "auth.h"
#include "wg.h"

extern int r_done;	//读取成功标志
u8 datatemp[26];

int main(void)
{
	
	u32 FLASH_SIZE;
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	    //延时初始化
	uart_init(72,9600); //串口初始化
	LED_Init();		  	//初始化与LED连接的硬件接口
	EXTI_Init();		//外部中断初始化
	SPI_Flash_Init();
	FLASH_SIZE = 2 * 1024 * 1024;

	while(1)
	{
		if (r_done == 1) {
			r_done = 0;
			if(dat_check()){
			SPI_Flash_Read(datatemp, FLASH_SIZE - 100,26);
			auth();
			}
		}
	}
	}

