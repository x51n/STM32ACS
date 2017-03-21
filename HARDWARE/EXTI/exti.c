#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "usart.h"
#include "wg.h"

//外部中断0服务程序
void EXTI0_IRQHandler(void) {
  delay_ms(10);   //消抖
  if (WK_UP == 1) // WK_UP按键
  {
    LED0 = !LED0;
    LED1 = !LED1;
  }
  EXTI->PR = 1 << 0; //清除LINE0上的中断标志位
}
//外部中断1服务程序
void EXTI1_IRQHandler(void) {
  delay_ms(10);  //消抖
  if (KEY0 == 0) //按键0
  {
    LED0 = !LED0;
  }
  EXTI->PR = 1 << 1; //清除LINE1上的中断标志位
}
//外部中断15~10服务程序
void EXTI15_10_IRQHandler(void) {
  delay_ms(10);  //消抖
  if (KEY1 == 0) //按键1
  {
    LED1 = !LED1;
  }
  EXTI->PR = 1 << 13; //清除LINE13上的中断标志位
}
//外部中断3服务程序
void EXTI3_IRQHandler(void) {
  WGR_D1();
  EXTI->PR = 1 << 3; //清除LINE1上的中断标志位
}

void EXTI2_IRQHandler(void) {
  WGR_D0();
  EXTI->PR = 1 << 2; //清除LINE1上的中断标志位
}
//外部中断初始化程序
//初始化PA0,PC5,PA15为中断输入.
void EXTI_Init(void) {
  KEY_Init();
  Ex_NVIC_Config(GPIO_A, 0, RTIR);  //上升沿触发
  Ex_NVIC_Config(GPIO_C, 1, FTIR);  //下降沿触发
  Ex_NVIC_Config(GPIO_C, 13, FTIR); //下降沿触发

  Ex_NVIC_Config(GPIO_C, 2, FTIR); //下降沿触发	D0 //韦根中断
  Ex_NVIC_Config(GPIO_C, 3, FTIR); //下降沿触发	D1

  MY_NVIC_Init(1, 1, EXTI0_IRQn, 3);     //抢占2，子优先级2?z组3
  MY_NVIC_Init(1, 1, EXTI1_IRQn, 3);     //抢占2，子优先级1，组3
  MY_NVIC_Init(1, 1, EXTI15_10_IRQn, 3); //抢占2，子优先级0，组3

  MY_NVIC_Init(0, 1, EXTI3_IRQn, 3);
  MY_NVIC_Init(0, 1, EXTI2_IRQn, 3);
}
