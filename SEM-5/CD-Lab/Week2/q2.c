#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char filename[50], c;
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
    while (c != EOF)
    {
        if (c == '#')
        {
            while (fgetc(fptr1) != '\n')
            {
            };
        }
        c = fgetc(fptr1);
        if (c == '#')
            continue;
        while (c != EOF && c != '#')
        {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}