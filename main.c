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
//Ҫд�뵽STM32 FLASH���ַ�������
#define usart2_baund  57600//����2�����ʣ�����ָ��ģ�鲨���ʸ���

//ˢָ��
unsigned int zwnumber=0;
#define FLASH_SAVE_ADDR  0X08009000 	//����FLASH
extern unsigned char step;
void System_Init()
{
	delay_init();	    	 //��ʱ������ʼ��	 
	Adc_Init();		  		//ADC��ʼ��	  		//ADC��ʼ��	
	initial_lcd();
  clear_screen();
	TIM3_Int_Init(9,7199);//1Khz�ļ���Ƶ�ʣ�������10Ϊ10ms  
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	usart2_init(usart2_baund);//��ʼ������2,������ָ��ģ��ͨѶ
	
	RTC_Init();	  			//RTC��ʼ��
//	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	Buzzer_Init();
	KEY_Init();		
	clear_screen();
	clear_screen();
	display_GB2312_string(0,40,"��ˢ��");	
	InitAlldata();			//��ʼ�����ж���������ݵ�����
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
		if(flag_com==0)//���û�ж�������һֱ��ɨ��
		{
			Read_cardID();//������
			
		}	
		if(flag_com==1)//���û�ж�������һֱ��ɨ��
		{
			flag_com=0;
			
			Uart1Sends(cardID);
			if(cardID[0]==0x13&&cardID[1]==0xBA&&cardID[2]==0x97&&cardID[3]==0x21&&strsta[0]==0)
			{
				clear_screen();
				strsta[0]=1;strsta[3]=0;
				zongjia=zongjia+96;
				display_GB2312_string(0,0,"��Ʒ������    ");	
				display_GB2312_string(2,0,"���ۣ�96Ԫ/��");			
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"�ܼ�:   Ԫ");	
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
				display_GB2312_string(0,0,"��Ʒ��ţ��     ");	
				display_GB2312_string(2,0,"���ۣ�28Ԫ/��");		
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"�ܼ�:   Ԫ");	
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
				display_GB2312_string(0,0,"��Ʒ������     ");	
				display_GB2312_string(2,0,"���ۣ�79Ԫ/��");		
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"�ܼ�:   Ԫ");	
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
				display_GB2312_string(0,0,"    ��ӭ����    ");	
				str[0] = zongjia% 1000/100+ 0x30; 
				str[1] = zongjia % 100/10+ 0x30;
				str[2] = zongjia % 10+ 0x30; 
				str[3] = '\0';
				display_GB2312_string(4,0,"Ӧ��:   Ԫ");	
				display_GB2312_string(4,40,str);	
				

				if(2000>zongjia)
				yue_yuan=yue_yuan-zongjia;
				str[0] = yue_yuan % 10000/1000+ 0x30; 
				str[1] = yue_yuan % 1000/100+ 0x30; 
				str[2] = yue_yuan % 100/10+ 0x30;
				str[3] = yue_yuan % 10+ 0x30; 
				str[4] = '\0';
				display_GB2312_string(6,0,"���:   Ԫ");	
				display_GB2312_string(6,40,str);
				zongjia=0;
				Buzzer=0;
				delay_ms(1000);
				Buzzer=1;
				
		
			}
		}			
	}
}
