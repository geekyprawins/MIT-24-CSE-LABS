#include <stdio.h>
#include <mpi/mpi.h>
#include <stdlib.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char *argv[])
{
    int rank, size, fact = 1, factsum, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    for (i = 1; i <= rank + 1; i++)
        fact = fact * i;

    MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM, 0, MCW);

    if (rank == 0)
        printf("Sum of all factorial = %d\n", factsum);

    MPI_Finalize();
    exit(0);
}