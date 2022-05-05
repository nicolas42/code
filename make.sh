
# make_run_linux
# g++ $1 -Iinclude -Ofast -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fPIC -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf  && ./a.out

# make and run in macos
dir="cpp"
for f in ${dir}/image_viewer.cpp ${dir}/play_audio.cpp ${dir}/render_text.cpp ${dir}/show_mandelbrot.cpp ${dir}/sobel_edge_detection.cpp ${dir}/aggregated_demos.cpp
do 
    g++ $f -Iinclude -Ofast -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fPIC -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer && ./a.out
done 


