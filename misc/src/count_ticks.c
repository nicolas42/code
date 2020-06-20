// #include <stdio.h>
// #include <time.h>
#include "count_ticks.h"

double time_elapsed(void){
	return clock()/(double)CLOCKS_PER_SEC;
}

void count_ticks(double max_time){

	double next_print_time = 1.0;
	
	for (int i = 0; i < 1e9; i++)
	{

		/* Print every second */
		if (time_elapsed() > next_print_time){
			next_print_time++;
			printf("%f ", time_elapsed());
			// printf("time_elapsed: %f ticks(): %lu\r\n", time_elapsed(), clock()); 
			fflush(stdout); 
			// protop: some buffers don't flush without a newline
		}

		if (time_elapsed() >= max_time){
			break;
		}
		
	}
}
	

// int main(int argc, char **argv)
// {
// 	puts("Counting ticks...");
// 	count_ticks(double max_time

// 	return 0;
// }

