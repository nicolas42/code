#include <time.h>

double time_elapsed(){
	return clock()/(double)CLOCKS_PER_SEC;
}
