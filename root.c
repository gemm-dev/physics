#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
Bracket method of root finding.
*/


double bracket_root(double (*fn)(double), double x0, double x1, double tol,
		    int *n, int maxsteps)
{
  int nsteps = 0;
  double fi;
  double ftest;

  fi=fn(x0);

  do{
    nsteps++;
    ftest = fn(x0)*fn(x0+tol*(double)nsteps);
  }
  while(ftest > 0 && nsteps < maxsteps);

  *n = nsteps;
  return(x0+tol*(nsteps-0.5));
}

/* 
Bisection method of root finding.
*/

double bisection_root(double (*fn)(double), double x0, double x1, double tol, 
		      int *n, int maxsteps)
{
  int nsteps = 0;
  double xmid;

  while(x1-x0 > tol && nsteps < maxsteps)  {
    nsteps++;
    xmid = (x0+x1)/2;
    if(fn(xmid) == 0) {
      *n = nsteps;
      return(xmid);
    }

    if(fn(x0)*fn(xmid) < 0)
      x1 = xmid;
    else
      x0 = xmid;
  }

  *n = nsteps;
  return((x0+x1)/2);

}


/* 
Newton-Raphson method of root finding.
*/

double newton_raphson_root(double (*fn)(double), double (*dfdx)(double),
			   double x, double tol, int *n, int maxsteps)
{
  int nsteps = 1;
  double x1 = x - fn(x)/dfdx(x); 

  while(fabs(x1-x)>tol && nsteps < maxsteps)  {
    nsteps++;
    x = x1;
    x1 = x - fn(x)/dfdx(x); 
  }

  *n = nsteps;
  return x1;

}
