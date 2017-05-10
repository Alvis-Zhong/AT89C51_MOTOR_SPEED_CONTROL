/*******************************************************************
	************************************************************
	*
	*@file     main.c
	*@author   Bin
	*@data     2017.05
	*@brief    主函数
	*
	*************************************************************
*********************************************************************/

#include <reg51.h>

#include "stdio.h"
#include "bsp_lcd1602.h"
#include "bsp_motor.h"

sbit ENA=P2^4;						//对L298芯片使能

float sum = 0;
float speed; 

uint hex; 
uint num=0;

uchar buff[16]; 

void timerinit();					//定时器和计数器的初始化函数

int main()
{
	lcd_init(); 						//LCD初始化
	timerinit();						//定时器和计数器相关配置寄存器的初始化函数
	ENA=1;									//打开L298的使能引脚之一
	P1=0xff;								//P1口初始化
	while(1)
	{
		key_con();						//电机控制
	}
}

/*	50ms产生一次中断	*/
void timerinit()
{
	TMOD = 0x41; 						//定时器/计数器0设置为定时器模式，定时器/计数器1设置为计数器模式
	TH0=(65536-50000)/256; 	
	TL0=(65536-50000)%256; 
	TH1=0x00; 
	TL1=0x00; 
	TR0=1;
	TR1=1; 
	ET0=1; 
	EA =1;
}

/*	定时器中断函数	*/
void timer0(void) interrupt 1
{
	TH0 = (65536-50000)/256; 
	TL0 = (65536-50000)%256;
	num++ ; 
	if(num==20)																			//电机转速1s更新一次
	{
		hex=TH1*32+TL1;
		speed=(int)(hex/22.93*60); 										//速度转换函数
		sprintf(buff,"speed:%5.2f         ",speed);		//向buff中写入需要现实的字符
		display(0,1,buff);														//LCD显示
		num=0;
		TH1=0;
		TL1=0;
	}
	TF0=0;																					//关闭中断
}