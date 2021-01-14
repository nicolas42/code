from https://cython.readthedocs.io/en/latest/src/quickstart/build.html

Imagine a simple “hello world” script in a file hello.pyx:

def say_hello_to(name):
    print("Hello %s!" % name)
The following could be a corresponding setup.py script:

from setuptools import setup
from Cython.Build import cythonize

setup(
    name='Hello world app',
    ext_modules=cythonize("hello.pyx"),
    zip_safe=False,
)
To build, run python setup.py build_ext --inplace. Then simply start a Python session and do from hello import say_hello_to and use the imported function as you see fit.

One caveat: the default action when running python setup.py install is to create a zipped egg file which will not work with cimport for pxd files when you try to use them from a dependent package. To prevent this, include zip_safe=False in the arguments to setup().


