#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cond;

int how_many = 10;
int pool = 0;

void * producer(void * ptr)
{
	while (how_many > 0)
	{
		pthread_mutex_lock(&mtx);
		printf("producer: %d\n", how_many);
		pool = how_many;
		how_many--;
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cond);
	}
	pthread_exit(0);
}

void * consumer(void * ptr)
{
	while (how_many > 0)
	{
		pthread_mutex_lock(&mtx);
		pthread_cond_wait(&cond, &mtx);
		printf("consumer: %d\n", pool);
		pool = 0;
		pthread_mutex_unlock(&mtx);
	}
	pthread_exit(0);
}

int main(int argc, char ** argv)
{
	pthread_t prod, cons;
	pthread_mutex_init(&mtx, 0);
	pthread_cond_init(&cond, 0);
	pthread_create(&cons, 0, consumer, 0);
	pthread_create(&prod, 0, producer, 0);
	pthread_join(prod, 0);
	pthread_join(cons, 0);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);	
	return 0;
}
