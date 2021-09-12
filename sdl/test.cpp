// g++ -std=c++14 test.cpp -framework SDL2 -framework SDL2_image -framework SDL2_ttf

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>


#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char **argv) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surface;





    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800, 800, 0, &window, &renderer);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Sans.ttf", 24);
    char text[] = "Hello World!";
    SDL_Color text_color = {255, 255, 255, 0};
    SDL_Color background_color = {0,0,0,0};
    surface = TTF_RenderText_Shaded(font, text, text_color, background_color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;


    SDL_Event event;
    int running = 1;
    while (running) {
        SDL_WaitEvent(&event);
        fprintf(stdout, "event! ");
        fflush(stdout);
        if (event.type == SDL_QUIT) running = 0;

        // clear, render, and present (copy the buffer?)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }




    SDL_DestroyTexture(texture);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
