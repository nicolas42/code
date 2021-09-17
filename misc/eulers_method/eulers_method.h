#include <stdio.h>

// namespace eulers_method {
  
struct eulers_method_arg next(struct eulers_method_arg a);
struct eulers_method_arg
{
  double x;
  double y;
  double step;
  double (*f)(double, double);
};

struct eulers_method_arg eulers_method_next(struct eulers_method_arg a)
{
  a.x += a.step;
  a.y += a.f(a.x, a.y) * a.step;
  return a;
}

 
//}
