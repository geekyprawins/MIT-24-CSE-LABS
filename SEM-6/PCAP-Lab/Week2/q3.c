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
        int array[size - 1];
        printf("Enter %d elements : ", size - 1);
        for (int i = 0; i < size - 1; i++)
        {
            scanf("%d", &array[i]);
        }
        int buffer_size = MPI_BSEND_OVERHEAD + sizeof(int) * size - 1;
        int *buffer = (int *)malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        for (int i = 0; i < size - 1; i++)
        {
            MPI_Bsend(&array[i], 1, MPI_INT, i + 1, i + 1, MCW);
        }
        MPI_Buffer_detach(&buffer, &buffer_size);
    }
    else
    {
        int num;
        MPI_Recv(&num, 1, MPI_INT, 0, rank, MCW, &status);
        if (rank % 2 == 0)
        {
            printf("Received digit: %d in process: %d, cube value : %d\n", num, rank, num * num * num);
        }
        else
        {
            printf("Received digit: %d in process: %d, square value : %d\n", num, rank, num * num);
        }
    }

    MPI_Finalize();
    return 0;
}
