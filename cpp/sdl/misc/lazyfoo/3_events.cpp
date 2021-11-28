// g++ 3.cpp -framework SDL2 -I../SDL2 && ./a.out

// Respond to left and right arrow events 


#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );

    SDL_Surface *surfaces[2];
    surfaces[0] = SDL_LoadBMP( "lenna.bmp" );
    surfaces[1] = SDL_LoadBMP( "smiley.bmp" );
    int surface_index = 1;

    SDL_Event event;
    int running = 1;
    int render_image = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;
        if ( event.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_LEFT ) 
            {
                printf("omg left\n");
                surface_index = 0; 
                render_image = 1;
            } 
            if ( event.key.keysym.sym == SDLK_RIGHT )
            {
                printf("omg right\n");
                surface_index = 1;
                render_image = 1;
            }
        }

        if (render_image) {
            SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );
            SDL_BlitSurface( surfaces[surface_index], NULL, surface, NULL );
            SDL_UpdateWindowSurface( window );
            render_image = 0;
        }
    }


    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
