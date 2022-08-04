#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;
    char filename[50], c;
    int count_chars = 0, count_lines = 1;
    printf("Enter the file to be used: ");
    scanf("%s", filename);
    fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("Entered file name does not exist.\n");
        exit(0);
    }
    c = fgetc(fptr);
    while (c != EOF)
    {
        count_chars++;
        if (c == '\n')
            count_lines++;
        c = fgetc(fptr);
    }
    fclose(fptr);
    printf("Number of characters: %d\n", count_chars);
    printf("Number of lines: %d\n", count_lines);
    return 0;
}