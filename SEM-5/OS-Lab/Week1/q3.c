#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int a = 20;
    float b = 54.258;
    char c = 'P';
    char str[] = "Praveen";
    printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n", a, b, c, str, a);
    errno = EPERM;
    printf("Error Access Number : %m\n");
    return 0;
}