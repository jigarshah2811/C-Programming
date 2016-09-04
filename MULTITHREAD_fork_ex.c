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
#include <sys/types.h>

#define MAX_THREADS 1

void childProcess()
{
    char *filename = "/local/jigasha2/counter";
    FILE *fp = fopen(filename, "w+");
    int buffer;

    fread(&buffer, sizeof(int), 1, fp);
    buffer++;
    fwrite(&buffer, sizeof(int), 1, fp);

    fclose(fp);
    exit(0);
}


int main()
{
	int i = -1;
    int retCode = 0;

    pid_t pid[MAX_THREADS];
   
    
   while(1)
   { 
        pid[i++] = fork();
        if(pid[i] == 0)
        {
            //CHILD
            childProcess();
        }
        else
        { 
            //MAIN
            if(i>=MAX_THREADS)
                break;
        }
   }

                // ALL CHILD PROCESSES DONE
            
	            //printf("Final SharedCounter: %d\t Expected: %d\n", finalCounter, MAX_THREADS*MAX_INC);
                   return 0;
}
