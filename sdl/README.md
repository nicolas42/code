# SDL frameworks

## How to make an SDL project using all of the frameworks.  (It'll still work if you're not using some of these)

clang++ a.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf -Wno-c++11-extensions



## Makefile foo whose function I've forgotten

CC = g++ $@.cpp -o $@


## Sometimes pkg-config can be used to find stuff :)

// g++ main.cpp `pkg-config --cflags --libs sdl2`


## Links

https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation



## Building and linking SDL in linux

Building and linking stuff between operating systems remains ridiculously challenging.

Build the source like

./configure && make && make install

then you can link a project like this

    gcc 1_open_a_window.c -lSDL2

to statically link I looked at sdl2-config

echo $(sdl2-config --static-libs)

It lists a bunch of linker flags which I used in addition to the .a files. 

    gcc 1_open_a_window.c libSDL2.a -ldl -lm -ldl -lpthread -lrt

The .a .la and .so files go into /usr/local.  You can get them from there.




## Building my examples

    sh make.sh <file.cpp>

for example 

    sh make.sh 5_show_mandelbrot.cpp

