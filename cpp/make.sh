make_run(){
    g++ $1 -Iinclude -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer  -Wfatal-errors -Wall -Wpedantic -g -fsanitize=address  && ./a.out
}

make_run_linux(){
    g++ $1 -Iinclude -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf -Wfatal-errors -Wall -Wpedantic -g -fsanitize=address  && ./a.out
}

# make and run all
for f in image_viewer.cpp play_audio.cpp render_text.cpp show_mandelbrot.cpp sobel_edge_detection.cpp make_primes.cpp misc.cpp
do 
    make_run $f
done 




