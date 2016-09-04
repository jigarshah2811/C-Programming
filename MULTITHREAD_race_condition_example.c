#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_THREADS 100
#define MAX_INC		1000

pthread_mutex_t lock;

struct shared
{
	int counter;
	char msg[10];
};

uint64_t gettid() {
    pthread_t ptid = pthread_self();
    return (uint64_t) ptid;
}

void* mythread_entry(void *args)
{
	struct shared *SharedCounter = (struct shared*)args;
	
	for(int i=0; i<MAX_INC; i++)
	{
		pthread_mutex_lock(&lock);
		SharedCounter->counter += 1;
		//printf("thread %llu, counter %d\n", gettid(), SharedCounter->counter);
		pthread_mutex_unlock(&lock);
	}
	
	pthread_exit(NULL);
}

int main()
{
	int i, retCode;

	struct shared *SharedCounter = (struct shared *)malloc(sizeof(struct shared));
	retCode = pthread_mutex_init(&lock, NULL);
	if(retCode != 0) printf("Lock failed");
	
	pthread_t mythread[MAX_THREADS];
	
	for(i=0; i<MAX_THREADS; i++)
	{
		retCode = pthread_create(&mythread[i], NULL, &mythread_entry, SharedCounter);
		if(retCode == -1)
		{
			printf("Thread_create failed");
			return -1;
		}
	}

	for( i=0; i<MAX_THREADS; i++)
	{
		pthread_join(mythread[i], NULL);
		printf("main says Running\n");
	}
	
	printf("Final SharedCounter: %d\t Expected: %d\n", SharedCounter->counter, MAX_THREADS*MAX_INC);
	free(SharedCounter);
	pthread_mutex_destroy(&lock);
	
	return 0;
		
}