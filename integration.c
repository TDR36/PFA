#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
	if (!strcmp("right", name))
	{
		qf->n=0;
		qf->w=1;
		qf->x=1;
	}
	else if (!strcmp("left", name)){
		qf->n=0;
		qf->w=1;
		qf->x=0;
	}
	else if (!strcmp("middle", name)){
		qf->n=0;
		qf->w=1;
		qf->x=0.5;
	}
	else if (strcmp("gauss2", name)&&strcmp("gauss3", name)&&strcmp("simpson", name)) return false;
	
	else if (!strcmp("trapezes", name))
	{
		qf->n=1;
		qf->w=0.5;
		qf->x=0;
	};

	strcpy(qf->name, name);
	return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}

double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	double result=0.0, a_aux,b_aux;
	double result_aux=0.0;

	for (int i=0; i<N; i++){

		a_aux = a +i *((b-a)/N);
		b_aux = a+(i+1)*((b-a)/N);
		printf("%2f", qf->n);
		for (int j=0; j<qf->n;j++){
			result_aux+=qf->w*(*f)(a_aux +(qf->x)*(b_aux-a_aux));
		}
		result += (b_aux-a_aux)*result_aux;
	}
	printf("%.2f\n",result);
	return result;
}













double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


