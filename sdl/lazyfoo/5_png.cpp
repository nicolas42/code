// g++ 5.cpp -framework SDL2 -framework SDL2_image -I../SDL2 && ./a.out

// Lets load a png omg


#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

int main( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window_object = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *window = SDL_GetWindowSurface( window_object );

    IMG_Init( IMG_INIT_PNG );
    SDL_Surface* image = IMG_Load( "nyan_cat.png" ); 

	

    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;

        SDL_FillRect( window, NULL, SDL_MapRGB( window->format, 0x00, 0x00, 0x00 ) );
        SDL_Rect window_size = { .x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT };
        SDL_BlitScaled( image, NULL, window, &window_size );
        SDL_UpdateWindowSurface( window_object );

    }


    SDL_DestroyWindow( window_object );
    SDL_Quit();
    return 0;
}
