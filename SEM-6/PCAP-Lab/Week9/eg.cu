#include <stdio.h>
#include <cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdlib.h>

__global__ void transpose(int *a, int *t){
    int n=threadIdx.x, m=blockIdx.x, size=blockDim.x, size1=gridDim.x;
    t[n*size+m]=a[m*size+n];
}

int main(void){
    int *a, *t, m, n, i, j;
    int *d_a, *d_t;

    printf("Enter m:");
    scanf("%d", &m);
    printf("Enter n:");
    scanf("%d", &n);

    int size=sizeof(int)*m*n;

    a=(int*)malloc(m*n*sizeof(int));
    t=(int*)malloc(m*n*sizeof(int));

    printf("Enter input matrix: ");

    for(i=0; i<m*n; i++){
        scanf("%d", &a[i]);
    }

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_t, size);
    
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    transpose<<<m,n>>>(d_a,d_t);
    cudaMemcpy(t,d_t, size, cudaMemcpyDeviceToHost);
    printf("Result vector is: \n");

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d\t", t[i*m+j]);
        }
        printf("\n");
    }

    getChar();
    cudaFree(d_a);
    cudaFree(d_t);
    
    return 0;
}