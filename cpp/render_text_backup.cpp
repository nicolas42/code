// g++ render_text.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#define BASIC_IMPLEMENTATION 
#include "basic.h"


// destructively split a string by converting delimiters into null bytes
// and noting down the positions after them.
int split_string2( char *str, const char *delim, char ***arg_strings, int *arg_length )
{
    int allocated = 16;
    int length = 0;
    char ** strings = (char**)malloc(allocated*sizeof(char*));

    // convert delimiters to null bytes
    size_t string_length = strlen(str);
    int i=0;
    for (i=0;i<string_length;i++) {
        for (int j=0;delim[j]!='\0';j+=1) {
            if (str[i]==delim[j]) { str[i] = '\0'; break; }
        }

    }

    if (str[0] != '\0' ) strings[length++] = str;

    for (i=1; i<string_length; i++ ) {
        if ( str[i-1] == '\0' && str[i] != '\0' ) {
            if (length == allocated) {
                allocated *= 2;
                strings = (char**)realloc(strings, allocated*sizeof(char*));
            }
            strings[length++] = str+i;
        }
    }

    *arg_strings = strings;
    *arg_length = length;

    return 0;
}

DEFINE_ARRAY(int)

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


    // char text_to_render[] = "Hello this is a long line now. Something that won't fit omgomgomg\0\n";
    // // "hello\n"
    // // "world\n"
    // // "omg\n"
    // // "let's see if something else is good like this for a long line omgomgomg";

    // char **lines; 
    // int lines_length;
    // int err = split_string2( text_to_render, "\n\r", &lines, &lines_length );
    // for(int i=0;i<lines_length;i+=1) printf("{%s}\n", lines[i]);


    int err;
    char *lines[1] = {"Hello this is a long line now. Something that won't fit on one line perhaps."};
    int lines_length = 1;

    int x = 0;
    int y = 0;

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    for(int j=0; j<lines_length; j+=1 ) {
        // render text wrapped

        SDL_Color text_color = {20,20,20,0};
        SDL_Color background_color = {255,255,255,0};

        char *text = lines[j];
        char line[1000];
        int count, extent;


        // /* Create an 8-bit palettized surface and render the given text at
        // high quality with the given font and colors.  The 0 pixel is background,
        // while other pixels have varying degrees of the foreground color.
        // Text is wrapped to multiple lines on line endings and on word boundaries
        // if it extends beyond wrapLength in pixels.
        // If wrapLength is 0, only wrap on new lines.
        // This function returns the new surface, or NULL if there was an error.
        // */
        // uint32_t wrap_length = 20;
        // SDL_Surface * text_surface = TTF_RenderText_Shaded_Wrapped(font, text, text_color, background_color, wrap_length);
        // SDL_Texture * texture;
        // SDL_Rect rect;
        // rect.x = x;
        // rect.y = y;
        // rect.w = text_surface->w;
        // rect.h = text_surface->h;

        // SDL_RenderCopy(renderer, texture, NULL, &rect);
        // SDL_FreeSurface(text_surface);
        // SDL_DestroyTexture(texture);


        for(int i=0;;++i){


            err = TTF_MeasureText(font, text, window_width, &extent, &count);
            if (err) printf("%s\n", SDL_GetError());

            // memset(line, 0, sizeof line);
            // count +=1;
            memcpy(line, text, count);
            line[count] = '\0';
            printf("%d %d %s\n", extent, count, line);
            


            SDL_Surface *text_surface = TTF_RenderText_Shaded(font, line, text_color, background_color); 
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            int line_height = text_surface->h;
            SDL_RenderCopy(renderer, text_texture, NULL, &rect);
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);

            SDL_Log("strlen: %lu count: %d line: %s\n", strlen(text), count, line);


            if (strlen(text) == count) break;
            text += count;
            y += line_height;

        }
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






// void render_some_text(SDL_Renderer *renderer, TTF_Font *font)
// {


//     SDL_Rect rect;
//     SDL_Surface *text_image;
//     SDL_Texture *texture;

//     SDL_SetRenderDrawColor(renderer, 255,255,255,255);
//     SDL_RenderClear(renderer);

//     int length = 4;
//     char text[4][100] = { "Hello", "world", "omg", "let's see if something else is good like this for a long line omgomgomg" };
//     int i;
//     for(i=0;i<length;++i) {
//         int x = 0;
//         int y = 0;
//         if(i!=0) { y = rect.y+rect.h; }

//         SDL_Color text_color = {20,20,20,0};
//         SDL_Color background_color = {255,255,255,0};
//         text_image = TTF_RenderText_Shaded(font, (char*)text[i], text_color, background_color); // TTF_RenderText_Solid doesn't smooth edges
//         texture = SDL_CreateTextureFromSurface(renderer, text_image);
//         rect.x = x;
//         rect.y = y;
//         rect.w = text_image->w;
//         rect.h = text_image->h;
//         SDL_RenderCopy(renderer, texture, NULL, &rect);

//         SDL_FreeSurface(text_image);
//         SDL_DestroyTexture(texture);
//     }
//     SDL_RenderPresent(renderer);
// }




        // render wrapped text
        // To render text we need to separate it into lines.  This is either due to a newline in the text or because of line wrapping.
        // We can use the TTF_SizeText function to determine whether the next line of text will fit on the page.
        // If it won't then we can determine the length of the string to render using TTF_MeasureText
        
        // /* Get the dimensions of a rendered string of text */
        // extern DECLSPEC int SDLCALL TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h);
        // extern DECLSPEC int SDLCALL TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h);
        // extern DECLSPEC int SDLCALL TTF_SizeUNICODE(TTF_Font *font, const Uint16 *text, int *w, int *h);

        // extern DECLSPEC int SDLCALL TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h);

        // int w,h;
        // int index = strchr(text,'\n');
        // // err = TTF_SizeText(font, text, &w, &h);
	

