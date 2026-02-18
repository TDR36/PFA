/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

#include <math.h>

double f(double t)
{
return sin(t);
}

int main()
{
QuadFormula qf;
double I1, I2, I3, I4, I5, I6, I7;
setQuadFormula(&qf, "left");
I1 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "right");
I2 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "middle");
I3 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "trapezes");
I4 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "simpson");
I5 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "gauss2");
I6 = integrate_dx(f, 0, M_PI, 0.07, &qf);

setQuadFormula(&qf, "gauss3");
I7 = integrate_dx(f, 0, M_PI, 0.07, &qf);
}
