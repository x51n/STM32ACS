#include "dor.h"
#include "led.h"
#include "sys.h"
#include "delay.h"

void dor_open(void) {
  LED1 = 0;
  delay_ms(1000);
  LED1 = 1;
  delay_ms(200);
}
