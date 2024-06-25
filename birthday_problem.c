#include <stdio.h>
#include <math.h>

// UUID collision chance calculations
// https://en.wikipedia.org/wiki/Birthday_problem

int birthday_problem_start(double N)
{
  // double N = 20;
  double i = 0;
  double p = 1;

  // The probability that N random numbers are different is the following.  
  for(i=0;i<N;i+=1){
    p = p * (365-i)/365;
  }
  // So the probability that there is at least one collision is 1-p
  printf("Probability that there is at least one collision is: %f\n",1-p);
  return 0;
}

double birthday_problem(double num_alternatives, double num_random_items)
{
  double i = 0;
  double p = 1;

  // The probability that N random items.  
  for(i=0;i<num_random_items;i+=1){
    p = p * (num_alternatives-i)/num_alternatives;
  }
  // So the probability that there is at least one collision is 1-p
  return 1-p;
}

double birthday_problem_approximation(double na, double nri) // num_alternatives, double num_random_items)
{
  double i = 0;
  double p = 1;

  // Approximations
  // e^x ~= 1 + x
  // e^(-a/365)  ~= 1 - a/365  so when a = 1, 1-a/365 = 365/365 - 1/365 = 364/365
  // so 364/365 * 363/365 * ... = exp(-1/365)*exp(-2/365) = exp((-1-2)/365) = exp(-3/365)

  /*  
  double sa = 0; // sum of a
  for(i=0;i<nri;i+=1){
    sa = sa + i;
  }
  */
  
  double sa = nri*nri/2 - nri/2; // n*n/2 - n/2

  p = exp(-sa / na);
  return 1-p;
}




int main()
{
  double p,i;

  /*
  p = 0;
  p = birthday_problem_start(20);


  */
  /*
  p = birthday_problem(365, 23);
  printf("%f %f\n", 23., p); // people, chance of at least one collision.
  */

  /*
  double na, nri; // num_alternatives, num_random_items;

  na = pow(2,64);
  nri = pow(2,32);
  
  printf("%f %f\n", na, nri);
  p = birthday_problem(na, nri);
  printf("%f %f\n", i, p); // items, chance of at least one collision.
  */
  /*
  p = birthday_problem_approximation(365, 23);
  printf("%f %f\n", 23., p); // people, chance of at least one collision.
  */


  for(i=0;i<50;i+=1){
    double bp = birthday_problem(365, i);
    double bpa = birthday_problem_approximation(365, i);
    printf("%f %f %f %f\n", i, bp, bpa, bp-bpa);
  }

  
  double na = pow(2,64);
  double nri = pow(2,32);  
  double bpa = birthday_problem_approximation(na, nri);
  printf("%f %f %f\n", na, nri, bpa);


  na = pow(2,128);
  nri = pow(2,63);
  bpa = birthday_problem_approximation(na, nri);
  printf("%f %f %f\n", na, nri, bpa);

  // if the number of random items is 2^(possibilities/2) or higher the probability of collisions quickly goes to 1

  // The number of items must remain below the square root of the number of possibilities or alternatives

  // For a 128 bit UUID there are 2^128 alternatives.  The number of items must remain under (2^128)^(1/2) = 2^64 items
  // for there to be an acceptable chance of collisions.  It's a ceiling on the number of items really.



  return 0;
}
