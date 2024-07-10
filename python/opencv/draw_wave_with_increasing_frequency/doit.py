import tkinter as tk
import math
import importlib
import config
import colorsys

def hsv2rgb(h, s, v):
    """Converts HSV values to RGB. Input and output ranges are 0..1."""
    return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h, s, v))

def draw_wave_at_frequency(canvas, frequency):
    canvas.delete("wave")  # Clear previous wave

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
            fill_color = f"#{int(color[0]):02x}{int(color[1]):02x}{int(color[2]):02x}"
        else:
            fill_color = f"#{int(config.color[0]):02x}{int(config.color[1]):02x}{int(config.color[2]):02x}"

        scaled_x = config.offset[0] + xy[0] * config.scaler[0]
        scaled_y = config.offset[1] - xy[1] * config.scaler[1]

        if prev_x is not None and prev_y is not None:
            canvas.create_line(prev_x, prev_y, scaled_x, scaled_y, fill=fill_color, width=config.radius, tags="wave")
        prev_x, prev_y = scaled_x, scaled_y

def update_wave(frequency):
    draw_wave_at_frequency(canvas, frequency)
    window.after(config.key_wait, lambda: update_wave(frequency + config.frequency_increment))

window = tk.Tk()
window.title('Wave Drawer')

canvas = tk.Canvas(window, width=config.width, height=config.height, bg='#ffffff')
canvas.pack()

update_wave(1)  # Start with frequency 1

window.mainloop()
