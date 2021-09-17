namespace eulers_method {

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


