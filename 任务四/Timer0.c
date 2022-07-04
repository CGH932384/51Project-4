#include <REGX52.H>

void Timer0Init(void)   //1����@11.0592MHz
{
	TMOD &= 0xF0;		     //���ö�ʱ��ģʽ
	TMOD |= 0x01;		
	TL0 = 0x18;	         //���ö�ʱ��ֵ
	TH0 = 0xFC;	         //���ö�ʱ��ֵ
	TF0 = 0;		
	TR0 = 1;		
	ET0=1;
	EA=1;
	PT0=0;
}


//����һ���ж�ģ��
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
