#include "mode.h"
#include "string.h"

void letter(char ch);
void light(char code[]);

//------------------------------------
//设计循环读取数组中的字符，并且执行闪烁
//------------------------------------
void mode (char ch[])
{
    int i,n;
    n=strlen(ch);       //测量字符长度
    for(i=0; i<n; i++)
        letter(ch[i]);
}
//========================================
//------------------------------------------------
//定义闪亮功能
//------------------------------------------------
void light(char code[])
{
    int i,s;
    s=strlen(code);
    for(i=0; i<s; i++)
    {
        switch (code[i])
        {
        case '0':
            LED0=0;
            LED1=1;
            delay_ms(200);
            LED0=1;
            LED1=1;
            delay_ms(100);
            break;
        case '1':
            LED0=0;
            LED1=0;
            delay_ms(200);
            LED0=1;
            LED1=1;
            delay_ms(100);
            break;
        default:
            break;
        }
    }
    LED0=1;
    LED1=1;
    delay_ms(300);
}
//================================================
//------------------------------------------------
//定义字符的莫斯电码编号
//------------------------------------------------
void letter(char ch)
{
    switch (ch)
    {
    case '1':
        light("01111");
        break;
    case '2':
        light("00111");
        break;
    case '3':
        light("00011");
        break;
    case '4':
        light("00001");
        break;
    case '5':
        light("00000");
        break;
    case '6':
        light("1000");
        break;
    case '7':
        light("11000");
        break;
    case '8':
        light("11100");
        break;
    case '9':
        light("11110");
        break;
    case '0':
        light("11111");
        break;
    case 'a':
		case 'A':
        light("01");
        break;
    case 'b':
    case 'B':
        light("1000");
        break;
    case 'c':
	  case 'C':
        light("1010");
        break;
    case 'd':
    case 'D':
        light("100");
        break;
    case 'e':
		case 'E':
        light("0");
        break;
    case 'f':
		case 'F':
        light("0010");
        break;
    case 'g':
		case 'G':
        light("110");
        break;
    case 'h':
		case 'H':
        light("0000");
        break;
    case 'i':
		case 'I':
        light("00");
        break;
    case 'j':
		case 'J':
        light("0111");
        break;
    case 'k':
		case 'K':
        light("101");
        break;
    case 'l':
		case 'L':
        light("0100");
        break;
    case 'm':
		case 'M':
        light("11");
        break;
    case 'n':
		case 'N':
        light("10");
        break;
    case 'o':
		case 'O':
        light("111");
        break;
    case 'p':
		case 'P':
        light("0110");
        break;
    case 'q':
		case 'Q':
        light("1101");
        break;
    case 'r':
		case 'R':
        light("010");
        break;
    case 's':
		case 'S':
        light("000");
        break;
    case 't':
		case 'T':
        light("1");
        break;
    case 'u':
		case 'U':
        light("001");
        break;
    case 'v':
		case 'V':
        light("0001");
        break;
    case 'w':
		case 'W':
        light("011");
        break;
    case 'x':
		case 'X':
        light("1001");
        break;
    case 'y':
		case 'Y':
        light("1011");
        break;
    case 'z':
		case 'Z':
        light("1100");
        break;
    default:
        break;
    }
}

