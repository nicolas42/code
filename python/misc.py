import numpy as np

def blur(a):
    kernel = np.array([[1,1,1], [1,1,1], [1,1,1]])
    kernel = kernel / np.sum(kernel)
    arraylist = []
    for y in range(3):
        temparray = np.copy(a)
        temparray = np.roll(temparray, y - 1, axis=0)
        for x in range(3):
            temparray_X = np.copy(temparray)
            temparray_X = np.roll(temparray_X, x - 1, axis=1)*kernel[y,x]
            arraylist.append(temparray_X)

    arraylist = np.array(arraylist)
    arraylist_sum = np.sum(arraylist, axis=0)
    return arraylist_sum



def demo_get_sign_of_multivector():

    def bubble_sort(arr):
        # using adjacent swaps
        # move the highest value to the nth place
        # then move the second highest value to the n-1th place
        # and so on.

        n = len(arr)
        for i in range(n-1):
            for j in range(0, n-i-1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    print(arr)

    def get_sign_of_multivector(arr):
        # every time a swap occurs between different elements
        # the sign is negated
        # this is consistent with anticommutativity

        n = len(arr)
        sign = 1
    
        for i in range(n-1):
            for j in range(0, n-1-i):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    sign = -sign
                    print(arr)
        
        print(sign, list(set(arr)))

    # demo 
    # in r3 there's one scalar and 3 vectors
    # vectors anticommute
    # 0 1 2 3
    # 0 1 2 3 12 23 31 123
    # 3221
    multivector_directions = [ [],[1],[2],[3],[1,2],[2,3],[3,1],[1,2,3]]
    arr = [3,1]
    print(arr)
    get_sign_of_multivector(arr)
 


    
def demo_matplotlib():

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

    # demo
    plt.plot(*approximate_circle(n=20), color = 'blue')
    plt.plot(*approximate_circle_with_derivative(n=20), color='red')
    plt.ylabel('some numbers')
    plt.show()



import re
import sys

def read_file(filename):
    file = open(filename,'r')
    input_string = file.read()
    file.close()
    return input_string



def demo_split_at_regex():
    filename = 'GH010013.txt';
    output_filename = 'output.txt'
    regex_pattern = r'\nFPS:\d*\.\d*\s*AVG_FPS:\d*\.\d*\n\n\s*cvWriteFrame\s*\nObjects:\s*\n';

    input_string = read_file(filename)
    output_list = re.split(regex_pattern, input_string)

    # print items in output_list
    for _,v in enumerate(output_list):
        print('{' + v + '}')




from typing import NamedTuple

def named_tuple_demo():
    class SomeType(NamedTuple):
        x: int
        y: int 
        data: bytes
        z: int = 4 

    a = SomeType(1, 2, bytes([12,31,23,123,1]) )

    print(a)




import math
import numpy as np


def newtons_method(f, dfdx):

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


def print_on_one_line_demo():
    # Printing a carriage return \r character moves the caret to the beginning of the line
    # Printing a newline character \n moves the caret to the next line.
    # To print on one line simply print a carriage return prior to the line
    # This will overwrite the current line if it is not empty

    import time
    import sys

    for i in range(100):
        time.sleep(0.01)
        print('\rDownloading File FooFile.txt [%d%%]' % i, end="")
        sys.stdout.flush()
    print("")




def pwd(): 
    return os.getcwd()

def ls():
    return os.listdir()

def read(filename):
    f = open(filename, "rb")
    d=f.read()
    f.close()
    return d

# os.getenv("PATH")

def to_string(bytes_data):
    # works on improperly encoded data
    return ''.join(map(chr,bytes_data))



if __name__ == "__main__":
    demo_get_sign_of_multivector()
    # demo_matplotlib()
    # demo_split_at_regex()
    named_tuple_demo()
    demo_newtons_method()
    print_on_one_line_demo()