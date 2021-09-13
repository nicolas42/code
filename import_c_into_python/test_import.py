from mandelbrot import *

im = make_image(800,800,4)
draw_mandelbrot(im ,0,0,1,1000)
filename = "out.png"
save_image(im, filename.encode('ascii'))

