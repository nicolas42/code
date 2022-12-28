from math import *

ts = [ i/1000 for i in range(1,10000) ]
xs = [0]
ys = [0]

vx=50
vy=0
dt=0.1
i=0
g=10
b=0.00001



for i in range(0,1000):
    
    newx = xs[i] + vx*dt
    newy = ys[i] + vy*dt
    xs.append(newx)
    ys.append(newy)

    ax = -b*vx**2
    ay = -g - b*vy**2
    vx=vx +ax*dt
    vy=vy +ay*dt
#     print(vx,vy)



import matplotlib.pyplot as plt
import numpy as np
import math 

fig, ax = plt.subplots()
ax.plot(xs, ys, linewidth=2.0)
plt.show()

