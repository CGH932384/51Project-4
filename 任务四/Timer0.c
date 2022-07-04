#include <REGX52.H>

void Timer0Init(void)   //1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		     //设置定时器模式
	TMOD |= 0x01;		
	TL0 = 0x18;	         //设置定时初值
	TH0 = 0xFC;	         //设置定时初值
	TF0 = 0;		
	TR0 = 1;		
	ET0=1;
	EA=1;
	PT0=0;
}


//函数一秒中断模板
/*
void Timer0_Routine()  interrupt 1
{
	static unsigned int T0count; 
	TH0=0xFC;
	TL0=0x66;
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;

	}
}  
*/
