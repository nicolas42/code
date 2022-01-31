// g++ buttons.cpp -Iinclude -framework SDL2 -framework SDL2_ttf && ./a.out


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "SDL2/SDL.h"
#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

#define SDL_STUFF_IMPLEMENTATION
#include "sdl_stuff.h"



int main(int argc, char **argv) {

    int button_width = 300;
    int button_height = 200;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 4 * button_width;
    int window_height = button_height;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer( window_width, window_height, 0, &window, &renderer );
    // SDL_SetWindowTitle(window, "Scroll text using the mouse wheel or arrow keys.");



	SDL_Surface* surface = STBIMG_Load( "data/button.png" );
	if( !surface ) {
		printf( "ERROR %s %d %s\n", __FILE__,__LINE__,SDL_GetError() );
        exit(1);
	}
    // SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) ); // what does this do?
    SDL_Texture *buttons_texture = SDL_CreateTextureFromSurface( renderer, surface );


    SDL_Rect srcrect, dstrect;
    srcrect = set_rect( 0,0, button_width,button_height );
    dstrect = set_rect( 0,0, button_width,button_height );

    for( int i = 0; i < 4; ++i ) {

        srcrect.y = i * button_height;
        dstrect.x = i * button_width;

        SDL_RenderCopy( renderer, buttons_texture, &srcrect, &dstrect );
        // int SDL_RenderCopy(SDL_Renderer * renderer, SDL_Texture * texture,  const SDL_Rect * srcrect, const SDL_Rect * dstrect);
    }
    SDL_RenderPresent( renderer );


    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while ( SDL_PollEvent(&event) ) {

            if (event.type == SDL_QUIT) { quit = 1; }

            if ( event.type == SDL_MOUSEMOTION ) printf("SDL_MOUSEMOTION "); // no newline
            if ( event.type == SDL_MOUSEBUTTONDOWN ) printf("SDL_MOUSEBUTTONDOWN\n");
            if ( event.type == SDL_MOUSEBUTTONUP ) printf("SDL_MOUSEBUTTONUP\n");
            if ( event.type == SDL_MOUSEWHEEL ) printf("SDL_MOUSEWHEEL\n");

        }

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



