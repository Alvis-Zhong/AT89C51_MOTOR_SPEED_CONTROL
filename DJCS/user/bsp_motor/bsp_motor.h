#ifndef __BSP_MOTO_H
#define __BSP_MOTO_H

#include <reg51.h>

#define uint unsigned int 
#define uchar unsigned char
	
/*	P1�����ڰ����Ŀ���	*/	
#define KEY P1

/*	����������	*/
uchar key_check();
uchar status_deal(uchar temp);
void pwm_control(uchar number);
void key_con();

#endif
