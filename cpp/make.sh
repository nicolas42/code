# echo $0
c_files=$(ls src/*.c)
cpp_files=$(ls src/*.cpp)
echo $c_files
echo $cpp_files

gcc -Isrc -Wall -Wpedantic -std=c99   -c $c_files 
gcc -Isrc -Wall -Wpedantic -std=c++14 -c $cpp_files 
ar rcs lib.a *.o
rm *.o 

