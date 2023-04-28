#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void vectorSin(float *A, float *B,int n)
{
	int tid=blockIdx.x*blockDim.x+threadIdx.x;

	if(tid<n)
		B[tid]=sin(A[tid]);
}

int main(void) 
{
	int n;

	printf("Enter number of elements:\t");
	scanf("%d",&n);

	float *h_A,*h_B;
	float *d_A, *d_B;
	
	int size = sizeof(float)*n;

	h_A=(float*)malloc(sizeof(size));
	h_B=(float*)malloc(sizeof(size));

	cudaMalloc((void **)&d_A, size);
	cudaMalloc((void **)&d_B, size);

	printf("Enter input vector:\n");
	for(int i=0;i<n;i++)
		scanf("%f",&h_A[i]);

	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
	
	dim3 dimGrid(ceil(n/256.0),1,1);
	dim3 dimBlock(256,1,1);

	vectorSin<<<dimGrid,dimBlock>>>(d_A,d_B,n);
	
	cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);

	printf("Resultant Sin vector:\n");
	for(int i=0;i<n;i++)
		printf("%f\t",h_B[i]);

	cudaFree(d_A);
	cudaFree(d_B);
	return 0;
}
