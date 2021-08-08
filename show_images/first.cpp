#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL2/SDL_image.h"
#include <vector>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;


int main( int argc, char* args[] )
{

	SDL_Init( SDL_INIT_VIDEO );
	SDL_Window* window = SDL_CreateWindow( "Press any key :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	SDL_Surface* window_surface = SDL_GetWindowSurface( window );

	SDL_Surface* bmp_surface = SDL_LoadBMP( "test.bmp" );





	IMG_Init( IMG_INIT_PNG & IMG_INIT_JPG );
	SDL_Surface* tmp_surface = IMG_Load( "7bf7d813b5984086a56a414e6921a3d6_md.jpg" );
	SDL_Surface* png_surface = SDL_ConvertSurface( tmp_surface, window_surface->format, 0 );
	SDL_FreeSurface( tmp_surface );





	//Apply the image
	SDL_BlitSurface( png_surface, NULL, window_surface, NULL );
	SDL_UpdateWindowSurface( window );


	std::vector<SDL_Surface*> surfaces;
	int surface_index = 0;
	surfaces.push_back(png_surface);
	surfaces.push_back(bmp_surface);

	SDL_Event e;
	bool quit = false;
	bool needs_update = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				needs_update = true;
				surface_index += 1;
				if ( surface_index > 1 ) surface_index = 0;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){

			}
			if (needs_update) {
				SDL_BlitSurface( surfaces.at(surface_index), NULL, window_surface, NULL );
				SDL_UpdateWindowSurface( window );
				needs_update = false;
			}

		}
	}




	SDL_FreeSurface( png_surface );
	SDL_FreeSurface( bmp_surface );
	SDL_DestroyWindow( window );
	SDL_Quit();


	return 0;
}
