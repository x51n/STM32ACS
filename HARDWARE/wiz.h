#include "spi.h"


#define WIZ_SCS			    GPIO_Pin_12	// out
#define WIZ_SCLK			GPIO_Pin_3	// out
#define WIZ_MISO			GPIO_Pin_4	// in
#define WIZ_MOSI			GPIO_Pin_5	// out

#define WIZ_RESET		    GPIO_Pin_9	// out
#define WIZ_INT			    GPIO_Pin_6	// in


void WIZ_Init(void);
void WIZ_CS(uint8_t val);
uint8_t SPI3_SendByte(uint8_t byte);
void socket0_int_UDP(void);
void socket1_int_TCP_S(void);
void set_net(void);
