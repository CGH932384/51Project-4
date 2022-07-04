#include <REGX52.H>
#include "Delay.h"
#include "I2C.h"
#include "AT24C02.h"
#include "timer0.h"
#include "LCD1602.h"
#include "key.h"

unsigned char min,sec,minsec;
unsigned char keynum,Runflag;
unsigned char timeSetSelect,timeSetFlashFlag,Value;
char time[7]={1,1,1,1,0,0,0};


void LCD_Show()
{
	LCD_ShowNum(1,1,time[0],2);
	LCD_ShowString(1,3,"-");
	LCD_ShowNum(1,4,time[1],2);
	LCD_ShowString(1,6,"-");
	LCD_ShowNum(1,7,time[2],2);
	LCD_ShowNum(2,1,time[3],2);
	LCD_ShowString(2,3,":");
	LCD_ShowNum(2,4,time[4],2);
	LCD_ShowString(2,6,":");
	LCD_ShowNum(2,7,time[5],2);	

}

void LCD_SetTime()
{

	if(Value==2)
	{
		timeSetSelect++;
		timeSetSelect%=6;
	}
	if(Value==3)
	{
		time[timeSetSelect]++;
		switch(timeSetSelect)
		{
			case 0:if(time[0]>99){time[0]=0;}break;
			case 1:if(time[1]>12){time[1]=1;time[0]++;}break;
			case 2:	switch(time[1])
					{
						case 1:if(time[2]>31){time[2]=1;time[1]++;}break;			
						case 3:if(time[2]>31){time[2]=1;time[1]++;}break;			
						case 5:if(time[2]>31){time[2]=1;time[1]++;}break;
						case 7:if(time[2]>31){time[2]=1;time[1]++;}break;
						case 8:if(time[2]>31){time[2]=1;time[1]++;}break;
						case 10:if(time[2]>31){time[2]=1;time[1]++;}break;
						case 12:if(time[2]>31){time[2]=1;time[1]=1;}break;
						case 4:if(time[2]>30){time[2]=1;time[1]++;}break;
						case 6:if(time[2]>30){time[2]=1;time[1]++;}break;
						case 9:if(time[2]>30){time[2]=1;time[1]++;}break;
						case 11:if(time[2]>30){time[2]=1;time[1]++;}break;
						case 2:	if(time[0]%4==0)
								{
									if(time[2]>29){time[2]=1;time[1]++;}
								}
								else
								{
									if(time[2]>28){time[2]=1;time[1]++;}
								}break;
					}break;
			case 3:if(time[3]==24){time[3]=0;time[2]++;}break;
			case 4:if(time[4]>59)
				   {
						time[4]=0;
						time[3]++;
						if(time[3]==24){time[3]=0;time[2]++;}
				   }break;
			case 5:if(time[5]>59)
					{
						time[5]=0;
						time[4]++;
						if(time[4]==60)
						{time[4]=0;time[3]++;if(time[3]==24){time[3]=0;time[2]++;}}
					}break;
		}		
	}
	if(Value==4)
	{
		time[timeSetSelect]--;
		switch(timeSetSelect)
		{
			case 0:if(time[0]<0){time[0]=99;}break;
			case 1:if(time[1]==0){time[1]=12;time[0]--;}break;
			case 2:switch(time[1])
				   {
					   case 0:time[1]=12;break;
				       case 1:{
								if(time[2]==0){time[2]=31;time[1]=12;}
								if(time[2]>31){time[2]=1;time[1]++;}
							  }break;
					   case 2:{
								if(time[1]%4==0)
								{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>29){time[2]=1;time[1]++;}													
								}
								else
								{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>28){time[2]=1;time[1]++;}
								}												
							   }break;
						case 3:{
									if(time[1]%4==0)
								    {
										if(time[2]<1){time[2]=29;time[1]--;}
										if(time[2]>31){time[2]=1;time[1]++;}
									}
									else
									{
										if(time[2]<1){time[2]=28;time[1]--;}
										if(time[2]>31){time[2]=1;time[1]++;}
									}
								}break;
							 
					    case 5:{
									if(time[2]<1){time[2]=30;time[1]--;}
									if(time[2]>31){time[2]=1;time[1]++;}
							   }break;
						case 7:{
									if(time[2]<1){time[2]=30;time[1]--;}
									if(time[2]>31){time[2]=1;time[1]++;}
								}break;
					    case 8:{
									if(time[2]<1){time[2]=30;time[1]--;}
									if(time[2]>31){time[2]=1;time[1]++;}
							   }break;
						case 10:{
									if(time[2]<1){time[2]=30;time[1]--;}
									if(time[2]>31){time[2]=1;time[1]++;}
								}break;
						case 12:{
									if(time[2]<1){time[2]=30;time[1]--;}
									if(time[2]>31){time[2]=1;time[1]++;}
								}break;
						case 4:{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>30){time[2]=1;time[1]++;}
								}break;
						case 6:{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>30){time[2]=1;time[1]++;}
								}break;
						case 9:{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>30){time[2]=1;time[1]++;}
							   }break;
						case 11:{
									if(time[2]<1){time[2]=31;time[1]--;}
									if(time[2]>30){time[2]=1;time[1]++;}
								}break;
							 
					} break;
		   case 3:if(time[3]<0){time[3]=23;time[2]--;}break;
		   case 4:if(time[4]<0){time[4]=59;time[3]--;}break;
		   case 5:if(time[5]<0){time[5]=59;time[4]--;}break;
		}		
	}

	if(timeSetSelect==0 && timeSetFlashFlag==1)
	{
		LCD_ShowString(1,1,"  ");
	}
	else 
	{
		LCD_ShowNum(1,1,time[0],2);
	}
	if(timeSetSelect==1 && timeSetFlashFlag==1)
	{
		LCD_ShowString(1,4,"  ");
	}
	else
	{
		LCD_ShowNum(1,4,time[1],2);
	}
	if(timeSetSelect==2 && timeSetFlashFlag==1)
	{
		LCD_ShowString(1,7,"  ");
	}
	else
	{
		LCD_ShowNum(1,7,time[2],2);
	}
	if(timeSetSelect==3 && timeSetFlashFlag==1)
	{	
		LCD_ShowString(2,1,"  ");
	}
	else
	{
		LCD_ShowNum(2,1,time[3],2);
	}
	if(timeSetSelect==4 && timeSetFlashFlag==1)
	{
		LCD_ShowString(2,4,"  ");
	}
	else 
	{
		LCD_ShowNum(2,4,time[4],2);
	}
	if(timeSetSelect==5 && timeSetFlashFlag==1)
	{
		LCD_ShowString(2,7,"  ");
	}
	else 
	{
		LCD_ShowNum(2,7,time[5],2);
	}
}


