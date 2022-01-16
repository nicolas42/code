// g++ play_music_and_sound_effects.cpp -I../cpp/SDL2 -framework SDL2 -framework SDL2_mixer -framework SDL2_image -I..

/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, SDL_mixer, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>


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
    // gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    //Initialize SDL_mixer
    int err = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    if (err) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    // music
    Mix_Music *music = NULL;
	music = Mix_LoadMUS( "beat.wav");
	if( !music ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    // sound effects
    Mix_Chunk *scratch = NULL;
	scratch = Mix_LoadWAV( "scratch.wav" );
	if( !scratch ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }

    Mix_Chunk *high = NULL;
	high = Mix_LoadWAV( "high.wav" );
	if( !high ) { printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); exit(1); }
	

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
