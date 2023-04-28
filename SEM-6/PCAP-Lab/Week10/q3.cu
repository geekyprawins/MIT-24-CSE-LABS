#include <stdio.h>

__global__ void complement_kernel(int* A, int* B, int M, int N)
{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    int num, binary_num = 0, base = 1, mask;
    if (i < M && j < N) {
        if (i == 0 || i == M-1 || j == 0 || j == N-1) {
            B[i*N+j] = A[i*N+j];
        } else {
            num = A[i*N+j];
            mask = ~0;
            while (num & mask) {
                mask <<= 1;
            }
            num = ~num & ~mask;
            while (num > 0) {
                binary_num += (num % 2) * base;
                num /= 2;
                base *= 10;
            }
            B[i*N+j] = binary_num;
        }
    }
}

int main()
{
    int M, N;
    printf("Enter the number of rows of the matrix: ");
    scanf("%d", &M);
    printf("Enter the number of columns of the matrix: ");
    scanf("%d", &N);

    int A[M*N];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i*N+j]);
        }
    }

    int B[M*N];

    // Allocate memory on the GPU
    int *d_A, *d_B;
    cudaMalloc((void **)&d_A, M * N * sizeof(int));
    cudaMalloc((void **)&d_B, M * N * sizeof(int));

    // Copy input data to the GPU
    cudaMemcpy(d_A, A, M * N * sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel
    dim3 block_size(16, 16);
    dim3 num_blocks((N + block_size.x - 1) / block_size.x, (M + block_size.y - 1) / block_size.y);
    complement_kernel<<<num_blocks, block_size>>>(d_A, d_B, M, N);

    // Copy output data from the GPU
    cudaMemcpy(B, d_B, M * N * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the output matrix
    printf("Output matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", B[i*N+j]);
        }
        printf("\n");
    }

    // Free memory on the GPU
    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}
