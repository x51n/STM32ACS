#include "userkeys.h"

//定义一个二维数组，将二维数组在auth中传递给一维数组，并且循环对比
//extern u8 datatemp;

u8 usersum; //用户总数
long testkey1 = 0x57fc1d;
extern u8 firstbit, lastbit;
long UID=0;
extern u8 dat[26];
extern u8 buffer[];
extern u16 len;
long ID[3];
long readkey;	
extern u8 datatemp[];
u8 testID[4];


//int valid_dat[1][26];
// int userkey; //合法用户身份信息
//int valid_dat[2][26]={{1}};
//u8 valid_dat[1][26];
/*={
		1,0,1,0,1,0,1,1,
		1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,0,
		1,1};	*/

/*void init_valid_dat(void) {
	//int valid_dat[usersum][26];
		int i;
		for(i=0;i<26;i++){
		valid_dat[1][i] = datatemp[i];
		}
}*/

void convert(void) {
	int i;
	UID = 0;
//  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  for (i = 0; i < 26; i++) {
    if (i == 0) {
      if (dat[i] == 1) {
        firstbit = 1;
      } else {
        firstbit = 0;
      }
    } else if (i < 25 && i > 0) {
      if (dat[i] == 1) {
        UID <<= 1;
        UID |= 1;
      } else {
        UID <<= 1;
      }
    } else if (i == 25) {
      if (dat[i] == 1) {
        lastbit = 1;
      } else {
        lastbit = 0;
      }
    }
  }
	printf("%x\n", UID);
}

int con_tcp_s(void)
{
	int i=0;
	int t=0;
	memset(ID,0,len); //清零数组
				 for ( i = 0; i < len; i++) {
							 switch (test(buffer[i])) {
							 case 3:
											 t++;
											 break;
							 case 1:
											 ID[t]<<=4;
											 ID[t]|=buffer[i]-0x30;
											 break;
							 case 2:
											 ID[t]<<=4;
											 ID[t]|=buffer[i]-0x57;
											 break;
							 }
			 }
			 for ( i = 0; i < t; i++) {
							 printf("%x\n", ID[i]);
			 }
			 usersum =t;
 }

int test (int i){
        if (i<=57 && i >=48) {
                return 1;
        }
        else if (i<=102 && i>=97) {
                return 2;
        }
				else if (i<=70 && i>=65) {
								return 2;
        }
        else if (i == 0x0a) {
                return 3;
        }
return 0;
}

u8 convert_long2u8(long id)
{ long temp;
	testID[0]=id&0x000000ff;
	temp=id&0x0000ff00;
	temp>>=8;
	testID[1]=temp;
	temp=id&0x00ff0000;
	temp>>=16;
	testID[2]=temp;
	temp=id&0xff000000;
	temp>>=24;
	testID[3]=temp;
}

u8 convert_u82long(u8* testid)
{
	int i=0;
	readkey=0;
	for(i= 0;i<8;i++){
		switch (test(testid[i])){
							 case 3:
											 break;
							 case 1:
											 readkey<<=4;
											 readkey|=testid[i]-0x30;
											 break;
							 case 2:
											 readkey<<=4;
											 readkey|=testid[i]-0x57;
											 break;
			
		}
			
//	readkey|=testid[3];
//	readkey<<=4;
//	readkey|=testid[2];
//	readkey<<=4;
//	readkey|=testid[1];
//	readkey<<=4;
//	readkey|=testid[0];
	}
}
