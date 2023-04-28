#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>

#include <math.h>

int main(int argc, char* argv[]){
    int rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MCW,&rank);

    if(rank%2==0)
        printf("Hello\n");
    else printf("World\n");

    MPI_Finalize();
    return 0;
}