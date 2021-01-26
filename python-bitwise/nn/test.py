
# https://iamtrask.github.io/2015/07/12/basic-python-network/

# python -i twolayers.py
# run in interactive mode

import numpy as np

def sigmoid(x):
	return 1/(1+np.exp(-x))

def sigmoid_derivative(x):
    """ y = sigmoid(x) => y' = y(1-y) """
    return x*(1-x)

def relu(x):
	return np.maximum(0,x)

def relu_derivative(x):
    return np.where(x >= 0, 1, 0)

# Inputs and outputs
X = np.array([[0,0,0],
            [0,0,1],
            [0,1,0],
            [0,1,1],
            [1,0,0],
            [1,0,1],
            [1,1,0],
            [1,1,1]])
                
y = np.array([[0],
			[0],
			[0],
			[1],
			[0],
			[1],
			[1],
			[1]])



np.random.seed(1)

# randomly initialize our weights with mean 0
w1 = 2*np.random.random((3,4)) - 1
w2 = 2*np.random.random((4,4)) - 1
w3 = 2*np.random.random((4,1)) - 1


for j in range(60000):

	# Feed forward through layers
    a0 = X
    a1 = sigmoid(np.dot(a0,w1))
    a2 = sigmoid(np.dot(a1,w2))
    a3 = sigmoid(np.dot(a2,w3))

    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(y-a3))))

    # Backpropagation
    cost = y - a3
    l3 = cost * sigmoid_derivative(a3)
    l2 = (np.dot(l3, w3.T)) * sigmoid_derivative(a2)
    l1 = (np.dot(l2, w2.T)) * sigmoid_derivative(a1)

    w3 += np.dot(a2.T, l3)
    w2 += np.dot(a1.T, l2)
    w1 += np.dot(a0.T, l1)



np.set_printoptions(precision=3)
# np.set_printoptions(suppress=True)

print(a3)
