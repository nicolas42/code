// g++ 1.cpp -framework SDL2 -I../SDL2

// Open a window, harder than it sounds

#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0x00, 0x00 ) );
    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;
    }

    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
