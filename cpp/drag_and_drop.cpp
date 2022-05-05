//  g++ drag_and_drop.cpp -I../include -framework SDL2 && ./a.out

#include "SDL2/SDL.h"
#include <vector>
#include <random>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

struct Entity {
    SDL_Rect rect;
    struct color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } color;
};

void random_seed()
{
    srand(time(NULL));
}

double random_float()
{
    int r = rand();
    return ((double)r)/((double)RAND_MAX);
}

uint8_t random_u8()
{
    return (uint8_t)255*random_float();
}

int is_inside( int x, int y, SDL_Rect rect )
{
    return rect.x < x && x < (rect.x + rect.w) && rect.y < y && y < (rect.y + rect.h);
}

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 800;
    int window_height = 800;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "");

    std::vector<Entity> entities;
    // r.x = 100; r.y = 100; r.w = 100; r.h = 100;
    // entities.push_back(r);
    
    random_seed();

    SDL_Event event;
    bool quit = false;
    bool is_mouse_down = false;
    int selected = -1;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if ( SDL_QUIT == event.type ) {
                quit = true;
            }
            else if ( SDL_MOUSEBUTTONDOWN == event.type ) {
                int x,y;
                SDL_GetMouseState(&x,&y);
                for( int i=0; i<entities.size(); i+=1 ) {
                    if (is_inside(x,y, entities[i].rect)){
                        selected = i;
                    }
                }
                if (selected == -1) { // no faces are selected
                    Entity e;
                    e.rect.x = x; e.rect.y = y; e.rect.w = 100; e.rect.h = 100;
                    e.color.r = random_u8();
                    e.color.g = random_u8();
                    e.color.b = random_u8();
                    e.color.a = 255;
                    entities.push_back(e);
                    selected = entities.size()-1;
                }
                is_mouse_down = true;

                printf("%f\n", random_float());

            }
            else if ( SDL_MOUSEBUTTONUP == event.type ) {
                selected = -1;
                is_mouse_down = false;
            }
            else if ( SDL_MOUSEMOTION == event.type ) {
                if (selected != -1){
                    entities[selected].rect.x = event.motion.x;
                    entities[selected].rect.y = event.motion.y;
                }
            }
        }

        SDL_SetRenderDrawColor( renderer, 255,255,255,255);
        SDL_RenderClear( renderer );
        for(int i=0;i<entities.size();i+=1){
            Entity e = entities[i];
            SDL_SetRenderDrawColor( renderer, e.color.r, e.color.g, e.color.b, 255 );
            SDL_RenderFillRect(renderer, &(entities[i].rect));
        }
        SDL_RenderPresent( renderer );
        SDL_Delay(10);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



