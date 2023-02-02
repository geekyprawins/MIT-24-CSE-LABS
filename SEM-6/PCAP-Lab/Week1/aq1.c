#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);

    int arr[9] = {18, 523, 301, 12342, 14, 108, 150, 1928};
    int n = arr[rank], reverse = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        reverse = reverse * 10 + rem;
        n /= 10;
    }

    arr[rank] = reverse;

    printf("%d ", arr[rank]);
    MPI_Finalize();
    return 0;
}