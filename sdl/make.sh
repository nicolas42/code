make(){
    g++ -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf $1 -o $1.out && ./$1.out
}

for f in $(ls *.cpp); do 
    echo $f; 
    make $f
done 




