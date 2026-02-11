/*************************************/
/* Header file integration.h         */
/* Creation date: 31 July, 2025      */                                    
/*************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

#ifndef INTEGRATION_H
#define INTEGRATION_H

typedef struct{
  char name[20]; /* Name of the quadrature formula. */
                 /* (possible value: "left", "right", "middle", "trapezes", "simpson", "gauss2" or "gauss3") */

} QuadFormula;

#ifdef INTEGRATION_C

#else /* INTEGRATION_C */


extern bool setQuadFormula(QuadFormula* qf, char* name);
extern void printQuadFormula(QuadFormula* qf); /* Not required but useful for debugging */

extern double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf);

extern double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf);

#endif /* INTEGRATION_C */

#endif /* INTEGRATION_H */
