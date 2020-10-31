#include <stdio.h>

// #include "eulers_method.hpp"

namespace eulers_method
{

  struct arg next(struct arg a);

  struct arg
  {
    double x;
    double y;
    double step;
    double (*f)(double, double);
  };

  struct arg next(struct arg a)
  {
    a.x += a.step;
    a.y += a.f(a.x, a.y) * a.step;
    return a;
  }

}
// namespace eulers_method

double dydx(double x, double y);
double dydx(double x, double y) { return 2 * x - y; }

int main()
{
  struct eulers_method::arg a;
  a.x = 1;
  a.y = 1;
  a.step = 0.1;
  a.f = dydx;

  for (int i = 0; i < 10; i += 1)
  {
    a = eulers_method::next(a);
    printf("[ %.2f %.2f %.2f ]\n", a.x, a.y, a.step);
  }

  return 0;
}
