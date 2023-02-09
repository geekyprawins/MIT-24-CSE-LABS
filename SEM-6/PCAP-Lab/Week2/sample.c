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
        printf("Enter a value in master process:");
        scanf("%d", &x);
        MPI_Send(&x, 1, MPI_INT, 1, 20, MCW);
        fprintf(stdout, "I have sent %d from process %d\n", x, rank);
        fflush(stdout);
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, 0, 20, MCW, &status);
        fprintf(stdout, "I have received %d in process %d\n", x, rank);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}