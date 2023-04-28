#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void pattern(char *str, char *ans, int len)
{
	int tid=blockIdx.x;
	int idx = (len*(len+1)/2) - ((len-tid)*(len+1-tid)/2);
	for(int i=0; i<(len-tid); i++)
		ans[idx+i] = str[i];
}

int main(void) {
    char str_h[10], *str_d;
	char *ans_h, *ans_d;
    printf("Enter the string: ");
    scanf("%s", str_h);
    int len = strlen(str_h);
	ans_h = (char*)malloc(((len*(len+1))/2)*sizeof(char));	
	cudaMalloc((void **)&str_d, len*sizeof(char));
	cudaMalloc((void **)&ans_d, ((len*(len+1))/2)*sizeof(char));
	cudaMemcpy(str_d, str_h, len*sizeof(char), cudaMemcpyHostToDevice);
	pattern<<<len,1>>>(str_d, ans_d, len);
	cudaMemcpy(ans_h, ans_d, ((len*(len+1))/2)*sizeof(char), cudaMemcpyDeviceToHost);
	printf("Final string is: %s.\n", ans_h);
	cudaFree(str_d);
	cudaFree(ans_d);
	return 0;
}