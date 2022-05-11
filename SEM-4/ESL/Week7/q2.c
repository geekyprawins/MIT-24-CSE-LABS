#include <LPC17xx.h>

unsigned char hexarr[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};

long int arr[4] = {9, 9, 9, 9};

unsigned int i = 0, j = 0;

void initializeTimer()
{
    LPC_TIM0->CTCR = 0x0;
    LPC_TIM0->PR = 2;
    LPC_TIM0->MR0 = 999;
    LPC_TIM0->MCR = 0x02;
    LPC_TIM0->EMR = 0x02 << 4;
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->TCR = 0x01;
}

void delay(int ms)
{
    initializeTimer();
    for (j = 0; j < ms; j++)
        while (!(LPC_TIM0->EMR & 1))
            ;
}

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_GPIO0->FIODIR |= 0XFF0;
    LPC_GPIO1->FIODIR |= 0XF << 23;

    while (1)
    {
        for (arr[3] = 9; arr[3] >= 0; arr[3]--)
            for (arr[2] = 9; arr[2] >= 0; arr[2]--)
                for (arr[1] = 9; arr[1] >= 0; arr[1]--)
                    for (arr[0] = 9; arr[0] >= 0; arr[0]--)
                    {
                        for (i = 0; i < 4; i++)
                        {
                            LPC_GPIO1->FIOPIN = i << 23;
                            LPC_GPIO0->FIOPIN = hexarr[arr[i]] << 4;
                            delay(1);
                        }
                        delay(1);
                        LPC_GPIO0->FIOCLR |= 0X00000FF0;
                    }
    }
}