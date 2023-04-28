// Matrix multiplication of 4x4 matrix #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cuda_runtime.h>
#include <stdio.h>
#define BLOCK_WIDTH 2
#define TILE_WIDTH 2
#define WIDTH 4

__global__ void MatMulElementThreadShared(int *a, int *b, int *c)
{
    __shared__ int MDs[TILE_WIDTH][TILE_WIDTH];
    __shared__ int NDs[TILE_WIDTH][TILE_WIDTH];
    int m;
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int Row = by * TILE_WIDTH + ty;
    int Col = bx * TILE_WIDTH + tx;
    int Pvalue = 0;
    for (m = 0; m < WIDTH / TILE_WIDTH; m++)
    {
        MDs[ty][tx] = a[Row * WIDTH + m * TILE_WIDTH + tx];
        NDs[ty][tx] = b[(m * TILE_WIDTH + ty) * WIDTH + Col];
        __syncthreads();
        for (int k = 0; k < TILE_WIDTH; k++)
        {
            Pvalue += MDs[ty][k] * NDs[k][tx];
        }
        __syncthreads();
    }
    c[Row * WIDTH + Col] = Pvalue;
}

int main()
{
    int *matA, *matB, *matProd;
    int *da, *db, *dc;
    printf("\n== Enter elements of Matrix A (4x4)==\n");
    matA = (int *)malloc(sizeof(int) * WIDTH * WIDTH);
    for (int i = 0; i < WIDTH * WIDTH; i++)
    {
        scanf("%d", &matA[i]);
    }
    printf("\n== Enter elements of Matrix B (4x4)=\n");
    matB = (int *)malloc(sizeof(int) * WIDTH * WIDTH);
    for (int i = 0; i < WIDTH * WIDTH; i++)
    { 
        scanf("%d", &matB[i]);
    }
   
    matProd = (int *)malloc(sizeof(int) * WIDTH * WIDTH);
    cudaMalloc((void **)&da, sizeof(int) * WIDTH * WIDTH);
    cudaMalloc((void **)&db, sizeof(int) * WIDTH * WIDTH);
    cudaMalloc((void **)&dc, sizeof(int) * WIDTH * WIDTH);
    cudaMemcpy(da, matA, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);
    cudaMemcpy(db, matB, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);
    int NumBlocks = WIDTH / BLOCK_WIDTH;
    dim3 grid_conf(NumBlocks, NumBlocks);
    dim3 block_conf(BLOCK_WIDTH, BLOCK_WIDTH);
    MatMulElementThreadShared<<<grid_conf, block_conf>>>(da, db, dc);
    cudaMemcpy(matProd, dc, sizeof(int) * WIDTH * WIDTH, cudaMemcpyDeviceToHost);
    printf("\n--Result of Multiplication=-\n");
    printf("----------------\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%6d", matProd[i * 4 + j]);
        }
        printf("\n");
    }

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
    free(matA);
    free(matB);
    free(matProd);

    return 0;
}
