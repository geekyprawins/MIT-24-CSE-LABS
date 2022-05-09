
#include<LPC17xx.h>

unsigned long c=1;
unsigned int i=0;

int main()
{
	LPC_GPIO0->FIODIR|=0XFF0;
	LPC_GPIO2->FIODIR&=0xFFFFEFFF;
	
	while(1)
	{
		if(LPC_GPIO2->FIOPIN & 1<<12)
		{
			LPC_GPIO0->FIOPIN=0;
			c=1;
		}
		else
		{
			LPC_GPIO0->FIOPIN=c<<4;
			c=(c<<1)%255;
		}
		
		for(i=0; i<10000; i++);
	}
}