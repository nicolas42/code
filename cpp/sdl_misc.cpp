// g++ sdl_misc.cpp -framework SDL2 -framework SDL2_image -ISDL2 -g -fsanitize=address && ./a.out

// notes
// -----------
// c-style casts have higher precedence than arithmetic and logic operations
// https://en.cppreference.com/w/cpp/language/operator_precedence
// https://wiki.libsdl.org/SDL_Event
// print error with line number macro
// https://stackoverflow.com/questions/8884481/exact-line-number-for-c-error


// SDL_BlitScaled() requires the surface to be converted to native format first
// by calling SDL_ConvertSurface()


// SDL_GetWindowSurface can't be combined with the rendering API
// You may not combine this with 3D or the rendering API on this window.
// https://wiki.libsdl.org/SDL_GetWindowSurface

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

#define PRINT_ERROR(ERR) printf("ERROR %s %d %s\n", __FILE__, __LINE__, ERR)

void print_event(SDL_Event event)
{
    if ( event.type == SDL_AUDIODEVICEADDED ) printf("SDL_AUDIODEVICEADDED\n");
    if ( event.type == SDL_AUDIODEVICEREMOVED ) printf("SDL_AUDIODEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERAXISMOTION ) printf("SDL_CONTROLLERAXISMOTION\n");
    if ( event.type == SDL_CONTROLLERBUTTONDOWN ) printf("SDL_CONTROLLERBUTTONDOWN\n");
    if ( event.type == SDL_CONTROLLERBUTTONUP ) printf("SDL_CONTROLLERBUTTONUP\n");
    if ( event.type == SDL_CONTROLLERDEVICEADDED ) printf("SDL_CONTROLLERDEVICEADDED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMOVED ) printf("SDL_CONTROLLERDEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMAPPED ) printf("SDL_CONTROLLERDEVICEREMAPPED\n");
    if ( event.type == SDL_DOLLARGESTURE ) printf("SDL_DOLLARGESTURE\n");
    if ( event.type == SDL_DOLLARRECORD ) printf("SDL_DOLLARRECORD\n");
    if ( event.type == SDL_DROPFILE ) printf("SDL_DROPFILE\n");
    if ( event.type == SDL_DROPTEXT ) printf("SDL_DROPTEXT\n");
    if ( event.type == SDL_DROPBEGIN ) printf("SDL_DROPBEGIN\n");
    if ( event.type == SDL_DROPCOMPLETE ) printf("SDL_DROPCOMPLETE\n");
    if ( event.type == SDL_FINGERMOTION ) printf("SDL_FINGERMOTION\n");
    if ( event.type == SDL_FINGERDOWN ) printf("SDL_FINGERDOWN\n");
    if ( event.type == SDL_FINGERUP ) printf("SDL_FINGERUP\n");
    if ( event.type == SDL_KEYDOWN ) printf("SDL_KEYDOWN\n");
    if ( event.type == SDL_KEYUP ) printf("SDL_KEYUP\n");
    if ( event.type == SDL_JOYAXISMOTION ) printf("SDL_JOYAXISMOTION\n");
    if ( event.type == SDL_JOYBALLMOTION ) printf("SDL_JOYBALLMOTION\n");
    if ( event.type == SDL_JOYHATMOTION ) printf("SDL_JOYHATMOTION\n");
    if ( event.type == SDL_JOYBUTTONDOWN ) printf("SDL_JOYBUTTONDOWN\n");
    if ( event.type == SDL_JOYBUTTONUP ) printf("SDL_JOYBUTTONUP\n");
    if ( event.type == SDL_JOYDEVICEADDED ) printf("SDL_JOYDEVICEADDED\n");
    if ( event.type == SDL_JOYDEVICEREMOVED ) printf("SDL_JOYDEVICEREMOVED\n");
    if ( event.type == SDL_MOUSEMOTION ) printf("SDL_MOUSEMOTION ");
    if ( event.type == SDL_MOUSEBUTTONDOWN ) printf("SDL_MOUSEBUTTONDOWN\n");
    if ( event.type == SDL_MOUSEBUTTONUP ) printf("SDL_MOUSEBUTTONUP\n");
    if ( event.type == SDL_MOUSEWHEEL ) printf("SDL_MOUSEWHEEL\n");
    if ( event.type == SDL_MULTIGESTURE ) printf("SDL_MULTIGESTURE\n");
    if ( event.type == SDL_QUIT ) printf("SDL_QUIT\n");
    if ( event.type == SDL_SYSWMEVENT ) printf("SDL_SYSWMEVENT\n");
    if ( event.type == SDL_TEXTEDITING ) printf("SDL_TEXTEDITING\n");
    if ( event.type == SDL_TEXTINPUT ) printf("SDL_TEXTINPUT\n");
    if ( event.type == SDL_USEREVENT ) printf("SDL_USEREVENT\n");
    if ( event.type == SDL_WINDOWEVENT ) printf("SDL_WINDOWEVENT\n");

    if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));

    fflush(stdout);
}

SDL_Rect make_rect(int x, int y, int w, int h)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    return dest;
}

int main1( int argc, char** argv )
{
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    const int window_width = 800;
    const int window_height = 600;
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );

    SDL_Surface *surface, *lenna, *lenna_native, *nyan_cat;
    int err;
    SDL_Rect destination;
    float scaler;

    surface = SDL_GetWindowSurface( window );
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x55,0x55,0xAA ) );

    lenna = SDL_LoadBMP( "data/lenna.bmp" );
    SDL_BlitSurface( lenna, NULL, surface, NULL );

    // blit scaled
    scaler = 300.0 / (float)lenna->h;
    destination = make_rect(lenna->w, 0, scaler*lenna->w, scaler*lenna->h);
    lenna_native = SDL_ConvertSurface( lenna, surface->format, 0 ); // requires native format
    err = SDL_BlitScaled( lenna_native, NULL, surface, &destination );
    if (err) PRINT_ERROR(SDL_GetError());

    // load png
    nyan_cat = IMG_Load( "data/nyan_cat.png" ); 
    scaler = 300.0 / (float)nyan_cat->h;
    destination = make_rect(0,300, scaler*nyan_cat->w, scaler*nyan_cat->h);
    err = SDL_BlitScaled( nyan_cat, NULL, surface, &destination );
    if (err) PRINT_ERROR(SDL_GetError());


    SDL_UpdateWindowSurface( window );


    SDL_Event event; 
    int quit = 0;
    while ( !quit ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) quit = 1;
        print_event(event);
    }


    SDL_FreeSurface(lenna);
    SDL_FreeSurface(lenna_native);
    SDL_FreeSurface(nyan_cat);
    SDL_DestroyWindow( window ); // frees surface
    SDL_Quit();
    return 0;
}



// use renderer
int main( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 600;
    
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    
    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    // SDL_SetRenderDrawColor( renderer, 255,255,255,255);
    // SDL_RenderClear( renderer );

    SDL_Surface* nyan_cat = IMG_Load( "data/nyan_cat.png" ); 
	SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, nyan_cat );
    if (!texture) PRINT_ERROR(SDL_GetError());

    float scaler = 300.0 / (float)nyan_cat->h;
    SDL_Rect destination = make_rect(0,300, scaler*nyan_cat->w, scaler*nyan_cat->h);

    SDL_RenderCopy( renderer, texture, NULL, &destination );
    SDL_RenderPresent( renderer );

    SDL_Event event;
    int quit = 0;
    while ( !quit ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) quit = 1;

    }


    SDL_FreeSurface(nyan_cat);
    SDL_DestroyWindow( window );
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );

    IMG_Quit();
    SDL_Quit();
    return 0;
}


