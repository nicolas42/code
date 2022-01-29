make(){
    g++ $1 -Iinclude -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer  -Wfatal-errors -Wall -Wpedantic -g -fsanitize=address  && ./a.out
}

for f in image_viewer.cpp play_audio.cpp render_text.cpp show_mandelbrot.cpp sobel_edge_detection.cpp make_primes.cpp misc.cpp
do 
    make $f
done 




