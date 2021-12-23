

import math
import numpy as np


def newtons_method(f, dydx):

    # Newton's method approximates solutions to equations by successive calculation of 
    # tangent lines. It requires an initial starting point.  Different starting points 
    # will yield different solutions. 

    # An arbitrary tangent line of a curve that goes through point (x0,y0) can be 
    # formulated as y-y0 = m(x-x0).  The x-intercept of this line is (-y0 / m + x0)

    equality_distance = 1e-10 # float equality is defined as being closer than this
    decimal_places = 5 # needs to be low enough to prevent duplicate solutions

    solutions = set()
    for x in np.arange(-100,100, 0.1):
        while True:
            y = f(x)
            dydx = dfdx(x)
            x_next = -y / dydx + x 
            if abs(x_next - x) < equality_distance:
                break
            x = x_next
        solutions.add(round(x, decimal_places))
    
    return sorted(solutions)
    print(solutions)

def demo_newtons_method():
    f = lambda x : 1 -23*x + 12*x**2 + 213*x**3
    dfdx = lambda x : -23 + 24*x + 213*3*x**2
    solutions = newtons_method(f, dfdx)
    print(solutions)
