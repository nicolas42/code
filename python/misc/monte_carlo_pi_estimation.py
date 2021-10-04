import random
import math

def estimate_pi_with_monte_carlo():

    random.seed()

    inside_circle = 0
    inside_square = 0

    for inside_square in range(1000000):
        x = random.random()
        y = random.random()
        # if math.sqrt(x**2 + y**2) <= 1:
        if x*x + y*y <= 1:
            inside_circle += 1

    # # inside_circle should be proportional to the area of a circle
    # # inside_square should be proportional to the area of a square
    # pi r^2
    # 4r^2

    pi_estimation = inside_circle / inside_square * 4

    print(pi_estimation)