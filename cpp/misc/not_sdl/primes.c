#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "types.h"


struct list {
  void** data;
  int length;
  int allocated;
};

struct list make_list()
{
    struct list l;
    l.length = 0;
    l.allocated = 10;
    l.data = (void**)malloc( l.allocated * sizeof(void*) );
    return l;
}

struct list append_list(struct list l, void* str)
{
    l.data[l.length] = str;
    l.length += 1;
    if ( l.length == l.allocated ) {
      l.allocated *= 2;
      l.data = (void**)realloc( l.data, l.allocated * sizeof(void*) );
    }
    return l;
}

struct list split_string(char *str, char delim)
{
    // convert spaces to null bytes
    size_t string_length = strlen(str);
    int i=0;
    for (i=0;i<string_length;i++) if (str[i]==delim) str[i] = '\0';

    // note down stuff after null bytes
    struct list l = make_list();
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










int prime_sieve( u64 candidate, struct list primes )
{
    for (u64 i=0; i<primes.length; i++){
        if ( candidate % (u64)primes.data[i] == 0) return 0;
    }
    return 1;
}


struct list simple_make_prime_numbers()
{
    struct list primes = make_list();
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
struct list make_prime_numbers(char *filename)
{
    // register signal handler
    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { printf("\nERROR registering signal handler\n"); }

    struct list p = make_list(); // primes
    FILE *file;
    int i;

    // if file exists then read the numbers from it,
    // otherwise create a new file and add 2 and 3 to start off.
    // 2 and 3 are needed since the program starts from the last
    // prime in the list and jumps in twos to the next candidate number.
    if ( file_exists(filename)) {
        char *str;
        struct list list;
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






/*
A simple little macro for quick typesafe expanding arrays

Put this in the global scope.
DEFINE_ARRAY(u64)

Then do something like this
u64_array a = u64_array_make();
a = u64_array_add(a, 23424234234);
printf("%c ", a.data[0]);


Tips for macros
------------------
Use -E to see the outputs of macros
gcc -E define_array_macro.c

## joins strings
so str1 ## str2 becomes str1str2
*/



#define DEFINE_ARRAY(TYPENAME)                                                                  \
                                                                                                \
typedef struct {                                                                                \
  TYPENAME* data;                                                                               \
  int length;                                                                                   \
  int allocated;                                                                                \
} TYPENAME ## _array;                                                                           \
                                                                                                \
TYPENAME ## _array TYPENAME ## _array_make()                                                    \
{                                                                                               \
    TYPENAME ## _array arr;                                                                     \
    arr.length = 0;                                                                             \
    arr.allocated = 16;                                                                         \
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );                           \
    return arr;                                                                                 \
}                                                                                               \
                                                                                                \
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)                \
{                                                                                               \
    arr.data[arr.length] = item;                                                                \
    arr.length += 1;                                                                            \
    if ( arr.length == arr.allocated ) {                                                        \
      arr.allocated *= 2;                                                                       \
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );              \
    }                                                                                           \
    return arr;                                                                                 \
}                                                                                               \



int main()
{
  //    simple_make_prime_numbers();
    make_prime_numbers("primes.txt");
    return 0;
}
