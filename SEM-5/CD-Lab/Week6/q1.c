/*
S -> a | > | (T)
T ->T,S | S
after removing LR
S -> a | > | (T)
T -> ST'
T' -> ,ST' | empty
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];
void S();
void T();
void Tprime();
void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}
void S()
{
    if (str[curr] == 'a' || str[curr] == '>')
    {
        curr++;
        return;
    }
    else if (str[curr] == '(')
    {
        curr++;
        T();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
        else
            invalid();
    }
    else
        invalid();
}
void T()
{
    S();
    Tprime();
}
void Tprime()
{
    if (str[curr] == ',')
    {
        curr++;
        S();
        Tprime();
    }
}
void main()
{
    printf("Enter String: \n");
    scanf("%s", str);
    S();
    if (str[curr] == '$')
        valid();
    else
        invalid();
}