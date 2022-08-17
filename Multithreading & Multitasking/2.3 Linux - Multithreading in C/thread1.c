#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * work(void * ptr)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("%d", (int)ptr);
		usleep(1000);
	}
	pthread_exit(0);
}

int main(int argc, char ** argv)
{
	pthread_t t0, t1;
	pthread_create(&t0, 0, work, (void *)0);
	pthread_create(&t1, 0, work, (void *)1);

	pthread_join(t0, 0);
	pthread_join(t1, 0);
	return 0;
}
