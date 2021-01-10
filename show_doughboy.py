# importing cv2 
import cv2 
import sys
import math

def draw_doughboy(image, frequency):

    # frequency = 2
    periods = 2
    samples = 30
    sine_wave = []
    for i in range(samples + 1):
        x = periods * 2 * math.pi * i / samples
        sine_wave.append( (x, math.sin(frequency * x)) )

    print(sine_wave)

    for xy in sine_wave:

        offset = ( 50, 200 )
        radius = 3
        color = (0,0,0)
        thickness = -1
        scaler = (50, 50)

        center_coordinates = ( int( offset[0] + xy[0]*scaler[0] ), int( offset[1] - xy[1]*scaler[1] ) )
        print(center_coordinates)
        cv2.circle(image, center_coordinates, radius, color, thickness, lineType=cv2.LINE_AA)

    return image



# path = sys.argv[1]
path = '/Users/nick/Downloads/IMG_9360.jpg'
image = cv2.imread(path)

for i in range(1000):
    frequency = 1 + i/100
    image_copy = draw_doughboy(image.copy(), frequency)
    cv2.imshow('window_name', image_copy) 
    cv2.waitKey(33)

cv2.destroyAllWindows()


