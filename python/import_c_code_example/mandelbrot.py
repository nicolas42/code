
# How to import data and functions from c into python. woo

# First compile a c file into a shared library with position independent code.
# then run

# all:
# 	clang -I../cpp/include -fPIC -shared mandelbrot.c -o mandelbrot.so  
# 	python mandelbrot.py
	


from ctypes import *

lib = CDLL("mandelbrot.so", RTLD_GLOBAL)

class IMAGE(Structure):
    _fields_ = [("w", c_int),
                ("h", c_int),
                ("c", c_int),
                ("data", POINTER(c_char))]


draw_mandelbrot = lib.draw_mandelbrot
draw_mandelbrot.argtypes = [IMAGE, c_double, c_double, c_double, c_double]
draw_mandelbrot.restype = None

make_image = lib.make_image
make_image.argtypes = [c_double, c_double, c_double]
make_image.restype = IMAGE

save_image = lib.save_image
save_image.argtypes = [IMAGE, POINTER(c_char)]
save_image.restype = c_int


if __name__ == "__main__":

    im = make_image(800,800,4)
    draw_mandelbrot(im ,0,0,1,1000)
    # print(im.data[0])
    filename = "out.png"
    save_image(im, filename.encode('ascii'))









# https://docs.python.org/3/library/ctypes.html
# https://github.com/pjreddie/darknet/blob/master/python/darknet.py




# The ctypes python package can be used to insert c code into python :).  There's some examples of how to do this in the darknet repo.

# gcc -shared -o libhello.so -fPIC hello.c

# The above line will make a shared object which can be imported into python using its ctypes module.

# ---------------------------------------

# from https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line

# To generate a shared library you need first to compile your C code with the -fPIC (position independent code) flag.

# gcc -c -fPIC hello.c -o hello.o
# This will generate an object file (.o), now you take it and create the .so file:

# gcc hello.o -shared -o libhello.so
# EDIT: Suggestions from the comments:

# You can use

# gcc -shared -o libhello.so -fPIC hello.c





# ----------------------------------------------------------


# clang -fPIC -shared ../draw_mandelbrot_in_color.c -o draw_mandelbrot_in_color.so  

# # -std=c99 -pedantic -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -g   #-fsanitize=address

# # -fPIC position independent code
# # python mandelbrot.py


# # clang -c -fPIC mandelbrot.c
# # clang -c mandelbrot.c -shared -o mandelbrot.so 
