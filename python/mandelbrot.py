from ctypes import *

lib = CDLL("mandelbrot.so", RTLD_GLOBAL)

mandelbrot = lib.mandelbrot
mandelbrot.argtypes = [c_int, c_int, c_double, c_double, c_double, c_double]

if __name__ == "__main__":
    mandelbrot(1000,1000,0,0,4,4)





# https://docs.python.org/3/library/ctypes.html
# https://github.com/pjreddie/darknet/blob/master/python/darknet.py

# def c_array(ctype, values):
#     """d = c_array(c_float, [0.0]*256)"""
    
#     arr = (ctype*len(values))()
#     arr[:] = values
#     return arr

