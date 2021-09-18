#include <stdio.h>
#include <signal.h>
#include <stdint.h>

// prime sieve.
// only checks odd numbers
int simple_prime_sieve()
{

    int length = 2;
	uint64_t prime_numbers[1000000] = {2, 3};
    // for (int i=0; i<length; i++) printf("%d %llu\n", i, prime_numbers[i]);

    int total_number_to_make = 1000000;
	for ( uint64_t candidate_number = prime_numbers[length-1]; length < total_number_to_make; candidate_number += 2 ) {
		
		int is_prime = 1;

		for ( int i = 0; i < length; i++){
			if ( candidate_number % prime_numbers[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime) {
			prime_numbers[length++] = candidate_number;
			printf("%lu ", candidate_number);			
		}
	}
	return 0;
}





#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>
#include <time.h>


typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

typedef struct string_array {
	size_t length;
	size_t allocated;
	char** data;
} string_array;

int file_exists(const char * filename);
double get_time_elapsed(void);
string read_file(char *filename);
string copy_string(string a);
void string_array_add(string_array* f, char* a);
string_array split_string(char* a, char* characters_to_split_on);


double get_time_elapsed(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}

string copy_string(string a)
{
	string b;
	b.length = a.length;
	b.allocated = a.allocated;
	b.data = (char*)malloc(b.allocated*sizeof(char*));
	strcpy(b.data, a.data);
	return b;
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

string read_file (char *filename)
{
	string f;
	f.length = 0;
	f.allocated = 1000;
	f.data = (char*)malloc(1000);

	FILE *fp;
	int c;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return f;
	}

	while (1) {
		c = fgetc(fp);
		if (feof(fp)) { 
			f.data[f.length] = '\0';
			f.length += 1;
			break; 
		}
		f.data[f.length] = (char)c;
		f.length += 1;
		
		if (f.length == f.allocated){
			f.allocated *= 2;
			f.data = (char*)realloc(f.data, f.allocated);
		}
	}
	fclose(fp);

	return f;
}



void string_array_add(string_array* s, char* string_to_add)
{
	if (s->length == s->allocated){
		s->allocated *= 2;
		s->data = (char**)realloc(s->data, s->allocated*sizeof(char**));
		// printf("GROW!!!\n");
	}
	s->data[s->length] = string_to_add;
	s->length += 1;
}

string_array split_string(char* s, char* split_chars)
{
	// this modifies the original string
	// first it changes all of the split characters to null
	// then it notes down all positions where there's a null non-null pattern
	// (as well as the first position if it's not null)

	string_array sa;
	sa.length = 0;
	sa.allocated = 100;
	sa.data = (char**)malloc(100*sizeof(char**));

	size_t strlen_a = strlen(s); 
	for (size_t i = 1; i < strlen_a; i++){

		for (size_t j = 0; j < strlen(split_chars); j++)
		{
			if ( s[i] == split_chars[j] ){ 
				s[i] = '\0'; 
				break; 
			}
		}
	}

	if (s[0] != '\0') {
		string_array_add(&sa, &(s[0]));
	}
	for (size_t i = 1; i < strlen_a; i++) {
		if (s[i-1] == '\0' && s[i] != '\0') {
			string_array_add(&sa, &(s[i]));
		}
	}

	return sa;
}






// double min(double a, double b)
// {
// 	if (a < b ){
// 		return a;
// 	}
// 	return b;
// }

// void demo_split_destructive(void)
// {
// 	string f = read_file("basic.h");
// 	string_array tokens = split_string(f.data, "\n\r\t ");

// 	for (size_t i = 0; i < min(10, tokens.length); i++){
// 		printf("{%s} ", tokens.data[i]);
// 	}
// }

// int split_main(int argc, char** argv)
// {
// 	// ./a.out split "Halsdkjf asldfk jasfdkl askjfd kalsfkj" "\n"

// 	if (argc != 4){
// 		printf("usage: ./a.out split string-to-split chars-to-split-on\n");
// 		return -1;
// 	}

// 	char* data = argv[2];
// 	char* characters_to_split_on = argv[3];
// 	string_array tokens = split_string(data, characters_to_split_on);

// 	for (size_t i = 0; i < min(10, tokens.length); i++){
// 		printf("%s\n", tokens.data[i]);
// 	}
// 	return 0;
// }






static FILE* file;

struct uint64_array {
    uint64_t* data;
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

int less_simple_prime_sieve(void)
{
    char* filename = "primes.dat";

    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { printf("\ncan't catch SIGINT\n"); }

    // first we make an unsigned 64 bit integer array to store the prime numbers
    // then, if the file exists, we read the numbers from it, which are space delimited.
    // then we use that array to generate more primes, appending them to the file as we go

    struct uint64_array p;
    p.allocated = 1e6;
    p.data = malloc( p.allocated * sizeof(uint64_t));
    p.length = 0;

    if (file_exists(filename)){
        string f = read_file(filename);
        string_array s = split_string(f.data, "\n\r\t ");

        for (size_t i = 0; i < s.length; i++)
        {             
            // printf("%s ", s.data[i]);       
            // char* ptr;
            sscanf(s.data[i], "%lu", &p.data[i]); 
            if (p.length == p.allocated){
                p.allocated *= 2;
                p.data = realloc(p.data, p.allocated * sizeof(uint64_t));
                // printf("OMG!!!\n");
            }

            // p.data[i] = strtoll(s.data[i], &ptr, 10);
            p.length += 1;
        }
        // printf("\n");

    }

    printf("last prime: %lu ", p.data[p.length-1]);
    
    if (p.length == 0){
        p.data[0] = 2;
        p.length = 1;
    }

	double t1 = get_time_elapsed();

	file = fopen(filename, "a");

    uint64_t is_prime = 0;
    uint64_t a = p.data[p.length-1];
	for ( ; ; a++){
		is_prime = 1;
		for ( uint64_t i = 0; i < p.length; i++){
			if ( a%p.data[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime){
			p.data[p.length++] = a;
            if (p.length == p.allocated){
                p.allocated *= 2;
                p.data = realloc(p.data, p.allocated * sizeof(uint64_t));
                // printf("OMG!!!\n");
            }

            printf(".");
            fflush(stdout);
            fprintf(file, "%lu ", p.data[p.length-1]);


			// printf("%lu ", a);
		}


		if (get_time_elapsed()-t1 >= 1){
			t1 = get_time_elapsed();
			printf("\r\n%lu\r\n", p.data[p.length-1]);

            // int timeout = 1000;
            // if (t1 > timeout){ break; }
		}
	}


    // fclose(file);

	// for ( uint64_t i = 0; i < p.length; i++){
		// printf("%d ", p.data[i]);
	// }

	// return 0;
}


int main()
{
    simple_prime_sieve();
    // less_simple_prime_sieve();
}
