// g++ make_primes.cpp && ./a.out

#include "basic.h"

DEFINE_ARRAY(u64)
DEFINE_ARRAY(u8)


int prime_sieve( uint64_t candidate, u64_array primes )
{
    for (uint64_t i=0; i<primes.length; i++){
        if ( candidate % primes.data[i] == 0) return 0;
    }
    return 1;
}


u64_array make_primes( int num_to_make )
{
    u64_array primes = u64_array_make();
    primes = u64_array_add( primes, 2 );
    uint64_t i;

	for ( i=3; i < num_to_make; i+=2){
		if ( prime_sieve(i, primes) ) {
            primes = u64_array_add( primes, i );
        }
    }
    for(i=0;i<primes.length;++i) printf("%llu ", primes.data[i]);

    return primes;
}




static sig_atomic_t sigint_flag = 0;

void signal_handler(int signal)
{
    if (signal == SIGINT){
        // fclose(file);
        printf("\nYou handled the SIGINT!\n");
        sigint_flag = 1;
    }
}
      
// sieve some primes and write them to the file
// read primes from file if it already exists
u64_array make_primes_with_file(const char *filename)
{
    // register signal handler
    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { 
        printf("\nERROR %s %d registering signal handler\n",__FILE__,__LINE__); 
    }

    u64_array primes = u64_array_make();
    int i;

    // if file exists then read the numbers from it,
    // otherwise create a new file and add 2 and 3 to start off.

    // 2 and 3 are needed since the program starts from the last
    // prime in the list and jumps in twos to the next candidate number.

    FILE *file = fopen(filename, "r");
    if (file){

        fseek(file, 0, SEEK_END); // seek to end of file
        int size = ftell(file);   // get current file pointer
        fseek(file, 0, SEEK_SET); // seek back to beginning of file
        char *str = (char*)malloc(size * sizeof(char));
        fread(str, size, 1, file);
        fclose(file);

        char *pos1 = str;
        char *pos2;
        long ret;

        while (1){
            ret = strtol(pos1, &pos2, 10);
            if (!ret) break;
            pos1 = pos2;
            // printf("The number(unsigned long integer) is %ld\n", ret);
            primes = u64_array_add( primes, (u64)ret );
        }

    } else {
        primes = u64_array_add( primes, 2 );
        primes = u64_array_add( primes, 3 );
        file = fopen(filename, "a");
        fprintf(file, "%llu %llu ", (uint64_t)(2), (uint64_t)(3));
        fclose(file);

    }



    printf("Prime numbers\n");
    printf("----------------\n");
    printf("Outputting results to %s\n", filename);
    printf("\rlast prime generated: %llu", (uint64_t)(primes.data[primes.length-1]));
    fflush(stdout);

    time_t t0 = clock();

    uint64_t limit = (uint64_t)primes.data[primes.length-1] + 1000*1000;
    file = fopen(filename, "a");

	for (uint64_t j = (uint64_t)(primes.data[primes.length-1]); j < limit; j += 2 ) {
        if (sigint_flag) { 
            sigint_flag = 0; 
            return primes; 
        }
		if ( prime_sieve(j, primes) ) {
            primes = u64_array_add( primes, j );

            fprintf(file, "%llu ", j);
		}
        // every second print the last prime that was found.
        float time_elapsed = ( clock() - t0 ) / CLOCKS_PER_SEC;
        if ( time_elapsed >= 1.0 ){
			t0 = clock();
		    printf("\rlast prime generated: %llu", (uint64_t)(primes.data[primes.length-1]));
            fflush(stdout);
        }
	}
    return primes;
}






int main()
{
    make_primes(100*1000);
    // make_primes_with_file("primes_gitignore.txt");

    return 0;
}



