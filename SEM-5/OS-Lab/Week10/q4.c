#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int numSector = 10;
    char sector[1024] = "";
    printf("Enter content to write: ");
    scanf("%s", sector);
    FILE* diskFptr = fopen(argv[1], "w+");
    if(!diskFptr) {
        printf("File not found!\n");
        exit(0);
    }
    fseek(diskFptr, 20, SEEK_SET);
    int n = fwrite(sector, strlen(sector), 1, diskFptr);
    if(n<0) {
        printf("Error!\n");
        exit(0);
    }
    printf("Write Success!\n");
    fclose(diskFptr);
    return 0;
}