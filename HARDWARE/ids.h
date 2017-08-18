#include "sys.h"

#define ids_on	1		//红外传感器检测到信号

//红外线端口定义
#define ids  PCin(4)  	//PC4


void IDS_Init(void);		//IO初始化
u8 IDS_Scan(void);		     //红外传感器扫描函数
void IDS_Alarm(void);				//红外报警服务函数
