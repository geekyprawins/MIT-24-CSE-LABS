#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){
    int rank,x=2;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MCW,&rank);

    printf("pow(%d,%d) is %lf\n",x,rank,pow(x,rank));

    MPI_Finalize();
    return 0;
}