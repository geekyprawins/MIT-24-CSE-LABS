#include <stdio.h>

__global__ void oddEvenSort(int *arr, int n)
{
    int temp;
    int i, idx = blockIdx.x * blockDim.x + threadIdx.x;
    for (i = 0; i < n; i++)
    {
        if (idx % 2 == 0) // Even phase
        {
            if (i % 2 == 0 && idx < n-1)
            {
                if (arr[idx] > arr[idx+1])
                {
                    temp = arr[idx];
                    arr[idx] = arr[idx+1];
                    arr[idx+1] = temp;
                }
            }
        }
        else // Odd phase
        {
            if (i % 2 == 1 && idx < n-1)
            {
                if (arr[idx] > arr[idx+1])
                {
                    temp = arr[idx];
                    arr[idx] = arr[idx+1];
                    arr[idx+1] = temp;
                }
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of elements to sort: ");
    scanf("%d", &n);

    int *arr, *d_arr;
    arr = (int *) malloc(n * sizeof(int));

    printf("Enter %d elements to sort: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    oddEvenSort<<<blocksPerGrid, threadsPerBlock>>>(d_arr, n);

    cudaMemcpy(arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    cudaFree(d_arr);
    free(arr);

    return 0;
}
