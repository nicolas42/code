#include <stdio.h>

#include "eulers_method.h"

double dydx(double x, double y);
double dydx(double x, double y) { return 2 * x - y; }

int main()
{
  struct eulers_method_arg a;
  a.x    = 1;
  a.y    = 1;
  a.step = 1;
  a.f    = dydx;
  
  for (int i = 0; i < 10; i += 1)
  {
    a = eulers_method_next(a);
    printf("[ %f %f %f ]\n", a.x, a.y, a.step);
  }

  return 0;
}

/*
a={'x': 1, 'y': 1, 'step': 0.1, 'f': lambda x,y: 2*x-y}
def next(a): a.x += a.step; a.y += a.f(a.x,a.y)*a.step;
*/
