#include "delay.h"
#include "key.h"

//按键初始化函数
// PA0.15和PC5 设置成输入
void KEY_Init(void) {
  RCC->APB2ENR |= 1 << 2; //使能PORTA时钟
  RCC->APB2ENR |= 1 << 4; //使能PORTC时钟
  // JTAG_Set(SWD_ENABLE);	//关闭JTAG,开启SWD	//似乎没有重复
  GPIOA->CRL &= 0XFFFFFFF0; // PA0设置成输入
  GPIOA->CRL |= 0X00000008;
  GPIOC->CRL &= 0XFFFF000F; // PC1，2，3设置成输入
  GPIOC->CRL |= 0X00008880;
  GPIOC->ODR |= 1 << 1;     // PC1上拉,PA0默认下拉
	GPIOC->ODR |= 1 << 2;
	GPIOC->ODR |= 1 << 3;
  GPIOC->CRH &= 0XFF0FFFFF; // PC13设置成输入
  GPIOC->CRH |= 0X00800000;
  GPIOC->ODR |= 1 << 13; // PC13上拉
}
//按键处理函数
//返回按键值
// mode:0,不支持连续按;1,支持连续按;
//返回值：
// 0，没有任何按键按下
// KEY0_PRES，KEY0按下
// KEY1_PRES，KEY1按下
// WKUP_PRES，WK_UP按下
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode) {
  static u8 key_up = 1; //按键按松开标志
  if (mode)
    key_up = 1; //支持连按
  if (key_up && (KEY0 == 0 || KEY1 == 0 || WK_UP == 1)) {
    delay_ms(10); //去抖动
    key_up = 0;
    if (KEY0 == 0)
      return KEY0_PRES;
    else if (KEY1 == 0)
      return KEY1_PRES;
    else if (WK_UP == 1)
      return WKUP_PRES;
  } else if (KEY0 == 1 && KEY1 == 1 && WK_UP == 0)
    key_up = 1;
  return 0; // 无按键按下
}
