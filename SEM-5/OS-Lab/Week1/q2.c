#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    int f1, f2, i = 0, k = 0, p = 0;
    char ch[100], ch2[100], chr;

    if (argc != 3)
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }

    if ((f1 = open(argv[1], O_RDONLY)) == -1)
    {
        printf("File not found\n");
        exit(1);
    }

    // printf("File Contents=%s and Number of characters are=%d",buffer, nread);
    while ((read(f1, &chr, 1)) > 0)
    {
        if (chr != '\n')
        {
            ch[i] = chr;
            i++;
        }

        else
        {
            k++;
            p++;
            ch[i] = '\0';
            i = 0;
            printf("Line:%d \t %s \n", p, ch);
            if (k == 20)
            {
                fgetc(stdin);
                k = 0;
            }
        }
    }
    close(f1);

    if ((f2 = open(argv[2], O_RDONLY)) == -1)
    {
        printf("File not found\n");
        exit(1);
    }

    p = 0;

    while ((read(f2, &chr, 1)) > 0)
    {
        if (chr != '\n')
        {
            ch2[i] = chr;
            i++;
        }

        else
        {
            k++;
            p++;
            ch[i] = '\0';
            i = 0;
            printf("Line:%d \t %s \n", p, ch2);
            if (k == 20)
            {
                fgetc(stdin);
                k = 0;
            }
        }
    }
    exit(0);
}

