import numpy as np
import matplotlib.pyplot as plt

charity = 1

bx = [ 1000.0/i for i in range(1,101) ]

ax = [ 1 for i in range(0,100) ]
for i in range(0,100):
    # print(ax)
    ax = [ abs(np.random.normal(i, i/2)) + charity for i in ax ]
    ax.sort(reverse = True)
    fig = plt.figure()
    plt.plot(ax)
    plt.plot(bx)
    plt.ylabel('some numbers')
    plt.show()
