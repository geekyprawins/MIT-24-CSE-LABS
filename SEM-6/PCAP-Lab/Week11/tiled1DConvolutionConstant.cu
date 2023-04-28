#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define K 3
#define BLOCK_SIZE 256

__constant__ float d_kernel[K];

__global__ void convConst(float *d_in, float *d_out, int n) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float sum = 0.0f;

    for (int i = 0; i < K; i++) {
        int idx = tid - (K/2) + i;
        if (idx >= 0 && idx < n) {
            sum += d_in[idx] * d_kernel[i];
        }
    }

    d_out[tid] = sum;
}

int main() {
    int n;
    printf("Enter the size of the input array: ");
    scanf("%d", &n);

    float *h_in = (float*)malloc(n * sizeof(float));
    float *h_out = (float*)malloc(n * sizeof(float));
    float *d_in, *d_out;
    cudaMalloc((void**)&d_in, n * sizeof(float));
    cudaMalloc((void**)&d_out, n * sizeof(float));

    printf("Enter the input array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &h_in[i]);
    }

    float h_kernel[K] = {1.0f, 2.0f, 3.0f};
    cudaMemcpyToSymbol(d_kernel, h_kernel, K * sizeof(float));

    int num_blocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    cudaMemcpy(d_in, h_in, n * sizeof(float), cudaMemcpyHostToDevice);
    convConst<<<num_blocks, BLOCK_SIZE>>>(d_in, d_out, n);
    cudaMemcpy(h_out, d_out, n * sizeof(float), cudaMemcpyDeviceToHost);
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    printf("Time taken: %f ms\n", milliseconds);

    printf("Output array:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", h_out[i]);
    }
    printf("\n");

    free(h_in);
    free(h_out);
    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}
