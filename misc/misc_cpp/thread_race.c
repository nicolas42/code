// Demo
// gcc thread_race.c && ./a.out

#define num_threads 1000

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int global = 0;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add1_to_global(void* arg)
{
	// pthread_mutex_lock(&mutex);
	global += 1;
	// pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

int main()
{

	printf("1000 threads adding 1 to a global. Who will win the race?\n");

	for (int i = 0; i < 1e6; i++){
		
		printf("Race %d: ", i);

		global = 0;
		// Launch threads
		pthread_t tids[num_threads];
		for (int i = 0; i < num_threads; i++) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&tids[i], &attr, add1_to_global, NULL);
		}

		// Wait for threads
		for (int i = 0; i < num_threads; i++) {
			pthread_join(tids[i], NULL);
		}

		printf("Result is %d\n", global);
		if (global != num_threads){ break; }
	}

}
