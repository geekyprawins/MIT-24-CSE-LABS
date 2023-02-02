#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);

    int a = 5;
    int b = 10;

    if (rank == 0)
    {
        printf("Performing %d+%d: %d\n", a, b, a + b);
    }
    else if (rank == 1)
    {
        printf("Performing %d-%d: %d\n", a, b, a - b);
    }
    else if (rank == 2)
    {
        printf("Performing %d*%d: %d\n", a, b, a * b);
    }
    else if (rank == 3)
    {
        printf("Performing %d/%d: %d\n", a, b, a / b);
    }
    else if (rank == 4)
    {
        printf("Performing %d\%%d: %d\n", a, b, a % b);
    }
    else
        printf("No operation!\n");

    MPI_Finalize();
    return 0;
}