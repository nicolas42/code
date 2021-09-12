# SDL frameworks

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