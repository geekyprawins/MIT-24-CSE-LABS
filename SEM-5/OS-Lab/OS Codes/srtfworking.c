// C++ program to implement Shortest Remaining Time First
// Shortest Remaining Time First (SRTF)
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define INT_MAX 2147483647
struct Process
{
    int pid;         // Process ID
    int burstTime;   // Burst Time
    int arrivalTime; // Arrival Time
};

// Function to find the waiting time for all
// processes
void findWaitingTime(struct Process proc[], int n,
                     int wt[])
{
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].burstTime;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes gets
    // completed
    while (complete != n)
    {
        // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time
        for (int j = 0; j < n; j++)
        {
            if ((proc[j].arrivalTime <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely
        // executed
        if (rt[shortest] == 0)
        {
            // Increment complete
            complete++;
            check = false;

            // Find finish time of current
            // process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time -
                           proc[shortest].burstTime -
                           proc[shortest].arrivalTime;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n,
                        int wt[], int tat[])
{
    // calculating turnaround time by adding
    // burstTime[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burstTime + wt[i];
}

// Function to calculate average time
void findavgTime(struct Process proc[], int n)
{
    int wt[n], tat[n], total_wt = 0,
                       total_tat = 0;

    // Function to find waiting time of all
    // processes
    findWaitingTime(proc, n, wt);

    // Function to find turn around time for
    // all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all
    // details
    printf("P\t\tBT\t\tWT\t\tTAT\t\t\n");

    // Calculate total waiting time and
    // total turnaround time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t %d\t\t %d\t\t %d\t\t\n",
               proc[i].pid, proc[i].burstTime, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f", (float)total_tat / (float)n);
}

// Driver code
int main()
{
    // Burst and then arrival time.
    struct Process proc[] = {{1, 6, 2}, {2, 2, 5}, {3, 8, 1}, {4, 3, 0}, {5, 4, 4}};
    int n = sizeof(proc) / sizeof(proc[0]);

    findavgTime(proc, n);
    return 0;
}