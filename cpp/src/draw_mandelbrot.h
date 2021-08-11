#include <stdio.h>
#include <stdlib.h>

struct image {
    // width, height, number of channels, image data
    int w;
    int h;
    int c;
    char *data;
};


void draw_mandelbrot(struct image im, double x, double y, double zoom, double max_iterations );

struct image draw_mandelbrot_main();
