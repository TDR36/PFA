#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
	if (!qf||!name) return false;
	if (!strcmp("right", name))
	{
		qf->n=0;
		qf->w=1.0;
		qf->x=1.0;
		qf->add_to_x=0.0;
		qf->add_to_w=0.0;
		strcpy(qf->name, name);
		return true;
	}
	else if (!strcmp("left", name)){
		qf->n=0;
		qf->w=1.0;
		qf->x=0.0;
		qf->add_to_x=0.0;
		qf->add_to_w=0.0;
		strcpy(qf->name, name);
		return true;
	}
	else if (!strcmp("middle", name)){
		qf->n=0;
		qf->w=1.0;
		qf->x=0.5;
		qf->add_to_x=0.0;
		qf->add_to_w=0.0;
		strcpy(qf->name, name);
		return true;
	}
	
	else if (!strcmp("trapezes", name))
	{
		qf->n=1;
		qf->w=0.5;
		qf->x=0.0;
		qf->add_to_x=1.0;
		qf->add_to_w=0.0;
		strcpy(qf->name, name);
		return true;
	}

	else if (!strcmp("simpson", name))
	{
		qf->n=2;
		qf->w=1.0/6.0;
		qf->x=0.0;
		qf->add_to_x=0.5;
		qf->add_to_w=0.4999999999;
		strcpy(qf->name, name);
		return true;
	}

	else if (!strcmp("gauss2", name))
	{
		qf->n=1;
		qf->w=0.5;
		qf->x=0.21132486540518713;
		qf->add_to_x=0.5773502691896257;
		qf->add_to_w=0.0;
		strcpy(qf->name, name);
		return true;
	}
	else if (!strcmp("gauss3", name))
	{
		qf->n=2;
		qf->w=0.27777777777777777;
		qf->x=0.11270166537;
		qf->add_to_x=0.38729833462;
		qf->add_to_w=0.16666666666;
		strcpy(qf->name, name);
		return true;
	}
	return false;
}

void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
}

double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	if (!f||!qf||N<=0) return 0.0;
	double result=0.0, a_aux,b_aux;
	double result_aux=0.0;

	double x_init= qf->x, w_init=qf->w;
	for (int i=0; i<N; i++){

		a_aux = a +i *((b-a)/N);
		b_aux = a+(i+1)*((b-a)/N);
		result_aux=0.0;
		for (int j=0; j<=qf->n;j++){
			result_aux+=w_init*(*f)(a_aux +x_init*(b_aux-a_aux));
			x_init +=qf->add_to_x;
			w_init += pow(-1, j)*qf->add_to_w; 
		}

		x_init = qf->x;
		w_init = qf->w;
		result += (b_aux-a_aux)*result_aux;
	}
	return result;
}





double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
	if (dx<=0.0) return 0.0;
	int N = (int)round(fabs(b-a)/dx);
	if (N<1) N=1;
	return integrate(f, a, b, N, qf);

}





