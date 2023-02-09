#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{
    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    MPI_Status status;

    if (rank == 0)
    {
        printf("Enter the integer to be transmitted: ");
        scanf("%d", &x);
        printf("Value before transmission: %d\n", x);
        x++;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MCW);
        MPI_Recv(&x, 1, MPI_INT, size - 1, 0, MCW, &status);
        printf("Value after transmission: %d\n", x);
    }
    else if (rank == size - 1)
    {
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MCW, &status);
        x++;
        MPI_Send(&x, 1, MPI_INT, 0, 0, MCW);
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MCW, &status);
        x++;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MCW);
    }

    MPI_Finalize();
    return 0;
}
