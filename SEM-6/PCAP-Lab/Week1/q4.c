#include "mpi.h"
#define MCW MPI_COMM_WORLD
#include <stdio.h>

int main(int argc, char* argv[]){
    int rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MCW,&rank);

    char word[] = "HeLLO";

    if(word[rank]>=65 && word[rank]<=90)
            word[rank]+=32;
    else if(word[rank]>=97 && word[rank]<=122)
            word[rank]-=32;
    
    printf("New string: %s Rank is: %d\n",word,rank);
   
    MPI_Finalize();
    return 0;
}