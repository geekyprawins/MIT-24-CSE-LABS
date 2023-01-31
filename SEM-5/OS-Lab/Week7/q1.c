#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int buf[5], f = 0, r = 0;
sem_t mutex_sem, end, start;

void *produce(void *arg)
{
	sem_wait(&start);
	for (int i = 0; i < 10; i++)
	{

		sem_wait(&mutex_sem);

		printf("Produced Item is : %d\n", i);

		buf[(++r) % 10] = i;
		sleep(1);

		sem_post(&mutex_sem);
	}
	sem_post(&end);
}

void *consume(void *arg)
{
	sem_wait(&end);
	int item;
	for (int i = 0; i < 10; i++)
	{

		sem_wait(&mutex_sem);

		item = buf[(++f) % 10];
		printf("Consumed Item is : %d\n", item);
		sleep(1);

		sem_post(&mutex_sem);
	}
	sem_post(&start);
}

int main()
{
	pthread_t t1, t2;
	sem_init(&mutex_sem, 0, 1);
	sem_init(&end, 0, 0);
	sem_init(&start, 0, 10);
	pthread_create(&t1, NULL, &produce, NULL);
	pthread_create(&t2, NULL, &consume, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}