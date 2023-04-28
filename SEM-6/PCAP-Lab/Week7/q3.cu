#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void Convolution_1D(float *N, float *M,float *P,int width,int mask_width)
{
	int tid=blockIdx.x*blockDim.x+threadIdx.x;
	float pValue=0;
	int startPoint= tid - (mask_width/2);

	for(int j=0;j<mask_width;j++)
	{
		if((startPoint+j>=0)&&(startPoint+j<width))
			pValue+=N[startPoint+j]*M[j];
	}
	P[tid]=pValue;
}

int main(void) 
{
	int width,mask_width;

	printf("Enter width:\t");
	scanf("%d",&width);

	printf("Enter mask_width:\t");
	scanf("%d",&mask_width);

	float *h_N,*h_P,*h_M;
	float *d_N,*d_P,*d_M;

	h_N=(float*)malloc(sizeof(float)*width);
	h_P=(float*)malloc(sizeof(float)*width);
	h_M=(float*)malloc(sizeof(float)*mask_width);

	cudaMalloc((void **)&d_N,sizeof(float)*width);
	cudaMalloc((void **)&d_P,sizeof(float)*width);
	cudaMalloc((void **)&d_M,sizeof(float)*mask_width);

	printf("Enter N:\n");
	for(int i=0;i<width;i++)
		scanf("%f",&h_N[i]);

	printf("Enter M:\n");
	for(int i=0;i<mask_width;i++)
		scanf("%f",&h_M[i]);


	cudaMemcpy(d_N, h_N,sizeof(float)*width, cudaMemcpyHostToDevice);
	cudaMemcpy(d_M, h_M,sizeof(float)*mask_width, cudaMemcpyHostToDevice);
	
	dim3 dimGrid(ceil(width/256.0),1,1);
	dim3 dimBlock(256,1,1);

	Convolution_1D<<<dimGrid,dimBlock>>>(d_N,d_M,d_P,width,mask_width);
	
	cudaMemcpy(h_P, d_P,sizeof(float)*width, cudaMemcpyDeviceToHost);

	printf("Resultant P:\n");
	for(int i=0;i<width;i++)
		printf("%f\t",h_P[i]);

	cudaFree(d_N);
	cudaFree(d_P);
	cudaFree(d_M);
	return 0;
}
