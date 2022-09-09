#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// credits to: Adithya Balanand (https://github.com/adithya-3141)
// for the following function

void removePreProcessorDirectives(FILE *fa, FILE *fb)
{

    char c;
    char buff;

    c = fgetc(fa);

    while (c != EOF)
    {

        if (c == '"')
        {
            fputc(c, fb);
            c = fgetc(fa);

            while (c != '"')
            {
                fputc(c, fb);
                c = fgetc(fa);
            }
            fputc(c, fb);
        }

        else if (c == '/')
        {
            buff = fgetc(fa);

            if (buff == '/')
            {

                fputc(buff, fb);
                while (c != '\n')
                {
                    fputc(c, fb);
                    c = fgetc(fa);
                }
            }

            else if (buff == '*')
            {
                fputc(c, fb);
                fputc(buff, fb);
                c = fgetc(fa);
                do
                {
                    while (c != '*')
                    {
                        fputc(c, fb);
                        c = fgetc(fa);
                    }
                    fputc(c, fb);
                    c = fgetc(fa);
                } while (c != '/');
                fputc(c, fb);
            }
        }

        else if (c == '#')
        {

            while (c != '\n')
            {
                c = fgetc(fa);
            }
        }

        else
        {
            fputc(c, fb);
        }

        c = fgetc(fa);
    }
}

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
    removePreProcessorDirectives(fptr1, fptr2);
    fclose(fptr1);
    fclose(fptr2);
    return 0;

}