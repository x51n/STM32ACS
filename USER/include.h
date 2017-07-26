#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "spi.h"
#include "flash.h"
#include "exti.h"
#include "wg.h"
#include "auth.h"
#include "dor.h"
#include "ids.h"
#include <stdio.h>

//W5500 头文件
#include "mcu_int.h"
#include "config.h"
#include "device.h"
#include "spi.h"
#include "socket.h"
#include "w5500.h"
#include "md5.h"
#include "wiz.h"

//VS1053 头文件
#include "mp3player.h"
#include "recorder.h"
#include "vs10xx.h"



#define WIZ_SCS			    GPIO_Pin_12	// out
#define WIZ_SCLK			GPIO_Pin_3	// out
#define WIZ_MISO			GPIO_Pin_4	// in
#define WIZ_MOSI			GPIO_Pin_5	// out

#define WIZ_RESET		    GPIO_Pin_9	// out
#define WIZ_INT			    GPIO_Pin_6	// in
