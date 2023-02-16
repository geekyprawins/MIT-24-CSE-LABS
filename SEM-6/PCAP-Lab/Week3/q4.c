#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{

    int rank, size, n = 3, length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    char A[size * n], B[size * n], *strA, *strB, result[2 * n * size + 1];
    if (rank == 0)
    {
        printf("Enter a string of length %d : ", size * n);
        scanf("%s", A);
        printf("Enter a string of length %d : ", size * n);
        scanf("%s", B);
        length = strlen(A);
        length /= size;
    }
    MPI_Bcast(&length, 1, MPI_INT, 0, MCW);
    strA = (char *)calloc(length, sizeof(char));
    strB = (char *)calloc(length, sizeof(char));
    MPI_Scatter(A, length, MPI_CHAR, strA, length, MPI_CHAR, 0, MCW);
    MPI_Scatter(B, length, MPI_CHAR, strB, length, MPI_CHAR, 0, MCW);
    char sendStr[2 * length + 1];
    sendStr[0] = '\0';
    int i = 0, j = 0, k = 0;
    while (i < length || j < length)
    {
        if (k % 2 == 0)
            sendStr[k++] = strA[i++];
        else
            sendStr[k++] = strB[j++];
    }
    sendStr[k] = '\0';
    MPI_Gather(sendStr, 2 * length, MPI_CHAR, result, 2 * length, MPI_CHAR, 0, MCW);
    if (rank == 0)
    {
        result[2 * n * size] = '\0';
        printf("The result is : ");
        for (int i = 0; i < 2 * n * size; i++)
        {
            printf("%c", result[i]);
        }
        printf("\n");
    }

    free(strA);
    free(strB);
    MPI_Finalize();
    return 0;
}