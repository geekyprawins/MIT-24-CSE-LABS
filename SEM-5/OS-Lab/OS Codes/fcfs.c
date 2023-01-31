#include <stdio.h>
#include <math.h>
#include <string.h>
int waitingTime[100], arrivalTime[100], burstTime[100], turnaroundTime[100], n, p[100];
float averageWaitingTime[5], averageTurnaroundTime[5];
int temp1, temp2, temp3, sqt, avg;
void fcfs()
{
    waitingTime[0] = 0;
    averageTurnaroundTime[0] = turnaroundTime[0] = burstTime[0];
    int btt = burstTime[0];
    int i;
    for (i = 1; i < n; i++)
    {
        waitingTime[i] = btt - arrivalTime[i];
        btt += burstTime[i];
        averageWaitingTime[0] += waitingTime[i];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
        averageTurnaroundTime[0] += turnaroundTime[i];
    }
    averageTurnaroundTime[0] /= n;
    averageWaitingTime[0] /= n;
    printf("SR.\tA.T.\tB.T.\tW.T.\tT.A.T.\n");
    for (i = 0; i < n; i++)
    {
        printf("%3d\t%3d\t%3d\t%3d\t%4d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
}
void input()
{
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
        p[i] = i + 1;
    for (i = 0; i < n; i++)
    {
        printf("Enter Burst Time of process %d:", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Enter Arrival Time of process %d:", i + 1);
        scanf("%d", &arrivalTime[i]);
    }
    for (i = 0; i < 5; i++)
    {
        averageWaitingTime[i] = 0.0;
        averageTurnaroundTime[i] = 0.0;
    }
}
void changeArrival()
{
    int a = arrivalTime[0];
    int i;
    for (i = 0; i < n; i++)
    {
        if (arrivalTime[i] < a)
            a = arrivalTime[i];
    }
    if (a != 0)
    {
        for (i = 0; i < n; i++)
            arrivalTime[i] = arrivalTime[i] - a;
    }
}
void display(int c)
{
    int i;
    printf("Average Waiting time:%f\nAverage Turn Around Time:%f\n", averageWaitingTime[c - 2], averageTurnaroundTime[c - 2]);
}
int main()
{
    char c;
    printf("\t\t***Welcome to CPU Scheduling***\n\n");
    input();
    fcfs();
    display(2);
}