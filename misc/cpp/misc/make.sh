# g++ -std=c++11  -Iinclude/  -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -flto -Ofast -c 
# gcc -Iinclude/  -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -flto -Ofast -c

# g++ -std=c++11  -Iinclude/  -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -flto -Ofast -c image_opencv.cpp

gcc -c src/*.c
ar rcs lib.a *.o 
rm *.o 

