#include <stdio.h>
#include "basic.h"

typedef unsigned long long u64;
static FILE* file;

struct u64_array {
    u64* data;
    size_t length;
    size_t allocated;
};

void signal_handler(int signal_number);

void signal_handler(int signal_number)
{
  if (signal_number == SIGINT){
    fclose(file);
    printf("received SIGINT\n");
    exit(0);
  }
}

int main(void)
{
    // first we make an unsigned 64 bit integer array to store the prime numbers
    // then, if the file exists, we read the numbers from it, which are space delimited.
    // then we use that array to generate more primes, appending them to the file as we go

    if (signal(SIGINT, signal_handler) == SIG_ERR){
        printf("\ncan't catch SIGINT\n");
    }

    struct u64_array p;
    p.allocated = 1e6;
    p.data = malloc( p.allocated * sizeof(u64));
    p.length = 0;


    char* filename = "primes.dat";
    if (file_exists(filename)){
        string f = read_file(filename);
        string_array s = split_string(f.data, "\n\r\t ");

        for (size_t i = 0; i < s.length; i++)
        {             
            // printf("%s ", s.data[i]);       
            // char* ptr;
            sscanf(s.data[i], "%llu", &p.data[i]); 
            if (p.length == p.allocated){
                p.allocated *= 2;
                p.data = realloc(p.data, p.allocated * sizeof(u64));
                // printf("OMG!!!\n");
            }

            // p.data[i] = strtoll(s.data[i], &ptr, 10);
            p.length += 1;
        }
        // printf("\n");

    }

    printf("*last prime: %llu ", p.data[p.length-1]);
    
    if (p.length == 0){
        p.data[0] = 2;
        p.length = 1;
    }

	double t1 = get_time_elapsed();

	file = fopen(filename, "a");

    u64 is_prime = 0;
    u64 a = p.data[p.length-1];
	for ( ; ; a++){
		is_prime = 1;
		for ( u64 i = 0; i < p.length; i++){
			if ( a%p.data[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime){
			p.data[p.length++] = a;
            if (p.length == p.allocated){
                p.allocated *= 2;
                p.data = realloc(p.data, p.allocated * sizeof(u64));
                // printf("OMG!!!\n");
            }

            fprintf(file, "%llu ", p.data[p.length-1]);

			// printf("%llu ", a);
		}


		if (get_time_elapsed()-t1 >= 1){
			t1 = get_time_elapsed();
			printf("last prime: %llu\r\n", p.data[p.length-1]);

            // int timeout = 1000;
            // if (t1 > timeout){ break; }
		}
	}


    // fclose(file);

	// for ( u64 i = 0; i < p.length; i++){
		// printf("%d ", p.data[i]);
	// }

	// return 0;
}
