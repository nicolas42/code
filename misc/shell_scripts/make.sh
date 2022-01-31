cat $0
gcc -Isrc -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -std=c99   -c src/*.c
gcc -Isrc -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -std=c++14 -c src/*.cpp
ar rcs lib.a *.o
rm *.o 

