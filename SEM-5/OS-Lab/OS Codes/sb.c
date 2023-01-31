#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

time_t start;
time_t duration = 5;
time_t end;

int freeseats = 10;
pthread_mutex_t fsm;
sem_t cust, barb;

void *barber(void *params){
    while(start < end){
        start = time(NULL);
        sem_wait(&cust);
        pthread_mutex_lock(&fsm);
        if(freeseats < 10) freeseats++;
        printf("Servicing customer, FS : %d\n", freeseats);
        sleep(1);
        sem_post(&barb);
        pthread_mutex_unlock(&fsm);
    }
}

void *customer(void *params){
    while(start < end)
        if(freeseats > 0) {
            pthread_mutex_lock(&fsm);
            freeseats--;
            printf("Occupied seat, FS : %d\n", freeseats);
            sem_post(&cust);
            sleep(1);
            pthread_mutex_unlock(&fsm);
            sem_wait(&barb);
        }
}

int main(){
    start = time(NULL);
    end = start + duration;
    sem_init(&cust, 0, 0);
    sem_init(&barb, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &barber, NULL);
    pthread_create(&t2, NULL, &customer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}