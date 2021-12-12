// g++ 6.cpp -framework SDL2 -framework SDL2_image -I../SDL2 && ./a.out

// Textures are hardware rendered images

// There's a bug where if I call SDL_GetWindowSurface on the window then
// it screws up CreateTextureFromSurface


#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

int main( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    // SDL_Surface *surface = SDL_GetWindowSurface( window );
    SDL_Renderer *window_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( window_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_Surface* tmp = IMG_Load( "lena.png" ); 
	SDL_Texture *image = SDL_CreateTextureFromSurface( window_renderer, tmp );
    if (image == NULL) printf("shit shit fucking guard dogs!\n");
    SDL_FreeSurface(tmp);


    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;

        SDL_RenderClear( window_renderer );
        SDL_RenderCopy( window_renderer, image, NULL, NULL );
        SDL_RenderPresent( window_renderer );
    }




    SDL_DestroyWindow( window );
    SDL_DestroyTexture( image );
    SDL_DestroyRenderer( window_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}
