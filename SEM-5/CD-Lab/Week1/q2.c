#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char filename[50], c;
    long int size;
    printf("Enter the name of the file to be reversed: ");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if (!fptr1)
    {
        printf("The entered file name does not exist.\n");
        exit(0);
    }
    fseek(fptr1, 0, SEEK_END);
    size = ftell(fptr1);
    printf("File size is: %ld\n", size);
    printf("Enter the destination file: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w+");
    fseek(fptr1, -2, SEEK_CUR);
    while (size)
    {
        c = fgetc(fptr1);
        fputc(c, fptr2);
        fseek(fptr1, -2, SEEK_CUR);
        size--;
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}