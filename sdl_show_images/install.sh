cat $0
clang++ -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf -Wno-c++11-extensions show_images.cpp -o show_images
cp show_images ~/bin/show_images

