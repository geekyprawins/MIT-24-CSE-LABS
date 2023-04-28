#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void add_matrices_row(int *a, int *b, int *c, int n, int m)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        for (int j = 0; j < m; j++)
        {
            c[i * m + j] = a[i * m + j] + b[i * m + j];
        }
    }
}

__global__ void add_matrices_col(int *a, int *b, int *c, int n, int m)
{
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    if (j < m)
    {
        for (int i = 0; i < n; i++)
        {
            c[i * m + j] = a[i * m + j] + b[i * m + j];
        }
    }
}

__global__ void add_matrices_elem(int *a, int *b, int *c, int n, int m)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n * m)
    {
        int i = idx / m;
        int j = idx % m;
        c[i * m + j] = a[i * m + j] + b[i * m + j];
    }
}

int main()
{
    int n, m;
    printf("Enter the dimensions of the matrices (n m): ");
    scanf("%d %d", &n, &m);
    int size = sizeof(int) * n * m;

    int *a = (int *)malloc(size);
    int *b = (int *)malloc(size);
    int *c = (int *)malloc(size);
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    printf("Enter the first matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i * m + j]);
        }
    }

    printf("Enter the second matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &b[i * m + j]);
        }
    }

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    int block_size = 256;
    int grid_size;

    int option;
    printf("Enter option(1. Row-wise 2. Column-wise 3. Element-wise) :\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        grid_size = (n + block_size - 1) / block_size;
        // Compute each row of the resultant matrix using one thread
        add_matrices_row<<<grid_size, block_size>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        printf("Result matrix (row-wise addition):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ", c[i * m + j]);
            }
            printf("\n");
        }
        break;
    case 2:
        // Compute each column of the resultant matrix using one thread
        grid_size = (m + block_size - 1) / block_size;
        add_matrices_col<<<grid_size, block_size>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        printf("Result matrix (column-wise addition):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ", c[i * m + j]);
            }
            printf("\n");
        }
        break;
    case 3:
        // Compute each element of the resultant matrix using one thread
        grid_size = (n * m + block_size - 1) / block_size;
        add_matrices_elem<<<grid_size, block_size>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        printf("Result matrix (element-wise addition):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ", c[i * m + j]);
            }
            printf("\n");
        }
        break;
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);
    return 0;
}