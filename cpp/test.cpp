#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "common.h"

#define HR printf("\n\n-------------------------------------------------------\n\n"); 

int main()
{
    double t0 = time_elapsed(); HR


    caesar_cipher_main(); HR
    multivector_main(); HR
    read_file_main(); HR
    eulers_method_main(); HR
    draw_mandelbrot_main(); HR // takes a while 
    thread_race_main(); HR
    demo_vectors(); HR
    sha1_main();


    printf("Time elapsed: %f\n", time_elapsed() - t0); HR
}
