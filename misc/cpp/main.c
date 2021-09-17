/*
gcc main.c lib.a -Isrc && ./a.out
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "draw_mandelbrot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



#define HR printf("\n\n-------------------------------------------------------\n\n"); 

int main()
{
    struct image im = draw_mandelbrot_main();
    stbi_write_jpg("mandelbrot_image.jpg", im.w, im.h, im.c, im.data, im.w*im.c);

}
