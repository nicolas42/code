cat $0
clang -fPIC -shared mandelbrot.c -o mandelbrot.so  # -std=c99 -pedantic -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -g   #-fsanitize=address
# -fPIC position independent code
# python mandelbrot.py


clang -c -fPIC mandelbrot.c
clang -c mandelbrot.c -shared -o mandelbrot.so 
