# SDL frameworks

## How to make an SDL project using all of the frameworks.  (It'll still work if you're not using some of these)

clang++ a.cpp -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf -Wno-c++11-extensions



## Makefile foo whose function I've forgotten

CC = g++ $@.cpp -o $@


## Sometimes pkg-config can be used to find stuff :)

// g++ main.cpp `pkg-config --cflags --libs sdl2`
