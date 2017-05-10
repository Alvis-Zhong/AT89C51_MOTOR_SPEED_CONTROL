#ifndef __BSP_LCD1602_H
#define __BSP_LCD1602_H

#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

/*	º¯ÊıµÄÉùÃ÷	*/
void lcd_init(); 
void display(uchar x ,uchar y , uchar * str); 

#endif
