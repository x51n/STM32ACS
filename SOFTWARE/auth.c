#include "auth.h"
#include "delay.h"
#include "dor.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "sec.h"
#include "wg.h"
#include "userkeys.h"
#include "include.h"


int auth_faultflag = 2;
extern u8 dat[26];
extern u8 usersum;
extern u8 datatemp[];
extern long readkey;
extern long UID;
extern u16 FLASH_SIZE;
extern u8 usersum;
u8 usersumtemp[1];
int auth_flag=0;

u8 valid_dat[1][26];
void auth_fault(void);
void auth_pass(void);
int i,j;

void auth(void) {
	int i,readsum=0;
	auth_flag =0;
	memset(usersumtemp,0x00,2);
	convert();
	SPI_Flash_Read(usersumtemp, FLASH_SIZE - 304 ,1);
	usersum=usersumtemp[0];
	for(i=0;i<usersum;i++){
	SPI_Flash_Read(datatemp, FLASH_SIZE - 300 + readsum,8);
	convert_u82long((u8*) datatemp);
	if (UID == readkey) {
		auth_flag =1;
		break;
	}
	readsum = readsum + 8;
}
	if(auth_flag == 0){auth_fault();}
		else if (auth_flag == 1)auth_pass();
}
// void auth(void) {
// 		for(i=0;i<26;i++){
// 		valid_dat[0][i] = datatemp[i];
// 		}
//   for (j=usersum-1; j >= -1; j--) {
//     for (i = 0; i <= 25; i++) {
//       if (valid_dat[0][i] != dat[i]){
// 				auth_faultflag = 1;
//         break;}
//       else if(valid_dat[j][25]==dat[25])
//         auth_faultflag = 0;
//     }
//     if (auth_faultflag == 0) {
//       auth_pass();
// 			 break;//验证成功
//     } else if (j == -1 || auth_faultflag == 1)
//       auth_fault(); //验证失败
// 			break;
//   }
// }

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