int  main()
{
	void timer0Init();
	unsigned char key();
	unsigned char MatrixKey();
	LCD_Init();
	timer0Init();
	time[0]=AT24C02_ReadByte(0);
	time[1]=AT24C02_ReadByte(1);
	time[2]=AT24C02_ReadByte(2);
	time[3]=AT24C02_ReadByte(3);
	time[4]=AT24C02_ReadByte(4);
	time[5]=AT24C02_ReadByte(5);		
	Runflag=1;
	while(1)
	{
		keynum=key();
		Value=MatrixKey();
		if(keynum==1||Value==1)
		{
			Runflag=!Runflag;
			min=time[4];sec=time[5];minsec=time[6];
			
		}
		if(!Runflag)
		{
		 	LCD_SetTime();	
		}
		LCD_Show();
		AT24C02_WriteByte(0,time[0]);
		Delay(5);
		AT24C02_WriteByte(1,time[1]);
		Delay(5);
		AT24C02_WriteByte(2,time[2]);
		Delay(5);
		AT24C02_WriteByte(3,time[3]);
		Delay(5);
		AT24C02_WriteByte(4,time[4]);
		Delay(5);
		AT24C02_WriteByte(5,time[5]);
		Delay(5);
	}
}

void LCD_loop()
{
	if(Runflag)
	{
		time[6]++;
		if(time[6]>=100)
		{
			time[6]=0;
			time[5]++;
		}
		if(time[5]>59)
		{
			time[5]=0;
			time[4]++;
			if(time[4]>59)
			{
				time[4]=0;
				time[3]++;
				if(time[3]>23)
				{
					time[3]=0;
				}
			}
		}
	}
}

void timer0_Routine()  interrupt 1
{
	static unsigned int T0count,T1count; 
	TL0 = 0x18;	
	TH0 = 0xFC;	
	T0count++;
	T1count++;
	if(T0count>=100)
	{
		T0count=0;
		timeSetFlashFlag=!timeSetFlashFlag;

	}
	if(T1count>=10)
	{
		T1count=0;
		LCD_loop();
	}
}  
