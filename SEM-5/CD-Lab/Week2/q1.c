#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fptr1, *fptr2;
	char filename[50], c;
	printf("Enter the file to be opened: ");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (!fptr1)
	{
		printf("The file does not exist.\n");
		exit(0);
	}
	printf("Enter the destination file: ");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+");
	c = fgetc(fptr1);
	while (c != EOF)
	{
		if (c == ' ' || c == '\t')
		{
			fputc(' ', fptr2);
			while (c == ' ' || c == '\t')
				c = fgetc(fptr1);
		}
		while (c != ' ' && c != '\t' && c != EOF)
		{
			fputc(c, fptr2);
			c = fgetc(fptr1);
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}