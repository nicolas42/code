# pip3 install matplotlib

import matplotlib.pyplot as plt
import math


def approximate_circle(n = 10):
    X,Y = [], []
    for i in range(n+1):
        theta = i * 2 * math.pi / n
        X.append( math.cos(theta) )
        Y.append( math.sin(theta) )
    return X,Y

def approximate_circle_with_derivative(n = 10):
    dt = 2 * math.pi / n
    X,Y = [], []
    x,y,t = 1,0-dt/2,0,
    X.append(x); Y.append(y)

    for i in range(n):

        x = x - math.sin(t)*dt
        y = y + math.cos(t)*dt
        t = t + dt
        
        X.append(x)
        Y.append(y)
    return X,Y


    
if __name__ == "__main__":

    plt.plot(*approximate_circle(n=20), color = 'blue')
    plt.plot(*approximate_circle_with_derivative(n=20), color='red')

    plt.ylabel('some numbers')
    plt.show()
