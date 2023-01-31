#include<stdio.h>

int bursttime[5] = {40, 90, 80, 15, 100};
int priority[5] = {3, 2, 5, 1, 4};

int times[5], priors[5];
int shortest, highprior, proc;

void init(){
    for(int i = 0; i < 5; i++) times[i] = bursttime[i], priors[i] = priority[i];
}

void FCFS(){
    printf("\nFCFS\n");
    for(int i = 0; i < 5; i++)
        printf("Processing %d with bursttime %d\n", i+1, bursttime[i]);
}

void SST(){
    shortest = 1000;
    for(int i = 0; i < 5; i++)
        if(times[i] < shortest) shortest = times[i], proc = i;
    times[proc] = 1001;
}

void SSTF(){
    printf("\nSSTF\n");
    init();
    for(int i = 0; i < 5; i++){
        SST();
        printf("Processing %d with bursttime %d\n", proc+1, shortest);
    }
}

void highpriority(){
    highprior = 0;
    for(int i = 0; i < 5; i++)
        if(priors[i] > highprior) highprior = priors[i], proc = i;
    priors[proc] = -1;
}

void Priority(){
    printf("\nPriority Scheduling\n");
    init();
    for(int i = 0; i < 5; i++){
        highpriority();
        printf("Processing %d with priority %d\n", proc+1, highprior);
    }
}

void RoundRobin(){
    printf("\nRound Robin\n");
    printf("Operating with burst time = 10 units\n");
    init();
    int stop = 0;
    while(!stop){
        stop = 1;
        for(int i = 0; i < 5; i++){
            if(times[i] <= 0) continue;
            stop = 0;
            printf("Processing %d with bursttime %d leaving remaning %d\n", i+1, times[i], times[i]-10 > 0 ? times[i] - 10 : 0);
            times[i] -= 10;
        }
    }
}

int main(){
    printf("\nWelcome to Shyam's short and sweet demo of CPU Scheduling Algos.\n");
    FCFS();
    SSTF();
    Priority();
    RoundRobin();
}