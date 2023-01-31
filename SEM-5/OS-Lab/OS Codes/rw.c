#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t nreadlock;
sem_t wrt;
int nread = 0;
int written = 0;

void *write1(void *param){
    sem_wait(&wrt);
    written++;
    printf("Writer has written %d\n", written);
    sem_post(&wrt);
}

void *read1(void *param){
    pthread_mutex_lock(&nreadlock);
    nread++;
    if(nread == 1) sem_wait(&wrt);
    pthread_mutex_unlock(&nreadlock);
    printf("Reader has read %d\n", written);
    pthread_mutex_lock(&nreadlock);
    nread--;
    if(nread == 0) sem_post(&wrt);
    pthread_mutex_unlock(&nreadlock);
}

int main(){
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&nreadlock, NULL);
    pthread_t t[6];
    for(int i = 0; i < 3; i++) pthread_create(&t[i], NULL, &write1, NULL);
    for(int i = 0; i < 3; i++) pthread_create(&t[i+3], NULL, &read1, NULL);
    for(int i = 0; i < 3; i++) pthread_join(t[i], NULL);
    for(int i = 0; i < 3; i++) pthread_join(t[i+3], NULL);
    return 0;
}

