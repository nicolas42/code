/*
 g++ render_text.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf

 cl /EHsc /Zi /I "win64\include\SDL2" "render_text.cpp" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\render_text.cpp.exe"

 /EHsc is to use vectors.  they need exceptions or something

 The SDL free functions take a long time.  Their overall duration is decreased if I put all the surface and texture pointers into a big array 
 and then free them all at the same time.  But calling free within a loop is bloody slow.

 The way to go appears to be to store textures for future use.  There's not that many glyphs to render after all.

*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
// #define BASIC_IMPLEMENTATION 
// #include "basic.h"

#include <stdio.h>
#include <stdlib.h>

enum rendering_strategy { 
    RENDER_SHADED, 
    RENDER_BLENDED, 
    RENDER_SOLID 
};

void render_text(SDL_Window *window, TTF_Font *font, const char *text, int y_offset, enum rendering_strategy rendering_strategy)
{

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    int window_width;
    int window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    int err;

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Color text_color = {20,20,20,0};
    SDL_Color background_color = {255,255,255,0};

    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect rect;
    int x = 0;
    int y = y_offset;

    int i;
    char glyph[2] = {'\0','\0'};
    // int font_height = TTF_FontHeight(font);
    
    uint32_t start_time = SDL_GetTicks();
    uint32_t rendering_time = 0;

    std::vector<SDL_Surface*> text_surfaces;
    std::vector<SDL_Texture*> text_textures;
    for(i=0; text[i]!='\0' && y < window_height; i+=1){


        uint32_t start_time1 = SDL_GetTicks();

        glyph[0] = text[i];
        if (rendering_strategy == RENDER_SHADED) text_surface = TTF_RenderText_Shaded(font, glyph, text_color, background_color); 
        else if (rendering_strategy == RENDER_BLENDED) text_surface = TTF_RenderText_Blended(font, glyph, text_color); 
        else if (rendering_strategy == RENDER_SOLID)  text_surface = TTF_RenderText_Solid(font, glyph, text_color );


        if (!text_surface) { SDL_Log(SDL_GetError()); }
        // SDL_Log("width: %d height: %d\n", text_surface->w, text_surface->h);

        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        rect.x = x;
        rect.y = y;
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        // SDL_Log("%d %d %d %d\n", rect.x, rect.y, rect.w, rect.h);
        
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


        text_surfaces.push_back(text_surface);
        text_textures.push_back(text_texture);
        // SDL_FreeSurface(text_surface);
        // SDL_DestroyTexture(text_texture);
        rendering_time += (SDL_GetTicks() - start_time1);

    }

    SDL_RenderPresent(renderer);

    SDL_Log("rendering time: %d\n", rendering_time );
    // freeing everything at once is faster
    for(int i=0;i<text_surfaces.size();i+=1) SDL_FreeSurface(text_surfaces[i]);
    for(int i=0;i<text_textures.size();i+=1) SDL_DestroyTexture(text_textures[i]);

    uint32_t total_time = SDL_GetTicks() - start_time;
    SDL_Log("total time: %d\n", total_time );

}



void print_event(SDL_Event event, bool show_mousemotion = false)
{
    if ( event.type == SDL_AUDIODEVICEADDED ) SDL_Log("SDL_AUDIODEVICEADDED\n");
    if ( event.type == SDL_AUDIODEVICEREMOVED ) SDL_Log("SDL_AUDIODEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERAXISMOTION ) SDL_Log("SDL_CONTROLLERAXISMOTION\n");
    if ( event.type == SDL_CONTROLLERBUTTONDOWN ) SDL_Log("SDL_CONTROLLERBUTTONDOWN\n");
    if ( event.type == SDL_CONTROLLERBUTTONUP ) SDL_Log("SDL_CONTROLLERBUTTONUP\n");
    if ( event.type == SDL_CONTROLLERDEVICEADDED ) SDL_Log("SDL_CONTROLLERDEVICEADDED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMOVED ) SDL_Log("SDL_CONTROLLERDEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMAPPED ) SDL_Log("SDL_CONTROLLERDEVICEREMAPPED\n");
    if ( event.type == SDL_DOLLARGESTURE ) SDL_Log("SDL_DOLLARGESTURE\n");
    if ( event.type == SDL_DOLLARRECORD ) SDL_Log("SDL_DOLLARRECORD\n");
    if ( event.type == SDL_DROPFILE ) SDL_Log("SDL_DROPFILE\n");
    if ( event.type == SDL_DROPTEXT ) SDL_Log("SDL_DROPTEXT\n");
    if ( event.type == SDL_DROPBEGIN ) SDL_Log("SDL_DROPBEGIN\n");
    if ( event.type == SDL_DROPCOMPLETE ) SDL_Log("SDL_DROPCOMPLETE\n");
    if ( event.type == SDL_FINGERMOTION ) SDL_Log("SDL_FINGERMOTION\n");
    if ( event.type == SDL_FINGERDOWN ) SDL_Log("SDL_FINGERDOWN\n");
    if ( event.type == SDL_FINGERUP ) SDL_Log("SDL_FINGERUP\n");
    if ( event.type == SDL_KEYDOWN ) SDL_Log("SDL_KEYDOWN\n");
    if ( event.type == SDL_KEYUP ) SDL_Log("SDL_KEYUP\n");
    if ( event.type == SDL_JOYAXISMOTION ) SDL_Log("SDL_JOYAXISMOTION\n");
    if ( event.type == SDL_JOYBALLMOTION ) SDL_Log("SDL_JOYBALLMOTION\n");
    if ( event.type == SDL_JOYHATMOTION ) SDL_Log("SDL_JOYHATMOTION\n");
    if ( event.type == SDL_JOYBUTTONDOWN ) SDL_Log("SDL_JOYBUTTONDOWN\n");
    if ( event.type == SDL_JOYBUTTONUP ) SDL_Log("SDL_JOYBUTTONUP\n");
    if ( event.type == SDL_JOYDEVICEADDED ) SDL_Log("SDL_JOYDEVICEADDED\n");
    if ( event.type == SDL_JOYDEVICEREMOVED ) SDL_Log("SDL_JOYDEVICEREMOVED\n");
    if (show_mousemotion) if ( event.type == SDL_MOUSEMOTION ) SDL_Log("SDL_MOUSEMOTION ");
    if ( event.type == SDL_MOUSEBUTTONDOWN ) SDL_Log("SDL_MOUSEBUTTONDOWN\n");
    if ( event.type == SDL_MOUSEBUTTONUP ) SDL_Log("SDL_MOUSEBUTTONUP\n");
    if ( event.type == SDL_MOUSEWHEEL ) SDL_Log("SDL_MOUSEWHEEL\n");
    if ( event.type == SDL_MULTIGESTURE ) SDL_Log("SDL_MULTIGESTURE\n");
    if ( event.type == SDL_QUIT ) SDL_Log("SDL_QUIT\n");
    if ( event.type == SDL_SYSWMEVENT ) SDL_Log("SDL_SYSWMEVENT\n");
    if ( event.type == SDL_TEXTEDITING ) SDL_Log("SDL_TEXTEDITING\n");
    if ( event.type == SDL_TEXTINPUT ) SDL_Log("SDL_TEXTINPUT\n");
    if ( event.type == SDL_USEREVENT ) SDL_Log("SDL_USEREVENT\n");
    if ( event.type == SDL_WINDOWEVENT ) SDL_Log("SDL_WINDOWEVENT\n");

    if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) SDL_Log("%s\n", SDL_GetKeyName(event.key.keysym.sym));

    fflush(stdout);
}


int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 800;
    int window_height = 800;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

    SDL_SetWindowTitle(window, "Press 1, 2, or 3 for different rendering modes.  The text should scroll using mouse wheel.");

    TTF_Init();
    char font_path[] = "c:/windows/fonts/verdana.ttf"; //"data/Sans.ttf";
    int font_size = 20;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) { SDL_Log("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError()); exit(1); }


    const char *text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    

    int y_offset = 0;
    enum rendering_strategy rendering_strategy = RENDER_SHADED;
    render_text(window, font, text , y_offset, rendering_strategy);


    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) == 1) {
            // print_event(e);

            // if(e.type = SDL_MOUSEMOTION) continue;

            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_MOUSEWHEEL){
                y_offset += 10*e.wheel.y;
                SDL_Log("%d %d\n", y_offset, e.wheel.y);
                render_text(window, font, text , y_offset, rendering_strategy);
            }
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_q) {
                    quit = 1;
                }
                else if (e.key.keysym.sym == SDLK_1) {
                    rendering_strategy = RENDER_BLENDED;
                }
                else if (e.key.keysym.sym == SDLK_2) {
                    rendering_strategy = RENDER_SHADED;
                }
                else if (e.key.keysym.sym == SDLK_3) {
                    rendering_strategy = RENDER_SOLID;
                }
                SDL_Log("render_strategy: %d\n", rendering_strategy);
                render_text(window, font, text , y_offset, rendering_strategy);

            }
        }
        SDL_Delay(10);
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

