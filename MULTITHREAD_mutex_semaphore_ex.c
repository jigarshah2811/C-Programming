/*
 * semaphore_example.c
 *
 *  Created on: Jul 15, 2016
 *      Author: jigasha2
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#define MAX_THREADS 10000
#define MAX_SHARED_RESOURCES 10000
#define MAX_INC		1000

#ifdef USE_MUTEX
    pthread_mutex_t mylock;
#else
    sem_t mysem[MAX_SHARED_RESOURCES];
    pthread_mutex_t mylock;
#endif

struct shared
{
	int threadId;
	long counter[MAX_SHARED_RESOURCES];
	char msg[10];
};


void* mythread_entry(void *args)
{
	struct shared *SharedCounter = (struct shared*)args;
    int i=0;

    int resource_to_use = SharedCounter->threadId % MAX_SHARED_RESOURCES;
#ifdef USE_MUTEX
        pthread_mutex_lock(&mylock);
#else
		sem_trywait(&mysem[resource_to_use]);
        pthread_mutex_lock(&mylock);
#endif

    for(i=0; i<MAX_INC; i++)
	{
	    sleep(0.001);
		SharedCounter->counter[resource_to_use] += 1;
		//printf("thread %d, counter %d\n", SharedCounter->threadId, SharedCounter->counter[resource_to_use]);
    }

#ifdef USE_MUTEX
		pthread_mutex_unlock(&mylock);
#else
        pthread_mutex_unlock(&mylock);
        sem_post(&mysem[resource_to_use]);
#endif
	
	pthread_exit(NULL);
}

int main()
{
	int i, retCode;

	// Init: Shared-Counter we are going to use across threads
	struct shared *SharedCounter = (struct shared *)malloc(sizeof(struct shared));
	for(i=0; i<MAX_SHARED_RESOURCES; i++)
	{
		SharedCounter->counter[i] = 0;
	}

#ifdef USE_MUTEX
	retCode = pthread_mutex_init(&mylock, NULL);
	if(retCode != 0) printf("mylock failed to init...\n");
#else
    for(i=0; i<MAX_SHARED_RESOURCES; i++)
    {
	    retCode = sem_init(&mysem[i], 0, MAX_THREADS/MAX_SHARED_RESOURCES);
	    if(retCode != 0) printf("mysem failed to init...\n");
    }
	retCode = pthread_mutex_init(&mylock, NULL);
	if(retCode != 0) printf("mylock failed to init...\n");
#endif


	pthread_t mythread[MAX_THREADS];

	for(i=0; i<MAX_THREADS; i++)
	{
		SharedCounter->threadId = i;
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
        //printf("main thread Running\n");
	}

	int finalCounter = 0;
	for(i=0; i<MAX_SHARED_RESOURCES; i++)
	{
		finalCounter = finalCounter + SharedCounter->counter[i];
	}

	printf("Final SharedCounter: %d\t Expected: %d\n", finalCounter, MAX_THREADS*MAX_INC);
#ifdef USE_MUTEX
    pthread_mutex_destroy(&mylock);
#else
    for(i=0; i<MAX_SHARED_RESOURCES; i++)
        sem_destroy(&mysem[i]);

    pthread_mutex_destroy(&mylock);
#endif

	free(SharedCounter);
	return 0;

}



