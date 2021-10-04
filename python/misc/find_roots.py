import math


def find_roots_with_newtons_method(f, fdash, x0):
    while True:
        y0 = f(x0)
        m = fdash(x0)
        x_intercept = -y0 / m + x0
        if (abs(x_intercept - x0) < 1e-10):
            return x_intercept
        else:
            x0 = x_intercept
    


def find_roots(f, fdash, xs):
    roots = set()
    for x in xs:
        try:
            r = find_roots_with_newtons_method(f, fdash, x)
            r = round(r, 7)
            roots.add(r)
        except Exception as e:
            print(e)
    roots = list(roots)
    roots.sort()
    return roots


if __name__ == "__main__":
    def f(x): return (2+x-x**2)
    def fdash(x): return 1-2*x
    r = find_roots(f, fdash, range(-100, 100))
    print(r)
