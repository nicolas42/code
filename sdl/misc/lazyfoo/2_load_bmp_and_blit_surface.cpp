// g++ 2.cpp -framework SDL2 -I../SDL2 && ./a.out

// Load an image an blit it to the screen
// ---------------------------------------
// surfaces are software rendered images
// blitting is copying an image to another image
// rendering is typically done to a backbuffer which needs to be swapped out with the front buffer to actually show something


// What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image. The third argument is the destination. We'll worry about the 2nd and 4th arguments in future tutorials.

// After drawing everything on the screen that we want to show for this frame we have to update the screen using SDL_UpdateWindowSurface. See when you draw to the screen, you are not typically drawing to the image on the screen you see. By default, most rendering systems out there are double buffered. These two buffers are the front and back buffer.

// When you make draw calls like SDL_BlitSurface, you render to the back buffer. What you see on the screen is the front buffer. The reason we do this is because most frames require drawing multiple objects to the screen. If we only had a front buffer, we would be able to see the frame as things are being drawn to it which means we would see unfinished frames. So what we do is draw everything to the back buffer first and once we're done we swap the back and front buffer so now the user can see the finished frame.

// This also means that you don't call SDL_UpdateWindowSurface after every blit, only after all the blits for the current frame are done.


#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
    SDL_Surface *image_surface = SDL_LoadBMP( "lenna.bmp" );

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image_surface->w, image_surface->h, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );

    SDL_BlitSurface( image_surface, NULL, surface, NULL );
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
