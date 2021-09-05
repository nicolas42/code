from ctypes import *

lib = CDLL("draw_mandelbrot_in_color.so", RTLD_GLOBAL)

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


# if __name__ == "__main__":

#     im = make_image(800,800,4)
#     draw_mandelbrot(im ,0,0,1,1000)
#     print(im.data[0])
#     filename = "out.png"
#     save_image(im, filename.encode('ascii'))





# https://docs.python.org/3/library/ctypes.html
# https://github.com/pjreddie/darknet/blob/master/python/darknet.py

# def c_array(ctype, values):
#     """d = c_array(c_float, [0.0]*256)"""
    
#     arr = (ctype*len(values))()
#     arr[:] = values
#     return arr

