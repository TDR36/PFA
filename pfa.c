#define PFA_C

#include "pfa.h"

/* Initialize the integration variables.
   Arguments :
   - quadrature : name of the quadrature formula that will be used. It can be "left", "right", 
     "middle", "trapezes", "simpson", "gauss2" or "gauss3".
   - dt : a positive value, which will be used to decide the number of subdivisions of an 
          interval [a,b], when computing the integration.
          The number of subdivisions will be N such that (b-a)/N ~ dt
*/
bool init_integration(char* quadrature, double dt)
{
	if (quadrature == NULL || dt <= 0.0) return false;
	if (!setQuadFormula(&pfaQF, quadrature)) return false;
    pfa_dt = dt;
    return true;
}



/* Density of the normal distribution */
double phi(double x)
{
	return 0.398942280401433 * exp( (-(x*x))/2 );
}

/* Cumulative distribution function of the normal distribution */
double PHI(double x)
{
  return 1.0/2.0+integrate_dx(phi,0.0,x,pfa_dt,&pfaQF) ;
}

/* =====================================
   Finance function: price of an option 
*/
double optionPrice(Option* option)
{
	if (!option) return 0.0;
	printf("%.3f\n",option->S0); 
	double C;
	double S0=option->S0;
	double K=option->K, mu=option->mu, sig=option->sig, T=option->T
	
	double z0= ((log(K / S0) - (mu - ((sig * sig) /2.0 )) * T) / ( sig * sqrt(T)));
	
	if (option->type==CALL){
	 return S0 * exp(mu * T) * PHI(sig*sqrt(T)-z0)-K*PHI(-z0);
	}

	else {
	 return K*PHI(z0)-S0*exp(mu *T)*PHI(z0-sig*sqrt(T));
	}
}



/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/

double clientPDF_X(InsuredClient* client, double x)
{
	if (!client) return 0.0;
  	return (x<=0.0) ? 0.0 : 1.0/(client->s*x) *phi((log(x)-client->m)/client->s);
}


/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
	if (!client) return 0.0;
 	return (x<=0.0) ? 0.0 : PHI((log(x)-client->m)/client->s);
}


/* ==========================================================*/
/* Distribution of X1+X2 : static intermediate functions     */

/* The static functions localProductPDF and localPDF_X1X2 take only one
   argument, of type double.
   They hence can be integrated: function integrate_dx takes as argument a function pointer f, 
   where f depends only on one argument (double t).
   The static functions below can be given as argument to integrate_dx.

   That's why we copy other variables of the final functions (client and x) to local static variables, 
   and define these static functions depending on only one argument (double t).
   These local functions can hence be arguments of integrate_dx.
*/
static InsuredClient* localClient;
static double localX;


/* This function assumes that static variables localClient and localX have been set.
   It can be an argument of integrate_dx (since it has the good signature)
*/
static double localProductPDF(double t)
{
  return clientPDF_X(localClient, t) * clientPDF_X(localClient, localX-t);
}

/* Density of X1+X2

   This function assumes that static variable localClient has been set.
   It is called by clientPDF_X1X2
   It can also be an argument of integrate_dx (since it has the good signature)
*/
static double localPDF_X1X2(double x)
{
	localX = x; 
  	return integrate_dx(localProductPDF,0.0,x,pfa_dt,&pfaQF);
} 


/* ==========================================================*/
/* Distribution of X1+X2 : the final functions               */

/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientPDF_X1X2(InsuredClient* client, double x)i           //
{
  if ( x<=0 ) return 0.0;

  localClient = client;
  return (x<=0.0) ? 0.0 : localPDF_X1X2(x);
}


/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientCDF_X1X2(InsuredClient* client, double x)
{
	if (!client) return 0.0;
  	localClient = client;

  	return integrate_dx(localPDF_X1X2, 0.0,x,pfa_dt,&pfaQF);
}



/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
	if (!client) return 0.0;
	if (x<0.0) return 0.0;
	if (!x) return client->p[0];

	return client->p[0] + client->p[1]*clientCDF_X(client, X) + client->p[2]*clientCDF_X1X2(client,x);
}



