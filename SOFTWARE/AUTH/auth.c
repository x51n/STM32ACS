#include "auth.h"
#include "delay.h"
#include "dor.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "sec.h"
#include "wg.h"
#include "userkey.h"

int auth_faultflag = 2;
extern u8 dat[26];
extern u8 usersum;
extern u8 datatemp[];
u8 valid_dat[1][26];
void auth_fault(void);
void auth_pass(void);
int i,j;


void auth(void) {
		for(i=0;i<26;i++){
		valid_dat[0][i] = datatemp[i];
		}
  for (j=usersum-1; j >= -1; j--) {
    for (i = 0; i <= 25; i++) {
      if (valid_dat[0][i] != dat[i]){
				auth_faultflag = 1;
        break;}
      else if(valid_dat[j][25]==dat[25])
        auth_faultflag = 0;
    }
    if (auth_faultflag == 0) {
      auth_pass(); 
			 break;//验证成功
    } else if (j == -1 || auth_faultflag == 1)
      auth_fault(); //验证失败
			break;
  }
}

void auth_pass(void) { 
		dor_open(); 
	}

void auth_fault(void) { 
	      LED0 = 0;
        delay_ms(200);
        LED0 = 1;
        delay_ms(200);
		    LED0 = 0;
        delay_ms(200);
        LED0 = 1;
        delay_ms(200);
}
