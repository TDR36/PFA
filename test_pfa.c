/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{
	Option *opt=calloc(1,sizeof(Option));
	opt->type=CALL;
	opt->S0 = 100;
	opt->K=100;
	opt->T=2;
	opt->mu=0.05;
	opt->sig=0.02;

	InsuredClient* client= calloc(1,sizeof(InsuredClient));

	client->m=1;
	client->s=1;
	client->p[3]={0.9, 0.05, 0.05};
	
	///////////////     X   0        1               2
	//////////////     PDF  0      0.0196         0.0726
	/////////////      CDF  0      0.049          0.0517
	
	init_integration("trapezes", 0.1);
	printf("%.3f",optionPrice(opt));//0.975
	free(opt);
	return 0;
}
