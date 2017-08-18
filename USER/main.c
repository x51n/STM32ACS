#include <include.h>
//#include "sys.h"


u8 wav_header[64] = {0X52,0X49,0X46,0X46,0XD4,0X86,0X01,0X00,0X57,0X41,0X56,0X45,0X66,0X6D,0X74,0X20,0X10,0X00,0X00,0X00,0X01,0X00,0X01,0X00,0X40,0X1F,0X00,0X00,0X80,0X3E,0X00,0X00,0X02,0X00,0X10,0X00,0X64,0X61,0X74,0X61,0XA0,0X86,0X01,0X00};//WAVÎÄ¼þÍ·
u8 datatemp[8];  //  韦根协议读取缓存
u8 buffer[2048];/*网络传输缓存*/
u8 recbuf[512] ={0};   //录音缓存
u8 plybuf[4096] ={0};
u8 PCM_flag = 0;       //读取录音片段结束
u8 TEXT_Buffer[8];

extern int r_done;  //读取成功标志
extern uint8 txsize[];
extern uint8 rxsize[];
extern uint8 pc_ip[];/*配置服务器的IP地址*/
extern uint16 pc_port;
extern uint16 len;
extern u8 dat[26];
extern long ID[];
extern u8 usersum;
extern u8 testID[];
extern u8 usersumtemp[];
//u16 usersize = 300;

void send_wav_header(void);       //写入wav头文件
u8 VS_Send_MusicData(u8* buf);

u16 SIZE; 
#define slen sizeof(recbuf)
#define rlen sizeof(plybuf)
	
   const     long FLASH_SIZE=2*1024*1024;


