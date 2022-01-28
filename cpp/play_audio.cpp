/*
g++ play_audio.cpp -Iinclude -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf -Wfatal-errors -fsanitize=address && ./a.out

call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /Zi /I "win64\include\SDL2" "play_audio.cpp" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\play_audio.cpp.exe" && win64\play_audio.cpp.exe
del *.obj *.pdb

based on code by the lazyfoo
*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <string>


typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;


#define DEFINE_ARRAY(TYPENAME)\
\
typedef struct {\
  TYPENAME* data;\
  int length;\
  int allocated;\
} TYPENAME ## _array;\
\
TYPENAME ## _array TYPENAME ## _array_make()\
{\
    TYPENAME ## _array arr;\
    arr.length = 0;\
    arr.allocated = 16;\
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
    return arr;\
}\
\
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)\
{\
    if ( arr.length == arr.allocated ) {\
      arr.allocated *= 2;\
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );\
    }\
    arr.data[arr.length] = item;\
    arr.length += 1;\
    return arr;\
}\





typedef char* string;
DEFINE_ARRAY(string);


// destructively split a string by converting delimiters into null bytes
// and noting down the positions after them.
string_array split_string(char *str, const char *delim)
{
    size_t string_length = strlen(str);

    // convert delimiters to null bytes
    for (int i = 0; i < string_length; i++ ) {
        for ( int j = 0; delim[j] != '\0'; j += 1 ) {
            if (str[i]==delim[j]) { 
                str[i] = '\0'; 
                break; 
            }
        }
    }

    string_array l = string_array_make();

    // add pointer to first element if it's not null
    if ( str[0] != '\0' ) l = string_array_add(l, str);
    for ( int i = 1; i < string_length; i++ ) {
        // add locations which are directly after null bytes
        if ( str[i-1] == '\0' && str[i] != '\0' ) l = string_array_add(l, str+i);
    }
    return l;
}




void stop_music(Mix_Music *music)
{
    Mix_HaltMusic(); // stop
}

void play_pause_music(Mix_Music *music)
{
    // If there is no music playing then play the music.
    // If the music is in being "played" then check whether the piece is paused of not
    // if it is paused then resume it, if it's not paused then pause it.
    // "Playing" music appears to be music that is loaded into the subsystem.

    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        } else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void play_sound_effect(Mix_Chunk *sound_effect)
{
    Mix_PlayChannel( -1, sound_effect, 0 );
}

int main( int argc, char* args[] )
{

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 400;
    int window_height = 400;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);  

    //Initialize SDL_mixer
    int err = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    if (err) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    // music
    Mix_Music *music = NULL;
	music = Mix_LoadMUS( "data/beat.wav");
	if( !music ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    // sound effects
    Mix_Chunk *scratch = NULL;
	scratch = Mix_LoadWAV( "data/scratch.wav" );
	if( !scratch ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    Mix_Chunk *high = NULL;
	high = Mix_LoadWAV( "data/high.wav" );
	if( !high ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }
	



    // Draw lines of text

    char text[] = 
        "SDLK_1 play_pause_music(music) \n"
        "SDLK_2 stop_music(music) \n"
        "SDLK_3 play_sound_effect(scratch) \n"
        "SDLK_4 play_sound_effect(high) \n";



    string_array lines = split_string(text,"\n");

    TTF_Init();
    char* font_path = (char*)"data/Sans.ttf";
    int font_size = 16;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        exit(1);
    }

    int extent = 0;
    int measure_width = 400;
    char line[1000];
    SDL_Color text_color = {20,20,20,0};
    SDL_Color background_color = {255,255,255,0};
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    int x = 0;
    int y = 0;

    for(int i=0;i<lines.length;++i){
        char *line = lines.data[i];
        SDL_Surface *text_surface = TTF_RenderText_Shaded(font, line, text_color, background_color); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        y += text_surface->h;

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(texture);

    }

    SDL_RenderPresent(renderer);












    SDL_Event e;
    int quit = 0;
    while (!quit) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
        if (e.type == SDL_KEYDOWN) {

            if (e.key.keysym.sym == SDLK_1) { play_pause_music(music); }
            if (e.key.keysym.sym == SDLK_2) { stop_music(music); }

            if (e.key.keysym.sym == SDLK_3) { play_sound_effect(scratch); }
            if (e.key.keysym.sym == SDLK_4) { play_sound_effect(high); }

        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	Mix_FreeMusic( music );
	Mix_FreeChunk( scratch );
	Mix_FreeChunk( high );
	Mix_Quit();
    SDL_Quit();

	return 0;
}
