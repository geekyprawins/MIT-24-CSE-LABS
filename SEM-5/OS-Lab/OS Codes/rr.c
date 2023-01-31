#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n, total = 0, checker = 0, y, time_quantum, waiting_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], keep[10], temp[10];
    float avg_wt, avg_tat;                      // average waiting time, average turnaround time
    printf("Enter the number of processes : "); // no. of processes
    scanf("%d", &n);
    y = n; // temporary storage

    // details of every process
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf("Arrival time is: ");
        scanf("%d", &arrival_time[i]);
        temp[i] = i;
        printf("Burst time is: ");
        scanf("%d", &burst_time[i]);
        keep[i] = burst_time[i]; // keeping track of burst time in a temporary array
    }
    printf("\nEnter the time quantum for the process: ");
    scanf("%d", &time_quantum);

    for (i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                int temp1 = arrival_time[j]; // swapping all the parameters
                int temp2 = burst_time[j];
                int temp3 = temp[j];
                arrival_time[j] = arrival_time[j + 1];
                burst_time[j] = burst_time[j + 1];
                temp[j] = temp[j + 1];
                arrival_time[j + 1] = temp1;
                burst_time[j + 1] = temp2;
                temp[j + 1] = temp3;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        keep[i] = burst_time[i]; // keeping track of burst time in a temporary array
    }

    // table obtained from gantt chart
    printf("\nProcesses \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ");
    total = 0;
    i = 0;
    while (y != 0)
    {
        if (keep[i] == 0)
        {
            i++;
            if (i == n)
            {
                i = 0;
            }
            continue;
        }
        else if (keep[i] <= time_quantum && keep[i] > 0)
        {
            total = total + keep[i];
            keep[i] = 0;
            y--; // decrement the number of processes
            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", temp[i] + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
            waiting_time = waiting_time + total - arrival_time[i] - burst_time[i];
            turnaround_time = turnaround_time + total - arrival_time[i];
            i++;
        }
        else
        {
            keep[i] = keep[i] - time_quantum;
            total = total + time_quantum;
            i++;
        }

        if (i == n)
        {
            i = 0;
        }
    }

    avg_wt = waiting_time * 1.0 / n;
    avg_tat = turnaround_time * 1.0 / n;
    printf("\n\nAverage Turn Around Time: %f", avg_tat);
    printf("\nAverage Waiting Time: %f\n", avg_wt);
    return 0;
}