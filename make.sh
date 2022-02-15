make_run(){
    g++ $1 -Iinclude -Ofast -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fPIC  \
     -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer && ./a.out
}

make_run_linux(){
    g++ $1 -Iinclude -Ofast -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fPIC  \
      -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf  && ./a.out
}

make_run_all(){
    for f in examples/image_viewer.cpp examples/play_audio.cpp examples/render_text.cpp examples/show_mandelbrot.cpp examples/sobel_edge_detection.cpp examples/aggregated_demos.cpp
    do 
        make_run $f
    done 
}
