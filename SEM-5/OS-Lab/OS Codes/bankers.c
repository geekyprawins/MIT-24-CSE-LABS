#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int av[10], max[10][10], alloc[10][10], need[10][10], work[10], finish[10], pro, res;
void bankers()
{
    memset(finish, 0, sizeof(finish));
    for (int i = 0; i < res; i++)
    {
        // scanf("%d",&av[i]);
        work[i] = av[i];
    }
    int ctr = 0;
    int ss[100] = {0};
    while (ctr < pro)
    {
        int fl = 0;
        for (int i = 0; i < pro; i++)
        {
            int fl2 = 1;
            if (finish[i] == 0)
            {
                for (int j = 0; j < res; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        fl2 = 0;
                        break;
                    }
                }
                if (fl2)
                {
                    for (int j = 0; j < res; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    ss[ctr] = i;
                    ctr++;
                    fl = 1;
                }
            }
        }
        if (fl == 0)
        {
            printf("No safety sequence\n");
            exit(0);
        }
        else if (pro == ctr)
        {
            printf("Safety sequence is\n");
            for (int i = 0; i < pro; i++)
            {
                printf("%d ", ss[i]);
            }
            return;
        }
    }
}
void request()
{
    int x;
    printf("\nEnter which process wants resources\n");
    scanf("%d", &x);
    printf("Enter request vector\n");
    int req[10];
    for (int i = 0; i < res; i++)
    {
        scanf("%d", &req[i]);
        if (req[i] > need[x][i])
        {
            printf("Request exceeds max need\n");
            exit(0);
        }
        if (req[i] > av[i])
        {
            printf("Process must Wait\n");
            exit(0);
        }
    }
    for (int i = 0; i < res; i++)
    {
        alloc[x][i] += req[i];
        need[x][i] -= req[i];
        av[i] -= req[i];
    }
    bankers();
}
int main()
{
    printf("Enter number of processes and resources\n");
    scanf("%d", &pro);
    scanf("%d", &res);
    printf("Enter Available, Max, Allocation\n");
    for (int i = 0; i < res; i++)
    {
        scanf("%d", &av[i]);
        work[i] = av[i];
    }
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\nAvailable matrix is\n");
    for (int i = 0; i < res; i++)
    {
        printf("%d ", av[i]);
    }
    printf("\nMax matrix is\n");
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    printf("\nAllocation matrix is\n");
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }
    printf("\nNeed matrix is\n");
    for (int i = 0; i < pro; i++)
    {
        for (int j = 0; j < res; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    bankers();
    request();
}