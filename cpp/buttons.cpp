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

int is_inside(int x, int y, SDL_Rect r )
{
    return r.x < x && x < (r.x + r.w) && r.y < y && y < (r.y + r.h);
}

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

    // get textures from one big file
    SDL_Texture *joined_textures = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_Texture *textures[4];
    enum { MOUSEOUT, MOUSEOVER, MOUSEDOWN, MOUSEUP };  // for textures[MOUSEOUT], etc.
    for( int i = 0; i < 4; ++i ) {
        SDL_Rect srcrect = make_rect( 0, i * button_height, button_width, button_height ); 
        textures[i] = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button_width, button_height );
        SDL_SetRenderTarget(renderer, textures[i]);
        SDL_RenderCopy(renderer, joined_textures, &srcrect, NULL);
    }
    SDL_SetRenderTarget(renderer, NULL); // reset render target


    // draw textures onto window
    SDL_Rect rects[4]; // rectangles corresponding to different buttons
    for (int i=0;i<4;i+=1) {
        rects[i] = make_rect( i * button_width, 0, button_width, button_height );
        SDL_RenderCopy(renderer, textures[0], NULL, &(rects[i]) );
    }
    SDL_RenderPresent( renderer );


    int x,y;
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while ( SDL_PollEvent(&event) ) {

            if (event.type == SDL_QUIT) { quit = 1; }

            if ( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN ) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                SDL_GetMouseState(&x,&y);
                // SDL_Log("%d %d\n", x,y);
                for(int i=0;i<4;i+=1) {
                    if ( is_inside( x, y, rects[i] ) ) {
                        if ( event.type == SDL_MOUSEMOTION ) SDL_RenderCopy(renderer, textures[MOUSEOVER], NULL, &(rects[i]) );
                        if ( event.type == SDL_MOUSEBUTTONUP ) SDL_RenderCopy(renderer, textures[MOUSEUP], NULL, &(rects[i]) );
                        if ( event.type == SDL_MOUSEBUTTONDOWN ) SDL_RenderCopy(renderer, textures[MOUSEDOWN], NULL, &(rects[i]) );
                    } else {
                        SDL_RenderCopy(renderer, textures[MOUSEOUT], NULL, &(rects[i]) );
                    }
                }
                SDL_RenderPresent( renderer );
            }
        }
        SDL_Delay(10);

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}





















// // g++ buttons.cpp -Iinclude -framework SDL2 -framework SDL2_ttf && ./a.out


// #include <stdio.h>
// #include <stdlib.h>
// #include <vector>
// #include <string>

// #include "SDL2/SDL.h"
// #define SDL_STBIMAGE_IMPLEMENTATION
// #include "SDL_stbimage.h"

// #define SDL_STUFF_IMPLEMENTATION
// #include "sdl_stuff.h"

// typedef struct { SDL_Rect r; SDL_Texture *texture; } Interface;

// int is_inside( Interface face, int x, int y )
// {
//     return face.r.x < x && x < face.r.x + face.r.w && face.r.y < y && y < face.r.y + face.r.h;
// }

// int main(int argc, char **argv) {

//     int button_width = 300;
//     int button_height = 200;

//     SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
//     int window_width = 4 * button_width;
//     int window_height = button_height;
//     SDL_Renderer *renderer;
//     SDL_Window *window;
//     SDL_CreateWindowAndRenderer( window_width, window_height, 0, &window, &renderer );
//     // SDL_SetWindowTitle(window, "Scroll text using the mouse wheel or arrow keys.");



// 	SDL_Surface* surface = STBIMG_Load( "data/button.png" );
// 	if( !surface ) {
// 		printf( "ERROR %s %d %s\n", __FILE__,__LINE__,SDL_GetError() );
//         exit(1);
// 	}
//     // SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) ); // what does this do?
//     SDL_Texture *joined_images = SDL_CreateTextureFromSurface( renderer, surface );

//     SDL_Rect r;
//     SDL_Rect srcrect = make_rect( 0,0, button_width,button_height );

//     Interface faces[4];
//     for( int i = 0; i < 4; ++i ) {
//         srcrect.y = i * button_height;
//         faces[i].texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button_width, button_height );
//         SDL_SetRenderTarget(renderer, faces[i].texture );
//         SDL_RenderCopy(renderer, joined_images, &srcrect, NULL);
//     }

//     int i = 0;
//     srcrect.y = i * button_height;
//     faces[i].texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button_width, button_height );
//     SDL_SetRenderTarget(renderer, faces[i].texture );
//     SDL_RenderCopy(renderer, joined_images, &srcrect, NULL);


//     SDL_SetRenderTarget(renderer, NULL);
//     for( int i = 0; i < 4; ++i ) {
//         int w, h;
//         SDL_QueryTexture(faces[i].texture, NULL, NULL, &w, &h);
//         faces[i].r = make_rect( i*w, 0, w, h);
//         // SDL_RenderCopy(renderer, faces[i].texture, NULL, &(faces[i].r) );
//     }

//     // enum { MOUSEOUT, MOUSEOVER, MOUSEDOWN, MOUSEUP };
//     SDL_RenderPresent( renderer );


//     int x, y;
//     SDL_Event event;
//     int quit = 0;
//     while (!quit) {
//         while ( SDL_PollEvent(&event) ) {
//             // print_event(event);
//             if (SDL_QUIT == event.type) { quit = 1; }

//             if ( SDL_MOUSEMOTION == event.type ) {} 
//             if ( SDL_MOUSEBUTTONDOWN == event.type ) { }
//             if ( SDL_MOUSEBUTTONUP == event.type ) {
//                 SDL_GetMouseState(&x, &y);
//                 int faces_index;
//                 for( faces_index = 0; faces_index<4; faces_index+=1) {
//                     if ( is_inside( faces[faces_index], x, y ) ) break;
//                 }
//                 SDL_RenderCopy(renderer, [MOUSEUP], NULL, &(faces[faces_index].r) );
//                 SDL_RenderPresent( renderer );
//             }
//             if ( SDL_MOUSEOUT == event.type ) {}

//         }

//     }


//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return EXIT_SUCCESS;
// }



