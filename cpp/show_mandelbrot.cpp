/*
g++ show_mandelbrot.cpp -ISDL2 -framework SDL2 && ./a.out

from https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation

Endianness
the integer rgba is stored in memory as abgr in x86 systems.
stb image functions operate on the data as a series of bytes whereas SDL functions operate on the data as a series of integers.

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "types.h"


float hue2rgb(float p, float q, float t) {
    if (t < 0.) {
        t += 1.;
    }
    if (t > 1.) {
        t -= 1.;
    }
    if (t < 1. / 6.) {
        return p + (q - p) * 6. * t;
    }
    if (t < 1. / 2.) {
        return q;
    }
    if (t < 2. / 3.) {
        return p + (q - p) * (2. / 3. - t) * 6.;
    }
    return p;
}

u32 hsl2rgba(float h, float s, float l) {

    float r,g,b;
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2.0 * l - q;
    if (s == 0.0) {
        r = 1.0;
        g = 1.0;
        b = 1.0; // achromatic
    } else {
        r = hue2rgb(p, q, h + 1.0 / 3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.0 / 3.0);
    }

    // scale channels by 255.0 and combine them into a 32 bit integer
    u32 rgba = (u32)(  
        ((u8)(r*255.0))<<24 | ((u8)(g*255.0))<<16 | ((u8)(b*255.0))<<8 | (u8)255  
    );
    return rgba;
}
    
typedef struct {
    // width, height, number of channels, image data
    u32 w,h,c,*data;
} Image;

Image make_image(float w, float h, float c)
{
    Image im;
    im.w = w;
    im.h = h;
    im.c = c;
    im.data = (u32*)malloc(im.w * im.h * sizeof(u32));
    return im;
}

void draw_mandelbrot_rgba(Image im, float x, float y, float zoom, float max_iterations )
{
    float i,j,h,w,cx,cy,zx,zy,zxtemp,hue;
    u32 in_set,num_iterations,pos,rgba,black;

    for (j = 0; j < im.h; j += 1) {
        for (i = 0; i < im.w; i += 1) {
            h = 4.0 / zoom;
            w = 4.0 / zoom;
            // z = z^2 + c
            cx = (x - w / 2) + i * (w / im.w);
            cy = (y - h / 2) + j * (w / im.w);
            zx = 0;
            zy = 0;
            in_set = 1;
            num_iterations = 1;
            while ( num_iterations <= max_iterations ) {
                zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                if (zx * zx + zy * zy > 4) {
                    in_set = 0;
                    break;
                }
                num_iterations += 1;
            }
            pos = (j * im.w) + (i);
            if (in_set) {
                im.data[pos] = 255; // black
            } else {
                hue = (num_iterations % 255) / 255.0;
                im.data[pos] = hsl2rgba(hue, 1.0, 0.5);
            }
        }
    }
}


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main( int argc, char* args[] )
{
    // window width, height, channels
    const int w  = 800;
    const int h = 800;
    const int c = 4;

    Image im;
    SDL_Surface *s;

    int i;

    // initialize
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    SDL_Surface *window_surface = SDL_GetWindowSurface( window );


    // make image
    im = make_image(w,h,c);
    draw_mandelbrot_rgba(im, -0.6999687500000003, -0.2901249999999999, 1000, 1000);
    // image to surface
    u32 pitch, depth, rmask, gmask, bmask, amask;
    pitch = 4*im.w; // The "pitch" is the length of a row in bytes, it appears.
    depth = 32;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    s = SDL_CreateRGBSurfaceFrom((void*)im.data, im.w, im.h, depth, pitch, rmask, gmask, bmask, amask);

    // blit it
    SDL_BlitSurface( s, NULL, window_surface, NULL );
    SDL_UpdateWindowSurface(window);

    // print surface pixel format
    SDL_PixelFormat* pixelFormat = s->format;
    Uint32 pixelFormatEnum = pixelFormat->format;
    const char* surfacePixelFormatName = SDL_GetPixelFormatName(pixelFormatEnum);
    SDL_Log("The surface's pixelformat is %s", surfacePixelFormatName);

    // swap pixels and write
    for(i=0;i<s->w*s->h;++i) ((u32*)s->pixels)[i] = SDL_Swap32(((u32*)s->pixels)[i]);
    int success = stbi_write_png("mandy.png", s->w, s->h, 4, s->pixels, s->w * 4);
    if (success) { SDL_Log("You wrote the png!"); }

    // event loop
    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event); // wait instead of poll to save compute
        if ( event.type == SDL_QUIT ) running = 0;
    }

    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}



// int texture_main(int argc, char ** argv)
// {
//     int WINDOW_WIDTH = 800;
//     int WINDOW_HEIGHT = 800;
//     SDL_Init( SDL_INIT_EVERYTHING );
//     SDL_Window* window_surface = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
//     SDL_Renderer* window_renderer = SDL_CreateRenderer( window_surface, -1, SDL_RENDERER_ACCELERATED );

//     Image image;
//     SDL_Texture* texture;


//     image = make_image(WINDOW_WIDTH, WINDOW_HEIGHT, 4); // width, height, number of channels
//     draw_mandelbrot_rgba(image, -0.6999687500000003, -0.2901249999999999, 1000, 1000); // x,y,zoom,max_iterations

//     texture = SDL_CreateTexture( window_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, image.w, image.h );
//     SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
//     SDL_UpdateTexture( texture, NULL, image.data, image.w * image.c );
//     SDL_RenderClear( window_renderer );
//     SDL_RenderCopy( window_renderer, texture, NULL, NULL );
//     SDL_RenderPresent( window_renderer );

//     SDL_Event event;
//     bool running = true;
//     int i = 0;
//     while ( running )
//     {
//         SDL_WaitEvent(&event);
//         if ( event.type == SDL_QUIT ) running = false;
//         printf("event %d\n", i++);
//     }

//     SDL_DestroyTexture(texture);
//     free(image.data);
//     SDL_Quit();
 
//     return 0;
// }



void reverse_pixel_order(Image im)
{
    // rbga <=> gbra, doesn't move alpha
    float i,j;
    int pos;
    char r,g,b;

    for(j=0;j<im.h;++j){
        for(i=0;i<im.h;++i){

            pos = (j * im.w * im.c) + (i * im.c);

            r = im.data[pos+0];
            g = im.data[pos+1];
            b = im.data[pos+2];

            im.data[pos + 0] = b;
            im.data[pos + 1] = g;
            im.data[pos + 2] = r;
            im.data[pos + 3] = (char)255;

        }
    }
}
