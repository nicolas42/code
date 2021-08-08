#include <stdio.h>

// typedef unsigned long long u64;


// prime sieve.
// only checks odd numbers
void make_prime_numbers( int total_number_to_make, int *data, int* ret_length )
{
	int length = *ret_length;
	// needs data to be at least {2,3} since it only checks odd numbers
	if ( length < 2 ) {
		printf("Oh noes!!!\n");
		data[0] = 2; data[1] = 3;
		length = 2;
	}
	for ( int candidate_number = data[length-1]; length < total_number_to_make; candidate_number += 2 ) {
		
		int is_prime = 1;
		
		for ( int i = 0; i < length; i++){
			if ( candidate_number % data[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime) {
			data[length++] = candidate_number;
			fprintf("%d ", candidate_number);			
		}
	}
	*ret_length = length;
}


int main(int argc, char** argv)
{

	// int data[100000] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
	// int length = 100;

	// int data[1000000] = {};
	int *data = malloc( 100 * sizeof(int) );
	int length = 0;
	make_prime_numbers(100, data, &length);
	// for ( int i=0; i<length; i+=1 ) printf("%d, ", data[i] );
	return 0;
}
