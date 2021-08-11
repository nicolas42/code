cat $0

c_files=$(ls src/*.c)
cpp_files=$(ls src/*.cpp)

clang -std=c99 -Weverything -c -Isrc $c_files 
clang -std=c++14 -Weverything -c -Isrc $cpp_files 

ar rcs lib.a *.o
rm *.o

