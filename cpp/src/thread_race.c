// gcc lock_demo.c && ./a.out 1000
// This script has a lot of threads modifying a single global
// It can be configured to lock the modify using
	// #define FUNCTION add1
	// #define FUNCTION add1_locked

// Demo
// gcc lock_demo.c && ./a.out 1000
// launches 1000 threads

// You might have to try it multiple times to see that 
// the result doesn't always equal the number of threads
//


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int thread_race_global_variable = 0;
// static pthread_mutex_t thread_race_mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_race_add1_to_global_variable(void* arg)
{
	// pthread_mutex_lock(&thread_race_mutex);
	thread_race_global_variable += 1;
	// pthread_mutex_unlock(&thread_race_mutex);
	pthread_exit(0);

}

void thread_race_main(void)
{
	#define num_threads 1000

	printf("1000 threads adding 1 to a global. Who will win the race?\n");

	for (int i = 0; i < 1e6; i++){
		
		printf("Race %d: ", i);

		thread_race_global_variable = 0;
		// Launch threads
		pthread_t tids[num_threads];
		for (int i = 0; i < num_threads; i++) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&tids[i], &attr, thread_race_add1_to_global_variable, NULL);
		}

		// Wait for threads
		for (int i = 0; i < num_threads; i++) {
			pthread_join(tids[i], NULL);
		}

		printf("Result is %d\n", thread_race_global_variable);
		if (thread_race_global_variable != num_threads){ break; }
	}

	#undef num_threads
}
