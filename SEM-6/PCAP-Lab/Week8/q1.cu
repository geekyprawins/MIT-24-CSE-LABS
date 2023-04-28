#include <stdio.h>
#include <cuda_runtime.h>

#define MAX_SENTENCE_LENGTH 100
#define MAX_WORD_LENGTH 10
#define BLOCK_SIZE 128

__global__ void countWordKernel(char* sentence_h, int* wordCount_h, char* word_h) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    while (index < MAX_SENTENCE_LENGTH) {
        int i = 0;
        while (i < MAX_WORD_LENGTH && word_h[i] != '\0' && sentence_h[index + i] == word_h[i]) {
            i++;
        }
        if (i == MAX_WORD_LENGTH || word_h[i] == '\0') {
            atomicAdd(wordCount_h, 1);
        }
        index += stride;
    }
}

int main() {

    char sentence_h[MAX_SENTENCE_LENGTH];
    char word_h[MAX_WORD_LENGTH];
    int wordCount_h;

    printf("Enter a sentence: ");
    scanf("%[^\n]s",sentence_h);
    printf("Enter a word: ");
    scanf("%s", word_h);

    char* sentence_d;
    char* word_d;
    int* wordCount_d;

    cudaMalloc(&sentence_d, MAX_SENTENCE_LENGTH * sizeof(char));
    cudaMalloc(&word_d, MAX_WORD_LENGTH * sizeof(char));
    cudaMalloc(&wordCount_d, sizeof(int));
    
    cudaMemcpy(sentence_d, sentence_h, MAX_SENTENCE_LENGTH * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(word_d, word_h, MAX_WORD_LENGTH * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(wordCount_d, &wordCount_h, sizeof(int), cudaMemcpyHostToDevice);
    
    countWordKernel<<<(MAX_SENTENCE_LENGTH + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE>>>(sentence_d, wordCount_d, word_d);

    cudaMemcpy(&wordCount_h, wordCount_d, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word '%s' appears %d times in the sentence.\n", word_h, wordCount_h);

    cudaFree(sentence_d);
    cudaFree(word_d);
    cudaFree(wordCount_d);

    return 0;

}
