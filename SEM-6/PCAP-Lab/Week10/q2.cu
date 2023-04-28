#include <stdio.h>
#include <cuda_runtime.h>

__global__ void replace_rows(float *A, int num_rows, int num_cols) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= num_rows) return;

    for (int j = 0; j < num_cols; j++) {
        int idx = row * num_cols + j;
        int power = row + 1;
        A[idx] = powf(A[idx], power);
    }
}

int main() {
    int M, N;
    printf("Enter no of rows and columns : ");
    scanf("%d %d", &M, &N);

    float *A = (float*)malloc(sizeof(float) * M * N);
    printf("Enter the matrix :\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%f", &A[i * N + j]);
        }
    }

    float *d_A;
    cudaMalloc(&d_A, sizeof(float) * M * N);
    cudaMemcpy(d_A, A, sizeof(float) * M * N, cudaMemcpyHostToDevice);

    replace_rows<<<(M + 255) / 256, 256>>>(d_A, M, N);

    cudaMemcpy(A, d_A, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

    printf("Modified matrix : \n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%g \t", A[i * N + j]);
        }
        printf("\n");
    }

    free(A);
    cudaFree(d_A);
    return 0;
}
