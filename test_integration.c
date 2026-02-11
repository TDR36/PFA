/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */
#include <math.h>
double f(double t)
{
return sin(t);
}
int main()
{
QuadFormula qf;
double I1, I2, I3;
setQuadFormula(&qf, "right");
I1 = integrate(f,0 , 3.14, 10, &qf);

return I1;
}
