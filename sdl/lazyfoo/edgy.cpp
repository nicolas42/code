// g++ edgy.cpp -framework SDL2 -framework SDL2_image -I../SDL2 && ./a.out


#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main( int argc, char* args[] )
{

    // This example shows how to create a SDL_Surface* with the data loaded
    // from an image file with stb_image.h (https://github.com/nothings/stb/)

    // the color format you request stb_image to output,
    // use STBI_rgb if you don't want/need the alpha channel
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char* data = stbi_load("lena.png", &width, &height, &orig_format, req_format);
    if (data == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        exit(1);
    }


    for (int j=0; j<height; j++ ){
        for (int i=0; i<width; i++ ){
            int pos = j*width*4 + i*4;
            char r = data[pos+0];
            char g = data[pos+1];
            char b = data[pos+2];
            char a = data[pos+3];

            char v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            data[pos+0] = v;
            data[pos+1] = v;
            data[pos+2] = v;
            data[pos+3] = 255;

        }
    }

    // https://github.com/petermlm/SobelFilter/blob/master/src/sobel.c


    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
    
    SDL_Renderer* window_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Texture* texture = SDL_CreateTexture( window_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height );

        
    SDL_UpdateTexture( texture, NULL, data, width * 4 );
    SDL_RenderCopy( window_renderer, texture, NULL, NULL );
    SDL_RenderPresent( window_renderer );

    SDL_Event event;
    bool running = true;
    while ( running )
    {
        SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( window_renderer );

        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }


    SDL_Quit();
    return 0;
}


