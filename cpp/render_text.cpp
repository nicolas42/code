// g++ render_text.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"


int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 400;
    int window_height = 400;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

    TTF_Init();
    char* font_path = (char*)"data/Sans.ttf";
    int font_size = 24;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        exit(1);
    }


    SDL_Rect rect;
    SDL_Surface *text_image;
    SDL_Texture *texture;

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    int length = 4;
    char text[4][100] = { "Hello", "world", "omg", "let's see if something else is good like this for a long line omgomgomg" };
    int i;
    for(i=0;i<length;++i) {
        int x = 0;
        int y = 0;
        if(i!=0) { y = rect.y+rect.h; }

        SDL_Color text_color = {20,20,20,0};
        SDL_Color background_color = {255,255,255,0};
        text_image = TTF_RenderText_Shaded(font, (char*)text[i], text_color, background_color); // TTF_RenderText_Solid doesn't smooth edges
        texture = SDL_CreateTextureFromSurface(renderer, text_image);
        rect.x = x;
        rect.y = y;
        rect.w = text_image->w;
        rect.h = text_image->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_FreeSurface(text_image);
        SDL_DestroyTexture(texture);
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



// void render_text(SDL_Renderer *renderer, int x, int y, char *text,
//         TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
//     int text_width;
//     int text_height;
//     SDL_Surface *surface;
//     SDL_Color textColor = {20,20,20,0};
//     SDL_Color backgroundColor = {255,255,255,0};

//     surface=TTF_RenderText_Shaded(font, text, textColor, backgroundColor);

//     *texture = SDL_CreateTextureFromSurface(renderer, surface);
//     text_width = surface->w;
//     text_height = surface->h;
//     SDL_FreeSurface(surface);
//     rect->x = x;
//     rect->y = y;
//     rect->w = text_width;
//     rect->h = text_height;
// }
