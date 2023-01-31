#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int max[10];
    int alloc[10];
    int need[10];
    int pid;
    bool completed;
} process;

int main()
{
    process p[10];
    int n;
    int resources;
    int available[10];
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter number of resources: ");
    scanf("%d", &resources);
    for (int i = 0; i < n; i++)
    {
        p[i].completed = false;
        printf("\nEnter max:");
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &p[i].max[j]);
        }
        printf("\nEnter alloc:");
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &p[i].alloc[j]);
        }
        // Calculating need.
        for (int j = 0; j < resources; j++)
        {
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
        }
    }
    // Print the need matrix:
    printf("\nNeed matrix:");
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < resources; j++)
        {
            printf("%d ", p[i].need[j]);
        }
    }
    printf("\n Enter available resources: ");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
    }
    // Calculating safe sequence.
    int safe_sequence[10];
    int index = 0;
    int completed = 0;
    while (true)
    {
        int temp = completed;
        for (int i = 0; i < n; i++)
        {
            int flag = 0;
            for (int j = 0; j < resources; j++)
            {
                if (p[i].need[j] > available[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag && p[i].completed == false)
            {
                // Add to safe sequence.
                safe_sequence[index++] = i;
                for (int j = 0; j < resources; j++)
                {
                    available[j] += p[i].alloc[j];
                }
                completed += 1;
                p[i].completed = true;
            }
            if (completed == n)
            {
                // Print safety sequence, also need to print table at the end.
                printf("\nSafety sequence is:");
                for (int j = 0; j < n; j++)
                {
                    printf("%d ", safe_sequence[j]);
                }
                exit(0);
            }
        }
        if (completed == temp)
        {
            int end = false;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < resources; j++)
                {
                    if (p[i].need[j] > available[j] && p[i].completed == false)
                    {
                        printf("\nDeadlocked state: !");
                        end = true;
                        printf("P%d ", i);
                        break;
                    }
                }
            }
            if (end == false)
            {
                exit(0);
            }
        }
    }

    return 0;
}