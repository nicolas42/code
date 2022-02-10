Shared libraries that are accessible from python can be made using the -shared option from gcc or clang.  This will create a dynamic library that 
is linkable at runtime.

The python ctypes library, or ffi presumably, can be used to interface with the object code.

gcc -shared -o libhello.so -fPIC hello.c

The above line will make a shared object which can be imported into python using its ctypes module.

---------------------------------------

from https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line

To generate a shared library you need first to compile your C code with the -fPIC (position independent code) flag.

gcc -c -fPIC hello.c -o hello.o
This will generate an object file (.o), now you take it and create the .so file:

gcc hello.o -shared -o libhello.so
EDIT: Suggestions from the comments:

You can use

gcc -shared -o libhello.so -fPIC hello.c





----------------------------------------------------------


clang -fPIC -shared ../draw_mandelbrot_in_color.c -o draw_mandelbrot_in_color.so  

# -std=c99 -pedantic -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -g   #-fsanitize=address

# -fPIC position independent code
# python mandelbrot.py


# clang -c -fPIC mandelbrot.c
# clang -c mandelbrot.c -shared -o mandelbrot.so 
