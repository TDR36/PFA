



#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
	if (strcmp("right", name)&&strcmp("left", name)&&strcmp("middle", name)&&strcmp("gauss2", name)&&strcmp("gauss3", name)&&strcmp("simpson", name)&&strcmp("trapezes", name)) return false;

	qf->name=name;
	return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	double result;
	if (strcmp("left", name)) result = left(f,a,b,N);
	return 0.0;
}

double left (double (*f)(double), double a, double b, int N){
	double result=0, a_aux,b_aux;
	for (int i=0; i<N; i++){

		a_aux = a +i *((b-a)/N);
		b_aux = a+(i+1)*((b-a)/N);

		result += (b_aux-a_aux)*f(a_aux);
	}
	return result;
}





















double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


