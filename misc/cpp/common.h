#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
char* caesar_cipher(char* text, int shift);
int caesar_cipher_main();
int draw_mandelbrot_main();
int newtons_method_main();
int eulers_method_main();
int read_file_main();
int thread_race_main();
int multivector_main();
double time_elapsed();
}

int demo_vectors();
void demo_vectors_main();
int sha1_main();


