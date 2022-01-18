The SDL renderer has a VSYNC option which I should try
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );



Header-only libraries 
------------------------------

Lessons learned about how to make a header-file library
V1.0
September 2013 Sean Barrett

Things to do in an stb-style header-file library,
and rationales:


1. #define LIBRARYNAME_IMPLEMENTATION

Use a symbol like the above to control creating
the implementation. (I used a far-less-clear name
in my first header-file library; it became
clear that was a mistake once I had multiple
libraries.)

Include a "header-file" section with header-file
guards and declarations for all the functions,
but only guard the implementation with LIBRARYNAME_IMPLEMENTATION,
not the header-file guard. That way, if client's
header file X includes your header file for
declarations, they can still include header file X
in the source file that creates the implementation;
if you guard the implementation too, then the first
include (before the #define) creates the declarations,
and the second one (after the #define) does nothing.

https://github.com/nothings/stb/blob/master/docs/stb_howto.txt


ctype.h
--------------------------------

This library checks whether characters are in particular sets including 
whitespace, alphanumeric, numeric, alpha (a-z), printable, punctuation, hexidecimal,
upper or lowercase, and printable.  It also converts uppercase and lowercase letters
into one another.

#include <ctype.h>

isalpha isalphanum isdigit islower isupper isspace tolower toupper isxdigit, and others

all take an integer 



How to use errno 
-----------------------
The c standard library uses a global called errno.  
To print out the string that is associated with the number use strerror(errno)
from string.h


#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno ;

int main () {
   FILE *fp;

   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      fprintf(stderr, "Value of errno: %d\n", errno);
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
   } else {
      fclose(fp);
   }
   
   return(0);
}







// https://github.com/libsdl-org/SDL_ttf/blob/main/SDL_ttf.h

/* Get the dimensions of a rendered string of text */
extern DECLSPEC int SDLCALL TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h);
extern DECLSPEC int SDLCALL TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h);
extern DECLSPEC int SDLCALL TTF_SizeUNICODE(TTF_Font *font, const Uint16 *text, int *w, int *h);

/* Get the measurement string of text without rendering
   e.g. the number of characters that can be rendered before reaching 'measure_width'
   in:
   measure_width - in pixels to measure this text
   out:
   count  - number of characters that can be rendered
   extent - latest calculated width
*/
extern DECLSPEC int SDLCALL TTF_MeasureText(TTF_Font *font, const char *text, int measure_width, int *extent, int *count);
extern DECLSPEC int SDLCALL TTF_MeasureUTF8(TTF_Font *font, const char *text, int measure_width, int *extent, int *count);
extern DECLSPEC int SDLCALL TTF_MeasureUNICODE(TTF_Font *font, const Uint16 *text, int measure_width, int *extent, int *count);


goal: render a file of text

for that we need to render each word separately, making sure not to 