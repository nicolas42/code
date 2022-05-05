# make and run a bunch of cpp demos

files=$(echo "aggregated_demos.cpp buttons.cpp drag_and_drop.cpp image_viewer.cpp make_primes.cpp myprintf_demo.cpp opengl_orbit_demo.cpp paint.cpp play_audio.cpp png2jpg.cpp render_chaos_demo.cpp render_text.cpp sdl_demo_random_pixels.cpp sdl_draw_rectangle.cpp sdl_lazyfoo_examples.cpp show_mandelbrot.cpp sobel_edge_detection.cpp std_vector_is_slow_demo.cpp string_builder_demo.cpp" )
dir="."
include="../include"
# link code is different between mac and linux
if [ $(uname) = Linux ]
then
    link=$(echo "-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf") # !! Seems to need an opengl linker flag
fi
if [ $(uname) = Darwin ]
then
    link=$(echo "-framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer -framework opengl")
fi



for f in ${files}
do 
    printf "\n\n%s\n" "COMPILING AND RUNNING ${f}"
    printf "%s\n\n" "-----------------------------------------"

    g++ ${dir}/$f -I${include} -Ofast -fPIC \
    -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors \
    ${link} \
    && ./a.out
done 


