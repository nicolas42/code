/*
macos:
g++ -ISDL2 -framework SDL2 -framework SDL2_image -std=c++11 image_viewer.cpp

linux:
	g++ -ISDL2 -lSDL2 -lSDL2_image -std=c++11 image_viewer.cpp
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h> /* "readdir" etc. are defined here. */
#include <limits.h> /* limits.h defines "PATH_MAX". */

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
// #include "find_files.h"

void find_files (const char * dir_name, std::vector<std::string> *output)
{
    /* this function is from lemoda.net */

    // std::vector<std::string> output;
    std::string buff = "";

    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
	// printf ("%s/%s\n", dir_name, d_name);

    buff = "";
    buff += dir_name;
    buff += "/";
    buff += d_name;
    // buff += "\n";
    output->push_back(buff);

#if 0
	/* If you don't want to print the directories, use the
	   following line: */

        if (! (entry->d_type & DT_DIR)) {
	    // printf ("%s/%s\n", dir_name, d_name);

        buff = "";
        buff += dir_name;
        buff += "/";
        buff += d_name;
        // buff += "\n";
        output->push_back(buff);
	}

#endif /* 0 */


        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                // printf ("%s\n", path);

                buff = "";
                buff += path;
                // buff += "\n";
                output->push_back(buff);


                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "find_files" with the new path. */
                find_files (path,output);
            }
	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }


}

// int list_dir_main (int argc, char **argv)
// {
//     // char *dir = argv[1]; // "/Users/nick/Downloads";
//     const char *dir = "/Users/nick/Downloads";

	// std::vector<std::string> files;
	// find_files("/Users/nick/Downloads", &files);
	// for (auto f : files) {
	// 	const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
	// 	if (strcmp(extension, "jpg")==0) std::cout << f << std::endl;
	// 	// std::cout << extension << std::endl;
	// 	// std::cout << f << std::endl;
	// }
// }

double min(double a, double b)
{
    if (a<b) return a;
    return b;
}

void show( SDL_Window *window, std::vector<std::string> filenames, int filenames_index ) 
{
    if (filenames.size() == 0) return;
    std::cout << "show: " << filenames[filenames_index] << std::endl;

    SDL_Surface *window_surface = SDL_GetWindowSurface( window );
    SDL_Surface* image_surface;
    SDL_Surface *optimised_image_surface;

    // set title to filename
    SDL_SetWindowTitle(window, filenames[filenames_index].c_str());

    // optimise image
    image_surface = IMG_Load( filenames[filenames_index].c_str() );
    if(!image_surface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        return;
    }

    optimised_image_surface = SDL_ConvertSurface( image_surface, window_surface->format, 0 );
    SDL_FreeSurface(image_surface);

    // draw optimised
    SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0));

    // resize to fit inside window
    double width_scaler = ((double)window_surface->w) / ((double)image_surface->w);
    double height_scaler = ((double)window_surface->h) / ((double)image_surface->h);
    double scaler = min(width_scaler, height_scaler);
    
    SDL_Rect image_size;
    image_size.w = (int)(scaler * image_surface->w);
    image_size.h = (int)(scaler * image_surface->h);
    image_size.y = (window_surface->h - image_size.h)/2;
    image_size.x = (window_surface->w - image_size.w)/2;

    SDL_BlitScaled( optimised_image_surface, NULL, window_surface, &image_size );
    SDL_FreeSurface(optimised_image_surface);

    SDL_UpdateWindowSurface( window );
    
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
    // https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
}

std::vector<std::string> get_image_filenames (char *f)
{
    // get image filenames
    std::vector<std::string> filenames;
    if (!strcmp(f,"")) return filenames;

	const char *desired_extensions[] = {"jpg", "png", "bmp", "jpeg"};
	std::vector<std::string> all_filenames;

    if ( is_dir(f) ) { 
        find_files(f, &all_filenames); 
    } else {
        // assume it's an image file
        filenames.push_back(f);
    }

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
    return filenames;
    
}

int main( int argc, char* argv[] )
{
    int window_width = 800;
    int window_height = 800;
	bool time_to_quit = false;
	bool is_fullscreen = false;


	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Event event;
	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG & IMG_INIT_JPG );
	window = SDL_CreateWindow( "Drag a directory onto the window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ); 
	window_surface = SDL_GetWindowSurface( window );
    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);


    // terminal
	char *dir = (char*)"";
    // if (argc == 1) printf("show_images <dir>\n");
	// if (argc==2){
	// 	dir = argv[1];
	// }
    

    std::vector<std::string> filenames;
    int filenames_index;
    char* dropped_filename;                  // Pointer for directory of dropped file

    filenames = get_image_filenames(dir);
	filenames_index = 0;
	show( window, filenames, filenames_index );

    while (!time_to_quit)
    {
        SDL_WaitEvent(&event);

		switch (event.type){

        case (SDL_DROPFILE): {      // In case if dropped file
            dropped_filename = event.drop.file;
            // Shows directory of dropped file
            // SDL_ShowSimpleMessageBox(
            //     SDL_MESSAGEBOX_INFORMATION,
            //     "File dropped on window",
            //     dropped_filename,
            //     window
            // );
            filenames = get_image_filenames(dropped_filename);
            filenames_index = 0;
            show( window, filenames, filenames_index );

            SDL_free(dropped_filename);    // Free dropped_filename memory
            break;
        }

		case SDL_QUIT:
			time_to_quit = true;
			break;

        case SDL_WINDOWEVENT:
            // printf("window event %d\n", (int)(event.window.event) );
            show( window, filenames, filenames_index );
            break;

		case SDL_KEYDOWN:

			if ( event.key.keysym.sym == SDLK_RIGHT ) {
				filenames_index += 1;
				if ( filenames_index >= filenames.size() ) filenames_index = 0;
				show( window, filenames, filenames_index );
            }

            if ( event.key.keysym.sym == SDLK_LEFT ) {
				filenames_index += -1;
				if ( filenames_index < 0 ) filenames_index = filenames.size()-1;
				show( window, filenames, filenames_index );
            }
            
            if ( event.key.keysym.sym == SDLK_f ) {
				if (is_fullscreen) {
					SDL_SetWindowFullscreen(window, 0);
				} else {
					SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN_DESKTOP );
				}
				is_fullscreen = !is_fullscreen;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			filenames_index += -1;
			if ( filenames_index < 0 ) filenames_index = filenames.size()-1;
			show( window, filenames, filenames_index );
			break;
		}

    }

	// SDL_FreeSurface( window_surface );
	// SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}



// SDL_Log("Window %d resized to %dx%d",
//     event.window.windowID, event.window.data1,
//     event.window.data2);
// window_width = event.window.data1;
// window_height = event.window.data2;
