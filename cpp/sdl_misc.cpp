// g++ sdl_misc.cpp -Iinclude -framework SDL2 && ./a.out
// https://wiki.libsdl.org/SDL_CreateTexture

#include "SDL2/SDL.h"
#define SDL_STUFF_IMPLEMENTATION
#include "sdl_stuff.h"

/* Moving Rectangle */
int main(int argc, char *argv[])
{
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        SDL_Rect r;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
                return 3;
        }

        int window_width = 1000;
        int window_height = 800;
        window = SDL_CreateWindow("SDL_CreateTexture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, 0);


        SDL_Rect block_rect = make_rect( 0, 0, 100, 50 );
        SDL_Texture *block = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, block_rect.w, block_rect.h );

        SDL_Rect menu_rect = make_rect(0,0, window_width, 100);
        SDL_Texture *menu = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, menu_rect.w, menu_rect.h );
        SDL_SetRenderTarget(renderer, menu);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        SDL_RenderClear(renderer);

        SDL_Rect content_rect = make_rect(0, 100, window_width, window_height - 100 );
        SDL_Texture *content = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, content_rect.w, content_rect.h );
        SDL_SetRenderTarget(renderer, content);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, block);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, content);
        SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0x00);
        SDL_RenderClear(renderer);

        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;

                block_rect.x=rand()%(content_rect.w - block_rect.w);
                block_rect.y=rand()%(content_rect.h - block_rect.h);


                SDL_SetRenderTarget(renderer, content);
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, block, NULL, &block_rect);

                SDL_SetRenderTarget(renderer, NULL);
                SDL_RenderCopy(renderer, menu, NULL, &menu_rect);
                SDL_RenderCopy(renderer, content, NULL, &content_rect);

                SDL_RenderPresent(renderer);

                SDL_Delay(333);
        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}