import pygame
import math
import importlib
import config
import colorsys

def hsv2rgb(h, s, v):
    """ Converts HSV values to RGB. Input and output ranges are 0..1. """
    return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h, s, v))

def draw_wave_at_frequency(screen, frequency):
    screen.fill(config.background_color)  # Clear the screen with background color

    sine_wave = []
    for i in range(config.samples + 1):
        x = config.periods * 2 * math.pi * i / config.samples
        y = math.sin(frequency * x)
        sine_wave.append((x, y))

    prev_x = prev_y = None
    for xy in sine_wave:
        if config.rainbow_color:
            max_x = sine_wave[-1][0]
            color = hsv2rgb(xy[0] / max_x, 1, 1)
        else:
            color = config.color

        scaled_x = int(config.offset[0] + xy[0] * config.scaler[0])
        scaled_y = int(config.offset[1] - xy[1] * config.scaler[1])

        if prev_x is not None and prev_y is not None:
            pygame.draw.line(screen, color, (prev_x, prev_y), (scaled_x, scaled_y), config.radius)
        prev_x, prev_y = scaled_x, scaled_y

    pygame.display.flip()  # Update the display

def main():
    pygame.init()
    screen = pygame.display.set_mode((config.width, config.height))
    pygame.display.set_caption('Dynamic Frequency Waves')

    running = True
    frequency = 1
    clock = pygame.time.Clock()

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE or event.key == pygame.K_q:
                    running = False

        draw_wave_at_frequency(screen, frequency)
        frequency += config.frequency_increment
        clock.tick(60)  # Cap the frame rate at 60 FPS

    pygame.quit()

if __name__ == "__main__":
    main()
