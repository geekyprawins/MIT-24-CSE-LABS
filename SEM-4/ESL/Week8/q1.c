#include <LPC17xx.h>
#define DATA 0xF << 23
#define RS 1 << 27
#define EN 1 << 28
char msg[] = {"Key Pressed: "};
int row, column, col, i;
int keyarr[4][4] = {{'0', '1', '2', '3'}, {'4', '5', '6', '7'}, {'8', '9', 'A', 'B'}, {'C', 'D', 'E', 'F'}};
int i = 0, j = 0;
void initializeLCD(void);
void writeData(int data, int rs);
void pulsate(void);
void initializeTimer(void);
void delay(int ms);
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
void initializeLCD()
{
    LPC_GPIO0->FIODIR |= (DATA | RS | EN);
    writeData(0x33, 0);
    writeData(0x32, 0);
    writeData(0x28, 0);
    writeData(0x0C, 0);
    writeData(0x06, 0);
    writeData(0x01, 0);
}
void writeData(int data, int rs)
{
    LPC_GPIO0->FIOCLR |= (DATA | RS | EN);
    if (rs == 1)
        LPC_GPIO0->FIOPIN |= RS;
    LPC_GPIO0->FIOPIN |= (data & 0xF0) << 19;
    pulsate();
    LPC_GPIO0->FIOCLR |= DATA;
    LPC_GPIO0->FIOPIN |= (data & 0x0F) << 23;
    pulsate();
}
void pulsate()
{
    LPC_GPIO0->FIOPIN |= EN;
    delay(10);
    LPC_GPIO0->FIOCLR |= EN;
    delay(20);
}
int main()
{
    LPC_GPIO2->FIODIR |= 0xF << 10;    // output pins
    LPC_GPIO1->FIODIR &= ~(0xF << 23); //;input pins
    initializeLCD();
    writeData(0x80, 0);
    for (i = 0; msg[i]; i++)
        writeData(msg[i], 1);
    for (row = 0;; row = (row + 1) % 4)
    {
        LPC_GPIO2->FIOCLR |= 0xF << 10;           //; clear row pins
        LPC_GPIO2->FIOPIN |= 1 << (10 + row);     //; enable row one by one
        column = (LPC_GPIO1->FIOPIN >> 23) & 0xF; //; read from column port pins

        if (column)
        {
            col = -1;
            while (column)
            {
                column /= 2;
                col++;
            }
            writeData(0xc0, 0);
            writeData(keyarr[row][col], 1);
        }
    }
}