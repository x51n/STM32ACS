#include "auth.h"
#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "usart.h"
#include "wg.h"

int fault_count = 0;
int lock_counter=0;
int delay_start_flag = 0; //计时开始标志
int valid_time_flag = 0; //有效时间标志,0代表有效
void init_delay(void);
void start_valid_time_counter(void);
void setlock(void);
void lock_exit(void);
void unlock_exit(void);
void start_lock_delay(void);

void sec(void) { //表示刷卡验证失败一次
  // fault_count++;
  // if (delay_start_flag == 0) {
  //   start_valid_time_counter();
  // } else if (delay_start_flag == 1) {
  //   if (valid_time_up();) {           //如果在有效时间内
  //     if (fault_count > 5) {          //如果输入错误超过5次
  //       setlock();                    //设置锁定
  //     } else if (unlock_time_up();) { //如果解除锁定时间到
  //       unlock();
  //       init_delay;
  //     }
  //   }
  // }
  fault_count++;
  if (fault_count == 1) {
    start_valid_time_counter();
  }
  if (fault_count == 5) { //如果错误次数小于5，有效时间大于
    if (valid_time_flag == 0) {
      setlock();
    } else if (valid_time_flag == 1) {
      init_delay();
      start_valid_time_counter();
    }
  }
}

void start_valid_time_counter(void) //开始启动记时
{
  init_delay();
  delay_start_flag = 1;
}

void init_delay(void) //初始化计时,相当与重置计时
{
  delay_start_flag = 0;
  fault_count = 0; //重置错误计数器
  valid_time_flag = 0;
}

// void atom_delay(void) //一个计时单位 30秒
// {
//   get_atom_time(); //设计一个生成30秒计时的部分
//}

void valid_time_up(void) //返回判断当前是否为有效时间
{
  if (delay_start_flag == 1) {
    int t;
    t++;
    if (t < 30) {
      valid_time_flag = 0;
    } else if (t == 30) {
      valid_time_flag = 1;
    }
  }
}

// void unlock_time_up(void) //返回当前是否在锁定时间内
// {
//
// }

void setlock(void) {  //该函数为执行延时多少，锁定时单片机
  lock_exit();        //关闭中断
  start_lock_delay(); //只执行该延时程序
  unlock_exit();      //打开中断
  init_delay();       //执行完后初始化计时程序
}

void lock_exit(void)
{

}

void unlock_exit()
{

}

void start_lock_delay()
{
  int p=0,i=2;
  lock_counter++;
  p=i*lock_counter;
  delay_ms(p);
  if (lock_counter>5) {
    lock_counter=0;
  }
}
