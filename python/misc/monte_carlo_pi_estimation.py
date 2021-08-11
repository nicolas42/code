"""
The ratio of the area of a circle to the area of a square that encloses it is
pi r^2 / 4 r^2 = Probability( being in the circle )
4*P(C) = pi
So to estimate pi we randomly throw darts at an imaginary circle and we use the ratio
ratio of the darts that land inside circle to the darts that land inside the
enclosing square to determine the the probability.  Four times this probability
should estimate pi.
"""

import random
import math

random.seed()

c = 0
s = 0
while(s <= 1e6):
    s = s + 1
    x = random.random()
    y = random.random()

    # r = math.sqrt( x**2 + y**2 )
    r = x**2 + y**2 # since r=1 the sqrt is not needed to determine whether we are inside or outside of the circle

    if r <= 1:
        c = c + 1


print(4*c/s)

# ÷