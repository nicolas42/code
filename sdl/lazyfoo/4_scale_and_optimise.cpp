// g++ 4.cpp -framework SDL2 -I../SDL2 && ./a.out

// Scale an image and optimise it for faster blitting
// --------------------------------------------------------------
// You can optimise an image to have the same format as the underlying surface that it's going to render to
// with SDL_ConvertSurface(a, surface->format, 0); omgomgomg

// You can also scale surfaces when you blit them using this call
// SDL_BlitScaled( images[image_index], NULL, window, &window_size );
// window_size is an SDL_Rect which is what you might imagine.
// a rectangle has x,y,w, and h parameters. yay.  it describes a rectangular area on the screen 
// or I suppose any rectangle that you might be interested in.



#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window_object = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *window = SDL_GetWindowSurface( window_object );

    SDL_Surface *images[2];
    int image_index = 0;
    // load some images and optimise them to the format of the window
    char filenames[2][20] = { "lenna.bmp", "smiley.bmp" };
    SDL_Surface *tmp;
    for (int i=0; i<2; i++ ) {
        tmp = SDL_LoadBMP( filenames[i] );
        images[i] = SDL_ConvertSurface( tmp, window->format, 0 );
    }
    SDL_FreeSurface(tmp);



	

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
                image_index = 0; 
                render_image = 1;
            } 
            if ( event.key.keysym.sym == SDLK_RIGHT )
            {
                printf("omg right\n");
                image_index = 1;
                render_image = 1;
            }
        }

        if (render_image) {
            SDL_FillRect( window, NULL, SDL_MapRGB( window->format, 0x00, 0x00, 0x00 ) );
            SDL_Rect window_size = { .x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT };
            SDL_BlitScaled( images[image_index], NULL, window, &window_size );
            SDL_UpdateWindowSurface( window_object );
            render_image = 0;
        }
    }


    SDL_DestroyWindow( window_object );
    SDL_Quit();
    return 0;
}
