cat $0
#cd $(dirname $0)
gcc ../src/mandelbrot.c -o mandelbrot.so   -fPIC -shared -std=c99 -pedantic -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -g   #-fsanitize=address
python mandelbrot.py
open mandelbrot.ppm 
