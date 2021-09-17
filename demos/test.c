#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "caesar_cipher.c"
#include "multivector.c"
#include "read_file.c"
#include "eulers_method.c"
#include "draw_mandelbrot.c"
#include "thread_race.c"
#include "time_elapsed.c"

#define HR printf("\n\n-------------------------------------------------------\n\n"); 

int main()
{
    double t0 = time_elapsed();
    HR
    caesar_cipher_main();
    HR
    multivector_main();
    HR
    read_file_main();
    HR
    eulers_method_main();
    HR
    // draw_mandelbrot_main(); // takes a while
    // HR
    thread_race_main();
    HR

    printf("Time elapsed: %f\n", time_elapsed() - t0);
    HR
}
