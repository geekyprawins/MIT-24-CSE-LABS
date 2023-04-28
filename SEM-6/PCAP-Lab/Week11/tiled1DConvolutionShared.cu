#include <stdio.h>

#define THREAD_BLOCK_SIZE 256
#define MASK_WIDTH 3

__global__ void convolution_kernel(float* N, float* M, float* P, int width, int mask_width) {
    // Determine the index of the current thread
    int thread_idx = threadIdx.x;
    int block_idx = blockIdx.x;
    int block_dim = blockDim.x;

    // Compute the start and end index of the current tile
    int tile_start = block_idx * block_dim - mask_width/2;
    // int tile_end = tile_start + block_dim - 1 + mask_width;

    // Allocate shared memory for the tile
    __shared__ float tile_data[THREAD_BLOCK_SIZE + MASK_WIDTH - 1];

    // Load data from global memory into shared memory
    for (int i = thread_idx - mask_width/2; i < block_dim + mask_width/2; i += block_dim) {
        int index = tile_start + i;
        if (index >= 0 && index < width) {
            tile_data[i + mask_width/2] = N[index];
        } else {
            tile_data[i + mask_width/2] = 0;
        }
    }

    // Synchronize to ensure all threads have finished loading data into shared memory
    __syncthreads();

    // Compute the output of the current thread
    float output = 0;
    for (int i = 0; i < mask_width; i++) {
        output += tile_data[thread_idx + i] * M[i];
    }

    // Store the output in global memory
    if (thread_idx < block_dim && tile_start + thread_idx >= 0 && tile_start + thread_idx < width) {
        P[tile_start + thread_idx] = output;
    }
}



int main() {
    // Define the input and mask arrays
 

    float N[1000],  P[1000];
    int n;
    // Initialize the input and mask arrays
    printf("Enter width of main array: ");
    scanf("%d",&n);
    printf("enter elements of the main array: ");
    for(int i = 0;i<n;i++){
        scanf("%f",&N[i]);
    }
       int mask_width;
    printf("Enter width of mask array: \n");
    scanf("%d",&mask_width);
   float M[mask_width];
        printf("enter elements of the mask array: ");
    for(int i = 0;i<mask_width;i++){
        scanf("%f",&M[i]);
    }
    // Allocate device memory for the input, mask, and output arrays
    float *d_N, *d_M, *d_P;
    cudaMalloc(&d_N, n * sizeof(float));
    cudaMalloc(&d_M, mask_width * sizeof(float));
    cudaMalloc(&d_P, n * sizeof(float));

    // Copy the input and mask arrays from host to device
    cudaMemcpy(d_N, N, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    // Launch the kernel with the appropriate arguments
    int num_blocks = (n + THREAD_BLOCK_SIZE - 1) / THREAD_BLOCK_SIZE;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float elapsedTime;
    
    
    cudaEventRecord(start,0);
    
    convolution_kernel<<<num_blocks, THREAD_BLOCK_SIZE>>>(d_N, d_M, d_P, n, mask_width);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    elapsedTime = 0;
    cudaEventElapsedTime(&elapsedTime, start, stop);
    // Copy the output array from device to host
    cudaMemcpy(P, d_P, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the output array
    for (int i = 0; i < n; i++) {
        printf("%f ", P[i]);
    }
    printf("\n");
printf("\nTotal Time Taken(Shared Memory): %f\n", elapsedTime);
    // Free device memory
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}