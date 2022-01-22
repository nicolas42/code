// g++ render_text.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#define BASIC_IMPLEMENTATION 
#include "basic.h"


int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 400;
    int window_height = 400;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

    TTF_Init();
    char* font_path = (char*)"data/Sans.ttf";
    int font_size = 20;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        SDL_Log("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
      //      extern DECLSPEC void SDLCALL SDL_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...) SDL_PRINTF_VARARG_FUNC(1);
        exit(1);
    }


    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    int err;
    char *text = (char*)"Hello this is a long line now. Something that won't fit on one line perhaps.\nNow we will write many things and these things will be rendered in great and awesome detail on the screen.\nAnd oh my lord how the money rolled in. The count of montey cristo.\nWhy they oughtta file that under educational too.\n";

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Color text_color = {20,20,20,0};
    SDL_Color background_color = {255,255,255,0};

    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect rect;
    int x = 0;
    int y = 0;

    char glyph[2] = {'\0','\0'};
    for(int i=0; text[i]!='\0'; i+=1){

        glyph[0] = text[i];
        text_surface = TTF_RenderText_Shaded(font, glyph, text_color, background_color); 
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        rect.x = x;
        rect.y = y;
        rect.w = text_surface->w;
        rect.h = text_surface->h;

        // wrap
        if ( glyph[0] == '\n' || rect.x + text_surface->w > window_width ) {
            x = 0;
            y += text_surface->h;
            rect.x = x;
            rect.y = y;
        } 
        if ( glyph[0] != '\n') {
            SDL_RenderCopy(renderer, text_texture, NULL, &rect);
            x += text_surface->w;
        }

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    SDL_RenderPresent(renderer);




    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }


    // TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