int main(void)
{
        u8 key;
        u16 i=0;
        u16 z;
       // u32 FLASH_SIZE;

//////////////////////////////////////////////////////////////////////////////
//系统初始化------- start
//////////////////////////////////////////////////////////////////////////////
        delay_init();  //延时函数初始化
        uart_init(9600); //串口初始化为9600
        LED_Init();   //初始化与LED连接的硬件接口
        KEY_Init(); //按键初始化
        dor_int();
        IDS_Init();
        WG_int();
        //iinchip_init();
        EXTIX_Init(); //外部中断初始化
        SPI_Flash_Init(); //SPI FLASH 初始化
        //												VS_HD_Reset();
        //											VS_Soft_Reset();
        Reset_W5500();
        WIZ_Init();
        printf("system read\r\n");
        set_net();
        socket0_int_UDP();
        socket1_int_TCP_S();
//////////////////////////////////////////////////////////////////
//        system int end
//////////////////////////////////////////////////////////////////


//	while(SPI_Flash_ReadID()!=W25Q16)							//检测不到W25Q64
//	{
//		LCD_ShowString(60,150,200,16,16,"25Q64 Check Failed!");
//		delay_ms(500);
//		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
//		delay_ms(500);
//	//	LED0=!LED0;//DS0闪烁
//	}
//	LCD_ShowString(60,150,200,16,16,"25Q64 Ready!");

       // FLASH_SIZE=2*1024*1024; //FLASH 大小为8M字节
////	while(1)
////	{
////		key=KEY_Scan(0);
////		if(key==WKUP_PRES)	//WK_UP 按下,写入W25Q64
////		{
////			LCD_Fill(0,170,239,319,WHITE);//清除半屏
////      LCD_ShowString(60,170,200,16,16,"Start Write W25Q64....");
////			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//从倒数第100个地址处开始,写入SIZE长度的数据
////			LCD_ShowString(60,170,200,16,16,"W25Q64 Write Finished!");	//提示传送完成
////		}
////		if(key==KEY0_PRES)	//KEY0 按下,读取字符串并显示
////		{
////      LCD_ShowString(60,170,200,16,16,"Start Read W25Q64.... ");
////			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//从倒数第100个地址处开始,读出SIZE个字节
////			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");	//提示传送完成
////			LCD_ShowString(60,190,200,16,16,datatemp);					//显示读到的字符串
////		}
////		i++;
////		delay_ms(10);
////		if(i==20)
////		{
////	//		LED0 =! LED0;//提示系统正在运行
////			i=0;
////		}
////	}

        //韦根读卡程序
////	while(1)
////	{

////	}
 //       while(1)        //TCP Client
 //       {

//  RCC_Configuration(); /* 配置单片机系统时钟*/
//  GPIO_Configuration();/* 配置GPIO*/
//  NVIC_Configuration();/* 配置嵌套中断向量*/

//  Systick_Init(72);/* 初始化Systick工作时钟*/
//  USART1_Init(); /*初始化串口通信:115200@8-n-1*/
//  at24c16_init();/*初始化eeprom*/

                //Init. TX & RX Memory size of w5500

//  while(1)
//  {
//		uint16 len=0;
// switch(getSn_SR(1))/*获取socket0的状态*/
//       {
//         case SOCK_INIT:/*socket初始化完成*/
//           listen(1);/*在TCP模式下向服务器发送连接请求*/
//
//           break;
//         case SOCK_ESTABLISHED:/*socket连接建立*/
//           if(getSn_IR(1) & Sn_IR_CON)
//           {
//              setSn_IR(1, Sn_IR_CON);/*Sn_IR的第0位置1*/
//            }
//           len=getSn_RX_RSR(1);/*len为已接收数据的大小*/
//           if(len>0)
//           {
//		      //t=IINCHIP_READ(Sn_SR(0));
//			  memset(buffer,0x00,len+1);  //清零数组
//             // printf("0x%d\r\n",t);
//              recv(1,buffer,len);/*W5200接收来自Sever的数据*/
//			  printf("%s\r\n",buffer);
//              send(1,buffer,len);/*W5200向Server发送数据*/
//            }
//           break;
//         case SOCK_CLOSE_WAIT:/*socket等待关闭状态*/
//           break;
//         case SOCK_CLOSED:/*socket关闭*/
//           socket(1,Sn_MR_TCP,port,Sn_MR_ND);/*打开socket0的一个端口*/
//           break;
//				 case SOCK_UDP:
//					 socket(1,Sn_MR_TCP,port,Sn_MR_ND);
//				   break;
//      }//  }
//	}

///////////////////////////////////////////////////////
//
//对讲
////////
                while(1)
                {
                        u8 key;
                        key=KEY_Scan(1);
                        while(SPI_Flash_ReadID()!=W25Q16)
                        {
                                printf("25Q64 Check Failed!");
                                delay_ms(500);
                                printf("Please Check!      ");
                                delay_ms(500);
                                LED0=!LED0;
                        }

                        if (r_done & 1) {
                                r_done = 0;
                                if(dat_check()) {
                                        u8 u;
                                        for(u=0; u<26; u++)
                                        {printf("%d",dat[u]);}
                                        printf("\r\n");
                                        for(u=0; u<26; u++)
                                        {datatemp[u]=dat[u];}
                                        for(u=0; u<26; u++)
                                        {printf("%d",datatemp[u]);}
                                        printf("\r\n");
                                       // SPI_Flash_Write((u8*)datatemp, FLASH_SIZE - 100,26);
                                        //		SPI_Flash_Read(datatemp, FLASH_SIZE - 100,26);
                                        //		printf("Start Read W25X16...\r\n");
                                        //SPI_Flash_Read(datatemp, FLASH_SIZE - 100,26);
																				//SPI_Flash_Read(datatemp, FLASH_SIZE - 300,6);
                                        for(u=0; u<26; u++)
                                        {printf("%d",datatemp[u]);}
																				printf("\r\n");
                                        auth();
                                }
                        }

                        if(key == 1 ) //按键按下讲话
                        {
/*speak:*///		LCD_ShowString(60,130,"Speaking ");
//			printf("Speaking\r\n");

                                //							VS_HD_Reset();
//											VS_Soft_Reset();
                                VS_Init();
                                recoder_enter_rec_mode(2048);
                                delay_ms(1);
                                //sendto(0,wav_header,64, pc_ip, pc_port);
                                LED0 = 0;
                                printf("Speaking\r\n");
//													GPIO_ResetBits(GPIOD,GPIO_Pin_2);
                                while(key != 0 ) //只要按键没放开
                                {
                                        key=KEY_Scan(1);
                                        read_pcm();
                                        if(PCM_flag==1) //一次读取成功，可以发送
                                        {
                                                sendto(0,recbuf,512, pc_ip, pc_port);
                                                printf("%s",recbuf);
                                                PCM_flag = 0;
                                        }
                                }
                                LED0 = 1;
//												VS_HD_Reset();
//												VS_Soft_Reset();
                                delay_ms(100);
                                //															GPIO_SetBits(GPIOD,GPIO_Pin_2);
                        }
                        //////////////////////////////////////////////
                        ///
                        ///        如果有语音数据
                        ///
                        /////////////////////////////////////////////
                        if(getSn_IR(0) & Sn_IR_RECV)
                        {
                                setSn_IR(0, Sn_IR_RECV);/*Sn_IR的第0位置1*/
                                VS_Init();
                                VS_HD_Reset();
                                VS_Soft_Reset();
                                SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
//												set210XX();
                                send_wav_header();
                                printf("Listening\r\n");

                                while((len=getSn_RX_RSR(0))>0)
                                {
                                        memset(plybuf,0x00,len+1); //清零数组
                                        recvfrom(0,plybuf,len, pc_ip,&pc_port);/*W5200接收计算机发送来的数据*/
                                        //todo
                                        //vs1053播放
                                        //							     sendto(0,plybuf,rlen, pc_ip, pc_port);
                                        z=0;
                                        do
                                        {
                                                u8 n;
                                                if(VS_DQ!=0) //
                                                {
                                                        VS_XDCS=0;
                                                        for(n=0; n<32; n++)
                                                        {
                                                                VS_SPI_ReadWriteByte(plybuf[z++]);
                                                        }
                                                        VS_XDCS=1;
                                                }
                                                //				printf("%d\r\n",z);
                                        }
                                        while((z<4096));

                                        sendto(0,plybuf,len, pc_ip, pc_port);
                                        printf("%s\r\n",plybuf);
                                }
                        }
                        //////////////////////////////////////////////
                        /////
                        /////            TCP 接收模式
                        /////
                        //////////////////////////////////////////////
                        if(getSn_IR(1) & Sn_IR_RECV)
                        {
                                setSn_IR(1, Sn_IR_CON);
                                len=getSn_RX_RSR(1);
                                if(len>0)
                                {
                                        //t=IINCHIP_READ(Sn_SR(0));
                                        memset(buffer,0x00,2048);
                                        // printf("0x%d\r\n",t);
                                        recv(1,buffer,len);
                                        printf("%s\r\n",buffer);
																			//	con_tcp_s();
																	      SIZE = sizeof(buffer);
                                        
																	usersum=0;
																	for(i=0;i<SIZE;i++)
																	{
																		if(buffer[i]==0x0a)usersum++;
																		else if(buffer[i]==0x00){usersumtemp[0]=usersum;break;}
																	}
																	SPI_Flash_Write((u8*)buffer, FLASH_SIZE - 300,usersum * 8);
																	SPI_Flash_Write((u8*) usersumtemp, FLASH_SIZE - 304,1);
                                        //		SPI_Flash_Read(datatemp, FLASH_SIZE - 100,26);
                                        //		printf("Start Read W25X16...\r\n");
                                        SPI_Flash_Read(datatemp, FLASH_SIZE - 300,6);
                                        printf("%s\n", datatemp);
                                        send(1,buffer,len);
//	          send(0,str1,100);
                                }
                        }
                        //todo
                        //进入播放模式

//												sendto(0,recbuf,512, pc_ip, pc_port);

												if(getSn_SR(1) == 0x1C   )    //如果不是监听状态，便重新初始化
													{
//														if(getSn_SR(1) ^ 0x17)
														{socket1_int_TCP_S();}
													}
                }
//			}
//		}
//                }
        }

//写入wav头文件
void send_wav_header(void)
{
        u8 i = 0,n = 0;
        do
        {
                if((VS_DQ!=0))
                {
                        VS_XDCS=0;
                        for(n=0; n<32; n++)
                        {
                                SPI1_ReadWriteByte(wav_header[i++]);
                        }
                        VS_XDCS=1;
                }
        }
        while(i<63);
}
