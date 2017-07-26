#include <include.h>

uint8 pc_ip[4]={192,168,1,101};/*配置服务器的IP地址*/
uint16 pc_port=8000;
uint16 len=0;

uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*定义Mac变量*/
uint8 lip[4]={192,168,1,110};/*定义lp变量*/
uint8 sub[4]={255,255,255,0};/*定义subnet变量*/
uint8 gw[4]={192,168,1,1};/*定义gateway变量*/
uint8 ip[4];
u16 L_UPD_port=6000;
u16 L_TCP_port=7000;
extern uint8 txsize[];
extern uint8 rxsize[];
extern uint8 buffer[];

void WIZ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  // Port C output
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC, GPIO_Pin_12);

  // Port B output;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_9);

  // Port C input
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  SPI3_Init();
}

void set_net(void) {
	/* code */

Reset_W5500();/*硬重启W5500*/
setSHAR(mac);/*配置Mac地址*/
  setSUBR(sub);/*配置子网掩码*/
  setGAR(gw);/*配置默认网关*/
  setSIPR(lip);/*配置Ip地址*/

    //Init. TX & RX Memory size of w5500
  sysinit(txsize, rxsize); /*初始化8个socket*/

  setRTR(2000);/*设置溢出时间值*/
  setRCR(3);/*设置最大重新发送次数*/

  getSIPR (ip);
  printf("IP : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  getSUBR(ip);
  printf("SN : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  getGAR(ip);
  printf("GW : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  printf("Network is ready.\r\n");

}

void socket0_int_UDP(void) {


///*	switch(getSn_SR(0))/*获取socket 0的状态*/
//      {
//         case SOCK_UDP:/*socket 的套接字初始化完成*/
//           delay_ms(1);
//           if(getSn_IR(0) & Sn_IR_RECV)
//          {
//            setSn_IR(0, Sn_IR_RECV);/*Sn_IR的第0位置1*/
//          }
//           if((len=getSn_RX_RSR(0))>0)
//           {
//						  printf("%s\r\n",buffer);
//              recvfrom(0,buffer, len, pc_ip,&pc_port);/*W5200接收计算机发送来的数据*/
//			        printf("%s\r\n",buffer);//
//              sendto(0,buffer,len, pc_ip, pc_port);/*W5200把接收到的数据发送给计算机*/
//              memset(buffer,0x00,len+1);  //清零数组

//            }
//           break;
//         case SOCK_CLOSED:/*socket 关闭*/
//           socket(0,Sn_MR_UDP,L_UPD_port,0);/*初始化socket 0的套接字*/
//           break;
//       }
u8 state = getSn_SR(0);
while (state ^ SOCK_UDP ) {
	if (state==SOCK_CLOSED) {
		socket(0,Sn_MR_UDP,L_UPD_port,0);
		state = getSn_SR(0);
	}
}
printf("UDP port is %d\r\n",L_UPD_port);
}

void socket1_int_TCP_S(void) {
	/* code */
	uint16 len=0;
	socket(1,Sn_MR_TCP,L_TCP_port,Sn_MR_ND);/*打开socket0的一个端口*/
	listen(1);/*在TCP模式下向服务器发送连接请求*/

// switch(getSn_SR(1))/*获取socket0的状态*/
//       {
//         case SOCK_INIT:/*socket初始化完成*/
//           listen(1);/*在TCP模式下向服务器发送连接请求*/
//           break;
//         case SOCK_ESTABLISHED:/*socket连接建立*/
//           if(getSn_IR(1) & Sn_IR_CON)
//           {
//              setSn_IR(1, Sn_IR_CON);/*Sn_IR的第0位置1*/
//            }
//           len=getSn_RX_RSR(1);/*len为已接收数据的大小*/
//           if(len>0)
//           {
//			  memset(buffer,0x00,len+1);  //清零数组
//              recv(1,buffer,len);/*W5200接收来自Sever的数据*/
//			  printf("%s\r\n",buffer);
//              send(1,buffer,len);/*W5200向Server发送数据*/
//            }
//           break;
//         case SOCK_CLOSE_WAIT:/*socket等待关闭状态*/
//           break;
//         case SOCK_CLOSED:/*socket关闭*/
//           socket(1,Sn_MR_TCP,L_TCP_port,Sn_MR_ND);/*打开socket0的一个端口*/
//           break;
//      }
printf("TCP port is %d\r\n",L_TCP_port);
			}

void WIZ_CS(uint8_t val)
{
	if (val == LOW) {
   		GPIO_ResetBits(GPIOC, WIZ_SCS);
	}else if (val == HIGH){
   		GPIO_SetBits(GPIOC, WIZ_SCS);
	}
}

uint8_t SPI3_SendByte(uint8_t byte)
{
	  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);

	  SPI_I2S_SendData(SPI3, byte);

	  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);

	  return SPI_I2S_ReceiveData(SPI3);
}
