#include <LPC17xx.h>

long int arr[4] = {0, 0, 0, 0};
unsigned char hexarr[16] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71};
unsigned int i = 0, j = 0;
int sign = 1;

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

    LPC_GPIO0->FIODIR |= 0xFF << 4;
    LPC_GPIO1->FIODIR |= 0xF << 23;
    LPC_GPIO2->FIODIR &= ~(1 << 0);

    for (arr[3] = (sign == 1) ? 0 : 15;; arr[3] = (arr[3] + sign + 16) % 16)
        for (arr[2] = (sign == 1) ? 0 : 15; arr[2] >= 0 && arr[2] <= 15; arr[2] += sign)
            for (arr[1] = (sign == 1) ? 0 : 15; arr[1] >= 0 && arr[1] <= 15; arr[1] += sign)
                for (arr[0] = (sign == 1) ? 0 : 15; arr[0] >= 0 && arr[0] <= 15; arr[0] += sign)
                {
                    if (!(LPC_GPIO2->FIOPIN & 1 << 0))
                    {
                        delay(1000);
                        sign *= -1;
                    }

                    for (i = 0; i < 4; i++)
                    {
                        LPC_GPIO1->FIOCLR |= 0xF << 23;
                        LPC_GPIO1->FIOPIN |= i << 23;
                        LPC_GPIO0->FIOCLR |= 0xFF << 4;
                        LPC_GPIO0->FIOPIN |= hexarr[arr[i]] << 4;
                        delay(1000);
                    }
                    LPC_GPIO0->FIOCLR |= 0xFF << 4;
                }
}