#include "mpi.h"
#include <stdio.h>
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
        for (int i = 1; i < size; i++)
        {
            MPI_Send(&i, 1, MPI_INT, i, i, MCW);
        }
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MCW, &status);
        printf("In process %d, number received is %d\n", rank, x);
    }

    MPI_Finalize();
    return 0;
}