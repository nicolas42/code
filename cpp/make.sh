make(){
    g++ -ISDL2 -framework SDL2 -framework SDL2_image -framework SDL2_ttf -std=c++11 $1 -o $1.out && ./$1.out
}

for f in $(ls *.cpp); do 
    echo "-------------------------------"
    echo $f; 
    echo "-------------------------------"
    make $f
done 


rm *.out

