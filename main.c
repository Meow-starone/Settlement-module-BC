#include "led.h"
#include "Buzzer.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "LCD_ZK.h"
#include "ds18b20.h"  
#include<stdio.h>
#include "adc.h"
#include "ultrasonic.h"	
#include "time.h"
#include "dht11.h"
#include "timer.h"
#include "stmflash.h" 
#include "MP3TF16P.h"
#include "rtc.h" 
#include "usart2.h"
#include "AS608.h"
#include "timer.h"
#include "rc522.h"
#include "rc522_add.h"
#include "wifi.h"

unsigned char sanzhongmimaOK=0;
extern  u8 keycode;
//extern  u8 step;
//extern	u8 len;	
//extern	u16 adcx;	 
//extern	float temp;
//extern	short temperature; 
u32  number=0;
extern void TIM3_Int_Init(u16 arr,u16 psc);
extern  u8 str[40];
extern unsigned char keycode;
//要写入到STM32 FLASH的字符串数组
#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改

//刷指纹
unsigned int zwnumber=0;
#define FLASH_SAVE_ADDR  0X08009000 	//设置FLASH
extern unsigned char step;
void System_Init()
{
	delay_init();	    	 //延时函数初始化	 
	Adc_Init();		  		//ADC初始化	  		//ADC初始化	
	initial_lcd();
  clear_screen();
	TIM3_Int_Init(9,7199);//1Khz的计数频率，计数到10为10ms  
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化为9600
	usart2_init(usart2_baund);//初始化串口2,用于与指纹模块通讯
	
	RTC_Init();	  			//RTC初始化
//	LED_Init();		  	 //初始化与LED连接的硬件接口 
	Buzzer_Init();
	KEY_Init();		
	clear_screen();
	clear_screen();
	display_GB2312_string(0,40,"请刷卡");	
	InitAlldata();			//初始化所有读卡相关数据的设置
	InitRc522();	
	Buzzer=1;
}
unsigned char key=0;
unsigned int zongjia=0,yue_yuan=2000;
unsigned char strsta[5]={0,0,0,0,0};
 int main(void)
 {	
	System_Init();
	Show_Init();
	while(1)
	{
		if(flag_com==0)//如果没有读到卡就一直在扫卡
		{
			Read_cardID();//读卡号
			
		}	
		if(flag_com==1)//如果没有读到卡就一直在扫卡
		{
			flag_com=0;
			
			Uart1Sends(cardID);
			if(cardID[0]==0x13&&cardID[1]==0xBA&&cardID[2]==0x97&&cardID[3]==0x21&&strsta[0]==0)
			{
				clear_screen();
				strsta[0]=1;strsta[3]=0;
				zongjia=zongjia+96;
				display_GB2312_string(0,0,"物品：晨宇    ");	
				display_GB2312_string(2,0,"单价：96元/斤");			
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"总价:   元");	
				display_GB2312_string(4,40,str);	
				Buzzer=0;
				delay_ms(200);
				Buzzer=1;
			}
			
			if(cardID[0]==0x13&&cardID[1]==0x77&&cardID[2]==0xDD&&cardID[3]==0x21&&strsta[1]==0)
			{
				clear_screen();
				strsta[1]=1;strsta[3]=0;
				zongjia=zongjia+28;
				display_GB2312_string(0,0,"物品：牛奶     ");	
				display_GB2312_string(2,0,"单价：28元/箱");		
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"总价:   元");	
				display_GB2312_string(4,40,str);	
				Buzzer=0;
				delay_ms(200);
				Buzzer=1;				
			}
			if(cardID[0]==0x13&&cardID[1]==0x68&&cardID[2]==0x0E&&cardID[3]==0x21&&strsta[2]==0)
			{
				clear_screen();
				strsta[2]=1;strsta[3]=0;
				zongjia=zongjia+79;
				display_GB2312_string(0,0,"物品：核桃     ");	
				display_GB2312_string(2,0,"单价：79元/箱");		
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"总价:   元");	
				display_GB2312_string(4,40,str);
				Buzzer=0;
				delay_ms(200);
				Buzzer=1;				
			}			
			
			if(cardID[0]==0x5D&&cardID[1]==0xE5&&cardID[2]==0x63&&cardID[3]==0xA9&&strsta[3]==0)
			{
				strsta[3]=1;
				clear_screen();
				strsta[0]=0;strsta[1]=0;strsta[2]=0;
				display_GB2312_string(0,0,"    欢迎光临    ");	
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"应付:   元");	
				display_GB2312_string(4,40,str);	
				

				if(2000>zongjia)
				yue_yuan=yue_yuan-zongjia;
				str[0] = yue_yuan % 10000/1000+ 0x30; 
				str[1] = yue_yuan % 1000/100+ 0x30; 
				str[2] = yue_yuan % 100/10+ 0x30;
				str[3] = yue_yuan % 10+ 0x30; 
				str[4] = '\0';
				display_GB2312_string(6,0,"余额:   元");	
				display_GB2312_string(6,40,str);
				zongjia=0;
				Buzzer=0;
				delay_ms(1000);
				Buzzer=1;
				
		
			}
		}			
	}
}
