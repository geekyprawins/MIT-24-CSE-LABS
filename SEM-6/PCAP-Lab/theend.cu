#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
__global__ void calc(char* a, char* res, int* s, int n, char dir){
  int bi = blockIdx.x, j = threadIdx.x, i = threadIdx.y, tid = i * 2 + j, first = s[bi], last = s[bi + 1], size = last - first - 1, m = n % size;
  res[first + size] = ' ';
  if(dir == 'R' && tid < size) res[first + tid] = a[first + (tid - m + size) % size];
  if(dir == 'L' && tid < size) res[first + tid] = a[first + (tid + m) % size];
}
int main(){
  char a[100], *d_a, res[100], *d_res, dir;
  int n;
  printf("Enter the sentence: ");
  fgets(a, sizeof(a), stdin); // need to give an extra space along with the last word in the sentence.
  printf("Enter the direction: ");
  scanf("%c", &dir);
  printf("Enter the value of n: ");
  scanf("%d", &n);
  int st[100], len = 0, i = 0, *d_st, maxi = 0;
  st[0] = 0;
  for(; a[len] != '\n'; len++){
    if(a[len] == ' '){
      st[++i] = len + 1;
      printf(": %d\n", st[i] - st[i - 1] - 1);
      if(maxi < st[i] - st[i - 1] - 1) maxi = st[i] - st[i - 1] - 1;
    }
    else printf("%c", a[len]);
  }
  printf("Largest word length is: %d\n", maxi);
  cudaMalloc((void**)&d_a, sizeof(char) * len);
  cudaMalloc((void**)&d_res, sizeof(char) * len);
  cudaMalloc((void**)&d_st, sizeof(int) * (i + 1));
  cudaMemcpy(d_a, &a, sizeof(char) * len, cudaMemcpyHostToDevice);
  cudaMemcpy(d_st, &st, sizeof(int) * (i + 1), cudaMemcpyHostToDevice);
  dim3 bl(2, maxi / 2 + (maxi % 2 > 0));
  calc<<<i, bl >>> (d_a, d_res, d_st, n, dir);
  cudaMemcpy(&res, d_res, sizeof(char) * len, cudaMemcpyDeviceToHost);
  res[len] = '\0';
  printf("Resultant string is %s\n", res);
  cudaFree(d_st);
  cudaFree(d_a);
  cudaFree(d_res);
  return 0;
}