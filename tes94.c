#include <pthread.h>

#include <stdio.h>

void show(int thread)
{
	printf("thread: %d\n", thread);
}

void *work(void *arg)
{
	int *x;
	x=arg;
	printf("%d %d\n", x[0], x[1]);
}

int main(int argc, char **argv)
{
	int x[2];
	int i;
	pthread_t thread;
	for(i=0; i<4; i++)
	{
		x[0] = i;
		x[1] = getpid();
		pthread_create(&thread, NULL, work, &x);
	}
	
	pthread_join(thread, NULL);
	return 0;
}
