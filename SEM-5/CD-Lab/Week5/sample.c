/*

E --> TEprime
E'--> +TE' / empty
T --> FT'
T'--> *FT' / empty
F --> (E) / i

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void E();
void Eprime();
void T();
void Tprime();
void F();

void invalid()
{
    printf("---------------ERROR!----------\n");
    exit(0);
}

void valid()
{

    printf("---------------SUCCESS!---------\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (str[curr] == '+')
    {
        curr++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (str[curr] == '*')
    {
        curr++;
        F();
        Tprime();
    }
}

void F()
{
    if (str[curr] == '(')
    {
        curr++;
        E();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
        else
            invalid();
    }
    else if (str[curr] == 'i')
    {
        curr++;
        return;
    }
    else
        invalid();
}

int main()
{
    printf("Enter String: ");
    scanf("%s", str);
    E();
    if (str[curr] == '$')
        valid();
    else
        // printf("%c\n",str[curr]);
        invalid();
}