#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
                                                          
int main()
{
    int numSector = 10;
    char sector[1024] = {0};
    FILE *disqueF = fopen("q1.txt", "r");
    fseek(disqueF, numSector * 512, SEEK_SET);
    fwrite(sector, 1024, 1, disqueF);
    for (int i = 0; i < sizeof(sector); i++)
    {
        printf("%x", sector[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    fclose(disqueF);

    return 0;
}