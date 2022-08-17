#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
 
pthread_mutex_t mtx;

void print(int thread, int i)
{
	pthread_mutex_lock(&mtx);
	printf("thread %d: %d\n", thread, i);
	pthread_mutex_unlock(&mtx);
}

void * work(void * ptr)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		print((int)ptr, i);
		usleep(1000);
	}
	pthread_exit(0);
}

int main(int argc, char ** argv)
{
	pthread_t t0, t1;

	pthread_mutex_init(&mtx, 0);
	pthread_create(&t0, 0, work, (void *)0);
	pthread_create(&t1, 0, work, (void *)1);

	pthread_join(t0, 0);
	pthread_join(t1, 0);

	pthread_mutex_destroy(&mtx);
	return 0;
}
