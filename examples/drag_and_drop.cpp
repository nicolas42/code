//  g++ drag_and_drop.cpp -I../include -framework SDL2 && ./a.out

#include "SDL2/SDL.h"
#include <vector>


int is_inside( int x, int y, SDL_Rect r )
{
    return r.x < x && x < (r.x + r.w) && r.y < y && y < (r.y + r.h);
}

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 800;
    int window_height = 800;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Scroll text using the mouse wheel or arrow keys.");

    std::vector<SDL_Rect> rx;
    SDL_Rect r;
    r.x = 100; r.y = 100; r.w = 100; r.h = 100;
    rx.push_back(r);

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
                for( int i=0; i<rx.size(); i+=1 ) {
                    if (is_inside(x,y, rx[i])){
                        selected = i;
                    }
                }
                if (selected == -1) { // no faces are selected
                    r.x = x; r.y = y; r.w = 100; r.h = 100;
                    rx.push_back(r);
                    selected = rx.size()-1;
                }
                is_mouse_down = true;

            }
            else if ( SDL_MOUSEBUTTONUP == event.type ) {
                selected = -1;
                is_mouse_down = false;
            }
            else if ( SDL_MOUSEMOTION == event.type ) {
                if (selected != -1){
                    rx[selected].x = event.motion.x;
                    rx[selected].y = event.motion.y;
                }
            }
        }


        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        
        for(int i=0;i<rx.size();i+=1){
            SDL_SetRenderDrawColor( renderer, 0, 0, 200, 255 );
            SDL_RenderFillRect(renderer, &(rx[i]));
        }
        SDL_RenderPresent( renderer );
        SDL_Delay(10);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



