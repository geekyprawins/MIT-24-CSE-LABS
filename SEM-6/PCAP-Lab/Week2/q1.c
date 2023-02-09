#include "mpi.h"
#include <stdio.h>
#include <string.h>
#define MCW MPI_COMM_WORLD

void word_toggle(int word_len, char *word)
{
    for (int i = 0; i < word_len; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] -= 32;
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] += 32;
        }
    }
}

int main(int argc, char *argv[])
{
    int rank, size, word_length;
    char word[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    MPI_Status status;

    if (rank == 0)
    {
        printf("Enter a word in master process:");
        scanf("%s", word);
        word_length = strlen(word);
        MPI_Ssend(&word_length, 1, MPI_INT, 1, 24, MCW);
        MPI_Ssend(word, word_length, MPI_CHAR, 1, 20, MCW);
        fprintf(stdout, "I have sent the word %s from process %d\n", word, rank);
        fflush(stdout);
        MPI_Recv(word, word_length, MPI_CHAR, 1, 22, MCW, &status);
        printf("After toggle word is: %s\n", word);
    }
    else
    {
        MPI_Recv(&word_length, 1, MPI_INT, 0, 24, MCW, &status);
        MPI_Recv(word, word_length, MPI_CHAR, 0, 20, MCW, &status);
        fprintf(stdout, "I have received the word %s in process %d\n", word, rank);
        fflush(stdout);
        word_toggle(word_length, word);
        MPI_Ssend(word, word_length, MPI_CHAR, 0, 22, MCW);
    }

    MPI_Finalize();
    return 0;
}