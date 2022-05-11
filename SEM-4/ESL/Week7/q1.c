#include <LPC17xx.h>
unsigned int dig_count = 0x00;
unsigned char array_dec[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // digits for representing digits 0 to 9
unsigned int dig_value[4] = {4, 3, 2, 1};                                                   // value 4 to 1
unsigned int dig_select[4] = {0 << 23, 1 << 23, 2 << 23, 3 << 23};                          // selects the display unit
void delay(void);
void display(void);

int main(void)
{
    LPC_GPIO0->FIODIR |= 0xFF << 4; // P0.4 to P0.11 output
    LPC_GPIO1->FIODIR |= 15 << 23;  // P1.23 to P1.26 output

    while (1)
    {
        delay();
        display();
        dig_count += 1;
        if (dig_count == 0x04)
            dig_count = 0x00;
    } // end of while(1)

} // end of main

void display(void) // To Display on 7-segments
{

    LPC_GPIO1->FIOPIN = dig_select[dig_count];
    LPC_GPIO0->FIOPIN = array_dec[dig_value[dig_count]] << 4;
}

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 10000; i++)
        ;
}
