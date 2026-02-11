/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */
#include <math.h>
double f(double t)
{
return log(t);
}
int main()
{
QuadFormula qf;
double I1, I2, I3;
setQuadFormula(&qf, "left");
I1 = integrate(f,1 , 3, 100, &qf);

return I1;
}
