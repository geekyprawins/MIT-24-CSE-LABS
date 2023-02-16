#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{

    int rank, size, N, *numbers, c, i, fact, sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (rank == 0)
    {
        N = size;
        printf("Enter %d values: \n", N);
        numbers = (int *)calloc(N, sizeof(int));
        for (i = 0; i < N; i++)
            scanf("%d", &numbers[i]);
    }

    MPI_Scatter(numbers, 1, MPI_INT, &c, 1, MPI_INT, 0, MCW);
    fact = 1;
    while (c > 0)
    {
        fact *= c;
        c--;
    }

    int res[N];

    MPI_Gather(&fact, 1, MPI_INT, res, 1, MPI_INT, 0, MCW);
    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
            sum += res[i];
        printf("The Sum is %d\n", sum);
        free(numbers);
    }

    MPI_Finalize();
    return 0;
}