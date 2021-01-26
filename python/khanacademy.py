from math import *
from find_roots import *

"""
f=lambda x: -18/x 
g=lambda x: x**2 +10*x +27
# h = g-f
h = lambda x: x**2 +10*x +27 +18/x
hdash = lambda x: 2*x +10 -18/x**2

r=find_roots(h,hdash,range(-100,100))
print(r)
#[-6.0, -3.0, -1.0]
H = lambda x: x**3/3 +5*x**2 +27*x +18*log(abs(x))
r = abs(H(-3)-H(-6)) + abs(H(-1)-H(-3))
print(r)
"""

"""
f=lambda x: sin(pi*sqrt(x/2))
g=lambda x: -4/21*x*(x-10/3)
# h = g-f
h = lambda x: -4/21*x*(x-10/3) - sin(pi*sqrt(x/2))
hdash = lambda x: -4/21*(2*x-10/3) - cos(pi*sqrt(x/2))*pi/2/sqrt(2*x)

r=find_roots(h,hdash,range(0,100))
r=[0, 1.3732974, 4.5]
H = lambda x: -4/21*(x**3/3-10/3*x**2/2) - 4/pi**2 *sin(pi*sqrt(x/2)) + 2*sqrt(2*x)/pi * cos(pi*sqrt(x/2))
area = abs(H(r[1])-H(r[0])) + abs(H(r[2])-H(r[1]))
print(area)

"""

f=lambda x: 
g=lambda x: 
# h = g-f
h = lambda x: 
hdash = lambda x: 

r=find_roots(h,hdash,range(0,100))
r=[0, 1.3732974, 4.5]
H = lambda x: 
area = abs(H(r[1])-H(r[0])) + abs(H(r[2])-H(r[1]))
print(area)


