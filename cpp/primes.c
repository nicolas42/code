#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "types.h"


typedef struct list {
  void** data;
  int length;
  int allocated;
} List;

List make_list()
{
    List l;
    l.length = 0;
    l.allocated = 10;
    l.data = (void**)malloc( l.allocated * sizeof(void*) );
    return l;
}

List append_list(List l, void* str)
{
    l.data[l.length] = str;
    l.length += 1;
    if ( l.length == l.allocated ) {
      l.allocated *= 2;
      l.data = (void**)realloc( l.data, l.allocated * sizeof(void*) );
    }
    return l;
}

List split_string(char *str, char delim)
{
    // convert spaces to null bytes
    size_t string_length = strlen(str);
    int i=0;
    for (i=0;i<string_length;i++) if (str[i]==delim) str[i] = '\0';

    // note down stuff after null bytes
    List l = make_list();
    if ( str[0] != '\0' ) l = append_list(l, str);
    for (i=1; i<string_length; i++ ) {
        if ( str[i-1] == '\0' && str[i] != '\0' ) l = append_list(l, str+i);
    }
    return l;
}

char* read_file(char *filename)
{
    char *str;
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f);   // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    str = (char*)malloc(size * sizeof(char));
    fread(str, size, 1, f);
    fclose(f);

    return str;
}


int file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    file = fopen(filename, "r");
    if (file){
        fclose(file);
        return 1;
    }
    return 0;
}

double time_elapsed(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}








int prime_sieve( u64 candidate, List primes )
{
    for (u64 i=0; i<primes.length; i++){
        if ( candidate % (u64)primes.data[i] == 0) return 0;
    }
    return 1;
}


List simple_make_prime_numbers()
{
    List primes = make_list();
    primes = append_list( primes, (void*)2 );
    u64 i;

	for (i=3;i<100*1000;i+=2){
		if ( prime_sieve(i, primes) ) {
            primes = append_list( primes, (void*)i );
        }
    }
    for(i=0;i<primes.length;++i) printf("%llu ", (u64)primes.data[i]);

    return primes;
}

void signal_handler(int signal)
{
    if (signal == SIGINT){
        // fclose(file);
        printf("\nreceived SIGINT\n");
        exit(0);
    }
}


      
// sieve some primes and write them to the file
// read primes from file if it already exists
List make_prime_numbers(char *filename)
{
    // register signal handler
    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { printf("\nERROR registering signal handler\n"); }

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
        list = split_string(str, ' ');
        for (i=0;i<list.length;i++) {
            u64 tmp;
            sscanf((char*)list.data[i], "%llu", &tmp);
            p = append_list( p, (void*)tmp );
        }
        for (i=0;i<list.length;i++) { printf("%llu ", (u64)(p.data[i])); }
        printf("\n");
    } else {
        p = append_list( p, (void*)2 );
        p = append_list( p, (void*)3 );
        file = fopen(filename, "a");
        fprintf(file, "%llu %llu ", (u64)(2), (u64)(3));
        fclose(file);
    }

    double t0 = time_elapsed();

    u64 limit = (u64)p.data[p.length-1] + 1000*1000;
    file = fopen(filename, "a");

	for (u64 j = (u64)(p.data[p.length-1]); j < limit; j += 2 ) {
		if ( prime_sieve(j, p) ) {
            p = append_list( p, (void*)j );
            fprintf(file, "%llu ", j);
		}
        // every second print the last prime that was found.
        if ( time_elapsed()-t0 >= 1 ){
			t0 = time_elapsed();
		    printf("\r...%llu", (u64)(p.data[p.length-1]));
            fflush(stdout);
        }
	}
    return p;
}



int main()
{
  //    simple_make_prime_numbers();
    make_prime_numbers("primes.txt");
}
