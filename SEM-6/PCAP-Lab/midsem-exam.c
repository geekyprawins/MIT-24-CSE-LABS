#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD


int isNum(char n){
    if(n=='0'||n=='1'||n=='2'||n=='3'||n=='4'||n=='5'||n=='6'||n=='7'||n=='8'||n=='9')
        return 1;
    return 0;
}

int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MCW,&rank);
    MPI_Comm_size(MCW,&size);

    char str[100];
    int len;

    if(rank==0){
        printf("Enter a string which is multiples of %d: \n",size);
        scanf("%s",str);
        printf("String entered is %s\n",str);
        len = strlen(str);
        printf("String length is %d\n",len);
    }

    MPI_Bcast(&len,1,MPI_INT,0,MCW);

    int wl = len/size;

    char w[wl];

    MPI_Scatter(str,wl,MPI_CHAR,w,wl,MPI_CHAR,0,MCW);

    int c=0,gc;


    for(int i=0;i<wl;i++){
        if(isNum(w[i])) c++;
    }

    char digStr[c];
    int g=0;
    for(int i=0;i<wl;i++){
        if(isNum(w[i])){
            digStr[g] = w[i];
            g++;
        }
    }

    digStr[g]='\0';


    printf("From rank: %d, digit string: %s, digit count: %d\n",rank,digStr,c);

    MPI_Reduce(&c,&gc,1,MPI_INT,MPI_SUM,0,MCW);

    if(rank==0){
        printf("Total digits in the string: %d\n",gc);
    }

    MPI_Finalize();

    return 0;

}