#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "caesar_cipher.h"
#include "multivector.h"
#include "read_file.h"
#include "eulers_method.h"
#include "draw_mandelbrot.h"
#include "thread_race.h"
#include "time_elapsed.h"

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
