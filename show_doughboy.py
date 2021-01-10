# importing cv2 
import cv2 
import sys
import math
import numpy as np
import importlib
import doughboy_config as config
import json



def draw_wave_at_frequency(image, frequency):

    sine_wave = []
    for i in range(config.samples + 1):
        x = config.periods * 2 * math.pi * i / config.samples
        sine_wave.append( (x, math.sin(frequency * x)) )
    print(sine_wave)

    for xy in sine_wave:
        center_coordinates = ( int( config.offset[0] + xy[0] * config.scaler[0] ), int( config.offset[1] - xy[1] * config.scaler[1] ) )
        print(center_coordinates)
        cv2.circle(image, center_coordinates, config.radius, config.color, config.thickness, lineType=cv2.LINE_AA)

    return image


i = 0
paused = False
while True:

    importlib.reload(config)

    image = np.zeros((config.height, config.width, 3), np.uint8)
    image[:, :] = config.background_color

    key = cv2.waitKey(config.key_wait) 
    if key in config.escape_keys:
        break
    elif key == config.pause_key: # space
        paused = not paused

    if not paused:
        i += 1
        frequency = 1 + i * config.frequency_increment
        image = draw_wave_at_frequency(image, frequency)
        cv2.imshow('window_name', image) 



cv2.destroyAllWindows()


