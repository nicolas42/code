
How to import data and functions from c into python. woo

First compile a c file into a shared library with position independent code.
then run

all:
	clang -I../lib -fPIC -shared mandelbrot.c -o mandelbrot.so  
	python mandelbrot.py
	