#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{

    int rank, size, N, d, nvCount = 0, totalNVCount = 0, length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    char string[size * 3], *str;
    if (rank == 0)
    {
        printf("Enter the string (length should be multiple of) %d : ", size);
        scanf("%s", string);
        length = strlen(string);
        length /= size;
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    str = (char *)calloc(length, sizeof(char));
    MPI_Scatter(string, length, MPI_CHAR, str, length, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < length; i++)
    {
        char x = str[i];
        if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' || x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U')
            nvCount++;
    }
    nvCount = length - nvCount;

    int res[size];

    MPI_Gather(&nvCount, 1, MPI_INT, res, 1, MPI_INT, 0, MCW);
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
            totalNVCount += res[i];
        printf("The total non-vowels are : %d\n", totalNVCount);
    }

    free(str);
    MPI_Finalize();
    return 0;
}