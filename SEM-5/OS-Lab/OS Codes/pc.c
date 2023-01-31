#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t mutex, full, empty;
int start = 0, end = 0, buff[10];

void *produce(void *params){
    for(int i = 0; i < 10; i++){
        sem_wait(&empty);
        sem_wait(&mutex);
        buff[(++end)%10] = i;
        printf("\nItem produced is : %d", i);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consume(void *params){
    for(int i = 0; i < 10; i++){
        sem_wait(&full);
        sem_wait(&mutex);
        printf("\nItem read is : %d", buff[(++start)%10]);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main(){
    pthread_t t1, t2;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    pthread_create(&t1, NULL, &produce, NULL);
    pthread_create(&t2, NULL, &consume, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}