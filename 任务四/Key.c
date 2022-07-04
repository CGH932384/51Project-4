#include <REGX52.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char KeyNumber1=0;
	
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNumber1=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNumber1=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber1=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber1=4;}
	
	return KeyNumber1;
}


unsigned char MatrixKey()
{
	unsigned char KeyValue=0;
	P1=0x0f; 
	if(P1!=0x0f)//读取按键是否按下
	{
		if(P1!=0x0f)//再次检测是否按下
        {
			//测试列
			P1=0x0f;
			switch(P1) 
            { case(0X07): KeyValue=1;break;
              case(0X0b): KeyValue=2;Delay(100);break; 
              case(0X0d): KeyValue=3;Delay(100);break; 
              case(0X0e): KeyValue=4;Delay(100);break;
			}
			//测试行
			P1=0XF0;
			switch(P1) 
			{ case(0X70): KeyValue=KeyValue;break; 
			  case(0Xb0): KeyValue=KeyValue+4;break; 
			  case(0Xd0): KeyValue=KeyValue+8;break;
			  case(0Xe0): KeyValue=KeyValue+12;break; 
			}
 	  } 
   }
	return KeyValue;
}

