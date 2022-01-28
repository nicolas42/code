
Header only libraries
----------------------------------------------

A header only library of the sort used by the stb library works by only 
including implementation of a header library if a particular define is set.
Usually it's called XX_IMPLEMENTATION.  The idea being that the header file 
can still be used normally.  Importantly in *ONE* file and only one file 
the previously mentioned define is set.  And that is the file that actually
includes the implementation.


Only define BASIC_IMPLEMENTATION in *ONE* file, like this.

#define BASIC_IMPLEMENTATION
#include "basic.h"


The header only file will look like this.  In addition to header guards to 
prevent multiple includes, there is an ifdef on BASIC_IMPLEMENTATION.
There's also a header guard for the implementation, because why not.




#ifndef BASIC_HEADER_GUARD
#define BASIC_HEADER_GUARD


.......


#endif // BASIC_HEADER_GUARD

#ifdef BASIC_IMPLEMENTATION

#ifndef BASIC_IMPLEMENTATION_GUARD
#define BASIC_IMPLEMENTATION_GUARD

.......

#endif // BASIC_IMPLEMENTATION_GUARD 

#endif // #ifdef BASIC_IMPLEMENTATION






Does a global signal flag need to be atomic?
------------------------------------------------

static int sigflag = 0;
sig_atomic_t sigflag = 0;
sig_atomic_t is an integer type which can be accessed as an atomic entity even in the presence of asynchronous interrupts made by signals.
could I just use a mutex?
It appears that atomic things are more efficient than mutexes

"Atomic operations leverage processor support (compare and swap instructions) and don't use locks at all, whereas locks are more OS-dependent and perform differently on, for example, Win and Linux.
Locks actually suspend thread execution, freeing up cpu resources for other tasks, but incurring in obvious context-switching overhead when stopping/restarting the thread. On the contrary, threads attempting atomic operations don't wait and keep trying until success (so-called busy-waiting), so they don't incur in context-switching overhead, but neither free up cpu resources.
Summing up, in general atomic operations are faster if contention between threads is sufficiently low. You should definitely do benchmarking as there's no other reliable method of knowing what's the lowest overhead between context-switching and busy-waiting."
https://stackoverflow.com/questions/15056237/which-is-more-efficient-basic-mutex-lock-or-atomic-integer







Compiling Stuff on Windows Using Visual Studio on the command line   #visualstudio 
----------------------------------------------------------------------------------------

Calling visual studio from the command line (cl) requires a script be run beforehand.
It's called vcvarsall.bat and it moves around every new version so you'll have to find it.
It's buried somewhere in the visual studio folder, which itself will change. yay :)

Here are the commands from the last time that I used them.

   call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

   cl /Zi /MD main.c


source: https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017


The imgui repo has a bunch of examples of how to use visual studio.  Here's one

    mkdir Debug

    cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib

    del *.pdb *.ilk *.obj 





Setting the PATH environmental variable in windows
-------------------------------------------------------
SET PATH=%PATH%;c:\users\nick\bin



Building and Linking C/C++ Repositories in Linux / macos   #pkg-config
-------------------------------------------------------------------------

To link libraries in macos use the -framework flag, e.g.

   g++ main.cpp -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf


To link libraries in Linux use -l<lib name>.  The library name is the filename without its "lib" prefix 
and without the file extension.  

    g++ main.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf




pkg-config is a useful utility that gives the linking flags that are required for different libraries, if they're more complicated.
It can also output the flags necessary to statically link libraries, which is cool.

   pkg-config --libs sdl2 opengl



.A libraries (archive)

.a libraries are a bunch of .o objects stuck together.  They can easily be linked on the command line by just putting in their name like a .c or a .o file.

   g++ main.c lib.a


.a libraries can be produced with the ar tool.

   ar rcs lib.a  sth.o sthelse.o









backup of make.sh for all the sdl files
-----------------------------------

make(){
    g++ -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf -std=c++11 $1 -o $1.out && ./$1.out
}

for f in $(ls *.cpp); do 
    echo "-------------------------------"
    echo $f; 
    echo "-------------------------------"
    make $f
done 


rm *.out





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



---------------------------------------------------------------
Old README.md File
---------------------------------------------------------------





make(){
    g++ -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf $1 -o $1.out && ./$1.out
}

for f in $(ls *.cpp); do 
    echo $f; 
    make $f
done 





# SDL frameworks

## To Do - How to install SDL, opengl, glew on different operating systems and link with your programs

How to make the thing

install SDL and SDL_image with a package manager or from https://libsdl.org/download-2.0.php

run something like this

macos:
	g++ -ISDL2 -framework SDL2 -framework SDL2_image -std=c++11 show_images.cpp 

linux:
	g++ -ISDL2 -lSDL2 -lSDL2_image -std=c++11 show_images.cpp


## Make all the SDL extensions!

clang++ a.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf


what does this mean?

-Wno-c++11-extensions


## Makefile foo whose function I've forgotten

CC = g++ $@.cpp -o $@


## Sometimes pkg-config can be used to find stuff :)

// g++ main.cpp `pkg-config --cflags --libs sdl2`


## Links

https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation



## Building and linking SDL in linux

Building and linking stuff between operating systems remains ridiculously challenging.

Build SDL

./configure; make; make install

then you can link a project like this

    gcc 1_open_a_window.c -lSDL2

to statically link do this

    gcc 1_open_a_window.c ~/lib/libSDL2.a -ldl -lm -ldl -lpthread -lrt

I found the link flags from sdl2-config, specifically $(sdl2-config --static-libs)



## Notes

difference between surface and texture
https://stackoverflow.com/questions/21392755/difference-between-surface-and-texture-sdl-general

seems like a surface and a texture are both images but a texture is hardware rendered.
