# # Pareto distribution from stochastic processes

# A random process where income is derived only as a function of your current wealth quickly produces a pareto wealth distribution.

# In fact in order to prevent most of the curve from going to zero, a small charity term had to be added.

# There's 100 actors.  Each actors income for the next time step is randomly chosen from a normal distribution that is centered at the 



import numpy as np
import matplotlib.pyplot as plt

charity = 1

# pareto_distribution = [ 1000.0/x for x in range(1,101) ]
randomly_derived_distribution = [ 1 for x in range(0,101) ]

fig = plt.figure()
for x in range(0,50):
    # print(randomly_derived_distribution)
    randomly_derived_distribution = [ x + abs(np.random.normal(0, x/2)) for x in randomly_derived_distribution ]
    randomly_derived_distribution.sort(reverse = True)
    plt.clf()
    plt.plot(randomly_derived_distribution)
    # plt.plot(pareto_distribution)
    plt.ylabel('some numbers')
    plt.legend(["random", "pareto"])
    plt.pause(0.5)

plt.show()
