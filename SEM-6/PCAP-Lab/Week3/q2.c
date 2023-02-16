#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{

    int rank, size, N, M, length, *numbers, c[100], sum = 0, avg = 0, gAvg = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (rank == 0)
    {
        printf("Enter value of M:\n");
        scanf("%d", &M);
        N = size;
        length = N * M;
        printf("Enter %d values: \n", length);
        numbers = (int *)calloc(length, sizeof(int));
        for (int i = 0; i < length; i++)
            scanf("%d", &numbers[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MCW);

    MPI_Scatter(numbers, M, MPI_INT, c, M, MPI_INT, 0, MCW);

    for (int i = 0; i < M; i++)
        sum += c[i];

    avg = sum / M;

    int res[size];
    MPI_Gather(&avg, 1, MPI_INT, res, 1, MPI_INT, 0, MCW);
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
            gAvg += res[i];
        printf("The total avg is %f\n", (double)gAvg / N);
        free(numbers);
    }

    MPI_Finalize();
    return 0;
}