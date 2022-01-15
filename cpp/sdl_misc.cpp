// clang++ sdl_misc.cpp -framework SDL2 -framework SDL2_image -ISDL2 -g -fsanitize=address && ./a.out

// c-style casts have higher precedence than arithmetic and logic operations
// https://en.cppreference.com/w/cpp/language/operator_precedence

// https://wiki.libsdl.org/SDL_Event


#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

#define PRINT_ERROR(err) printf("ERROR %s %d %s\n", __FILE__, __LINE__, err);

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
    if ( event.type == SDL_MOUSEMOTION ) printf("SDL_MOUSEMOTION\n");
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
}

SDL_Rect make_rect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

int main( int argc, char* args[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    const int window_width = 800;
    const int window_height = 600;
    SDL_Window *w = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );



    SDL_Surface *window, *lenna, *lenna_native, *nyan_cat;
    int err;
    SDL_Rect dest;

    window = SDL_GetWindowSurface( w );
    SDL_FillRect( window, NULL, SDL_MapRGB( window->format, 0x55,0x55,0xAA ) );


    lenna = SDL_LoadBMP( "data/lenna.bmp" );
    SDL_BlitSurface( lenna, NULL, window, NULL );

    // blig scaled requires images to be in native format so use convertsurface
    float scaler = 300.0 / (float)lenna->h;
    dest.x = lenna->w;
    dest.y = 0;
    dest.w = (int) ( scaler*lenna->w );
    dest.h = (int)( scaler*lenna->h );
    lenna_native = SDL_ConvertSurface( lenna, window->format, 0 ); 
    err = SDL_BlitScaled( lenna_native, NULL, window, &dest );
    if (err) PRINT_ERROR(SDL_GetError());

    // apparently the image library already converts to native, I guess
    nyan_cat = IMG_Load( "data/nyan_cat.png" ); 
    scaler = 300.0 / (float)nyan_cat->h;
    dest.x = 0;
    dest.y = 300;
    dest.w = (int) ( scaler*nyan_cat->w );
    dest.h = (int)( scaler*nyan_cat->h );
    err = SDL_BlitScaled( nyan_cat, NULL, window, &dest );
    if (err) PRINT_ERROR(SDL_GetError());


    // // actually show stuff
    // SDL_UpdateWindowSurface( w );


    SDL_Renderer *renderer = SDL_CreateRenderer( w, -1, SDL_RENDERER_ACCELERATED );
    // SDL_SetRenderDrawColor( renderer, 255,255,255,255);

    // SDL_Surface* nyan_cat = IMG_Load( "data/nyan_cat.png" ); 
	SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, nyan_cat );
    if (!texture) PRINT_ERROR(SDL_GetError());

    SDL_RenderClear( renderer );
    scaler = 300.0 / (float)nyan_cat->h;
    dest.x = 0;
    dest.y = 300;
    dest.w = (int) ( scaler*nyan_cat->w );
    dest.h = (int)( scaler*nyan_cat->h );

    SDL_RenderCopy( renderer, texture, NULL, &dest );
    SDL_RenderPresent( renderer );





    SDL_Event event; 
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;
        print_event(event);
    }


    // SDL_FreeSurface(window);
    // SDL_FreeSurface(lenna);
    // SDL_FreeSurface(lenna_native);

    SDL_DestroyWindow( w );
    SDL_Quit();
    return 0;
}


// Textures are hardware rendered images

// There's a bug where if I call SDL_GetWindowSurface on the window then
// it screws up CreateTextureFromSurface


int main1( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    // SDL_Surface *surface = SDL_GetWindowSurface( window );
    SDL_Renderer *window_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( window_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_Surface* tmp = IMG_Load( "data/nyan_cat.png" ); 
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




// // make
// // g++ lazyfoo_examples.cpp -framework SDL2 -framework SDL2_image -ISDL2 && ./a.out
// // 
// // SDL2_image is just needed for reading png files

// int main( int argc, char* args[] )
// {
//     // open_a_window(argc, args);
//     load_a_bmp_and_blit_it_to_the_screen( argc, args);
//     // respond_to_left_and_right_keyboard_events( argc, args);
//     // scale_an_image_and_optimise_it_for_faster_blitting( argc, args);
//     // lets_load_a_png( argc, args);
//     // use_textures_to_render_an_image( argc, args);

// }
