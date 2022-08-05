#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char keys[11][10] = {"int", "main", "char",
                         "FILE", "while", "if",
                         "else if", "else", "continue",
                         "break", "return"};
    char buff[50], filename[50], c;
    FILE *fptr1, *fptr2;
    printf("Enter the file name of the file to be read: ");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if (!fptr1)
    {
        printf("File does not exist.\n");
        exit(0);
    }
    printf("Enter the destination file name: ");
    memset(filename, 0, 50);
    scanf("%s", filename);
    fptr2 = fopen(filename, "w+");
    c = fgetc(fptr1);
    int i = 0, k = 0;
    while (c != EOF)
    {
        if (isalpha(c))
        {
            buff[i++] = c;
            c = fgetc(fptr1);
            while (isalpha(c))
            {
                buff[i++] = c;
                c = fgetc(fptr1);
            }
            buff[i] = '\0';
            for (int j = 0; j < 11; j++)
            {
                if (strcmp(buff, keys[j]) == 0)
                {
                    while (buff[k])
                        fputc(toupper(buff[k++]), fptr2);
                    fputc('\n', fptr2);
                    break;
                }
            }
        }
        i = 0;
        k = 0;
        memset(buff, 0, 50);
        c = fgetc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}