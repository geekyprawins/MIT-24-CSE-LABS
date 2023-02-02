#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);

    printf("Rank is %d\n", rank);

    if (rank == 0)
    {
        int low = 1, high = 50, flag, i;
        while (low < high)
        {
            flag = 0;
            if (low <= 1)
            {
                ++low;
                continue;
            }
            for (i = 2; i <= low / 2; ++i)
            {

                if (low % i == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
                printf("%d ", low);

            ++low;
        }
        printf("\n");
    }
    else if (rank == 1)
    {
        int low = 51, high = 100, flag, i;
        while (low < high)
        {
            flag = 0;
            if (low <= 1)
            {
                ++low;
                continue;
            }
            for (i = 2; i <= low / 2; ++i)
            {

                if (low % i == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
                printf("%d ", low);

            ++low;
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
