#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdint.h>

#define BASIC_IMPLEMENTATION
#include "basic.h"





int prime_sieve( uint64_t candidate, List primes )
{
    for (uint64_t i=0; i<primes.length; i++){
        if ( candidate % (uint64_t)primes.data[i] == 0) return 0;
    }
    return 1;
}


List simple_make_primes()
{
    List primes = make_list();
    primes = append_list( primes, (void*)2 );
    uint64_t i;

	for (i=3;i<100*1000;i+=2){
		if ( prime_sieve(i, primes) ) {
            primes = append_list( primes, (void*)i );
        }
    }
    for(i=0;i<primes.length;++i) printf("%llu ", (uint64_t)primes.data[i]);

    return primes;
}




static int stop_making_primes = 0;

void signal_handler(int signal)
{
    if (signal == SIGINT){
        // fclose(file);
        printf("\nYou handled the SIGINT!\n");
        stop_making_primes = 1;
    }
}

// Does a signal flag global need to be atomic?
// ------------------------------------------------

// static int sigflag = 0;
// sig_atomic_t sigflag = 0;
// sig_atomic_t is an integer type which can be accessed as an atomic entity even in the presence of asynchronous interrupts made by signals.
// could I just use a mutex?
// It appears that atomic things are more efficient than mutexes

// "Atomic operations leverage processor support (compare and swap instructions) and don't use locks at all, whereas locks are more OS-dependent and perform differently on, for example, Win and Linux.
// Locks actually suspend thread execution, freeing up cpu resources for other tasks, but incurring in obvious context-switching overhead when stopping/restarting the thread. On the contrary, threads attempting atomic operations don't wait and keep trying until success (so-called busy-waiting), so they don't incur in context-switching overhead, but neither free up cpu resources.
// Summing up, in general atomic operations are faster if contention between threads is sufficiently low. You should definitely do benchmarking as there's no other reliable method of knowing what's the lowest overhead between context-switching and busy-waiting."
// https://stackoverflow.com/questions/15056237/which-is-more-efficient-basic-mutex-lock-or-atomic-integer



      
// sieve some primes and write them to the file
// read primes from file if it already exists
List make_primes(const char *filename)
{
    // register signal handler
    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { printf("\nERROR %s %d registering signal handler\n",__FILE__,__LINE__); }

    List p = make_list(); // primes
    FILE *file;
    int i;

    // if file exists then read the numbers from it,
    // otherwise create a new file and add 2 and 3 to start off.
    // 2 and 3 are needed since the program starts from the last
    // prime in the list and jumps in twos to the next candidate number.
    if ( file_exists(filename)) {
        char *str;
        List list;
        str = read_file(filename);
        list = split_string(str, " ");
        for (i=0;i<list.length;i++) {
            uint64_t tmp;
            sscanf((char*)list.data[i], "%llu", &tmp);
            p = append_list( p, (void*)tmp );
        }

        // for (i=0;i<list.length;i++) { printf("%llu ", (uint64_t)(p.data[i])); }
        // printf("\n");

    } else {
        p = append_list( p, (void*)2 );
        p = append_list( p, (void*)3 );
        file = fopen(filename, "a");
        fprintf(file, "%llu %llu ", (uint64_t)(2), (uint64_t)(3));
        fclose(file);
    }

    double t0 = time_elapsed();

    uint64_t limit = (uint64_t)p.data[p.length-1] + 1000*1000;
    file = fopen(filename, "a");

    printf("Prime numbers\n");
    printf("----------------\n");
    printf("Outputting results to %s\n", filename);
    printf("\rlast prime generated: %llu", (uint64_t)(p.data[p.length-1]));
    fflush(stdout);

	for (uint64_t j = (uint64_t)(p.data[p.length-1]); j < limit; j += 2 ) {
        if (stop_making_primes) { stop_making_primes = 0; return p; }
		if ( prime_sieve(j, p) ) {
            p = append_list( p, (void*)j );

            fprintf(file, "%llu ", j);
		}
        // every second print the last prime that was found.
        if ( time_elapsed()-t0 >= 1 ){
			t0 = time_elapsed();
		    printf("\rlast prime generated: %llu", (uint64_t)(p.data[p.length-1]));
            fflush(stdout);
        }
	}
    return p;
}



int main()
{
  //    simple_make_primes();
    make_primes("primes.txt");
    return 0;
}



