#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "basic.h"
#include "list_dir.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;


int main( int argc, char* argv[] )
{

	// printf("%d %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
	
	const char *dir;
	if (argc==2){
		dir = argv[1];
	} else {
        printf("show_images <dir>\n");
        return -1;
		dir = "/Users/nick/Downloads";
	}

	const char *desired_extensions[] = {"jpg", "png", "bmp", "jpeg"};
	std::vector<std::string> all_filenames;
	list_dir(dir, &all_filenames);

	std::vector<std::string> filenames;
	for (auto f : all_filenames) {
		const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
		for (auto desired_extension : desired_extensions ){
			if (strcmp(extension, desired_extension)==0) {
				filenames.push_back(f);
				// std::cout << f << std::endl;
				break;
			}
		}
	}

	for (auto i:filenames) std::cout << i << std::endl;
	int filenames_index = 0;
	const int filenames_length = filenames.size();


	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG & IMG_INIT_JPG );

	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Surface* image_surface;

	window = SDL_CreateWindow( "Press any key :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN ); // SDL_WINDOW_FULLSCREEN_DESKTOP ); // 

	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	window_surface = SDL_GetWindowSurface( window );

	bool gui_needs_updating = false;
	bool running = true;
	bool is_fullscreen = false;


    while (running)
    {
		SDL_Event event;
        SDL_WaitEvent(&event);
 
		switch (event.type){

		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym){

			case SDLK_RIGHT:
				filenames_index += 1;
				if ( filenames_index >= filenames_length ) filenames_index = 0;
				gui_needs_updating = true;
				break;

			case SDLK_LEFT:
				filenames_index += -1;
				if ( filenames_index < 0 ) filenames_index = filenames_length-1;
				gui_needs_updating = true;
				break;

			case SDLK_f:
				printf("Hello\n");
				if (is_fullscreen) {
					SDL_SetWindowFullscreen(window, 0);
				} else {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
				is_fullscreen = !is_fullscreen;
				
				break;

			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			filenames_index += -1;
			if ( filenames_index < 0 ) filenames_index = filenames_length-1;
			gui_needs_updating = true;
			break;

		}

		if (gui_needs_updating) {
			SDL_FreeSurface(image_surface);
			
			SDL_SetWindowTitle(window, filenames[filenames_index].c_str());
			image_surface = IMG_Load( filenames[filenames_index].c_str() );
			// image_surface = SDL_ConvertSurface( image_surface, window_surface->format, 0 );
			SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0));
			SDL_BlitSurface( image_surface, NULL, window_surface, NULL );
			SDL_UpdateWindowSurface( window );
			gui_needs_updating = false;
		}

    }


	SDL_FreeSurface( window_surface );
	SDL_FreeSurface( image_surface );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
