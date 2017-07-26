#include "ids.h"
#include "led.h"
#include "delay.h"

//按键初始化函数
//PA0.15和PC5 设置成输入
void IDS_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PA15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入  //todo
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA15
}



//红外传感器扫描处理函数
u8 IDS_Scan(void)
{
	if(ids == 0)return ids_on;
	return 0;
}


void IDS_Alarm(void)
{
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;


}
