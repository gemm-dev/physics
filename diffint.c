#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
forward_diff function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return as the forward difference approximation to the
derivative of the function fn calculated at x with step size delta.
*/

double forward_diff(double (*fn)(double), double x, double delta)
{

	return (fn(x+delta)-fn(x))/delta;
	
}

/* 
center_diff function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return as the central difference approximation to the
derivative of the function fn calculated at x with step size delta
(to avoid any possible confusion, this means that fn will be evaluated
at x-delta and x+delta).
*/

double center_diff(double (*fn)(double), double x, double delta)
{

	return (fn(x+delta)-fn(x-delta))/(2*delta);

}

/*
second_deriv function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return the approximation to the second derivative
of the function fn at x based on the values taken by fn at x and
at the nearest neighbor points x+dx, x-dx.
*/

double second_deriv(double (*fn)(double), double x, double delta)
{
	
	return (fn(x+delta)+fn(x-delta)-2*fn(x))/(delta*delta);

}

/* 
trap_integrate function receives from the calling program the name fn of
an external function program and the lower and upper limits of an
integration domain, x0 and xn, and must return the approximation 
to the integral of fn over the interval x0,xn given by the trapezoidal
formula based on a subdivision of the interval of integration into n
equal subintervals.
*/

double trap_integrate(double (*fn)(double), double x0, double xn, int n)
{
	double ti=0.;
	double delta;

	delta = (xn-x0)/(double)n;

	for(int i = 1; i < n; i++)
	{
		ti += delta*fn(x0+i*delta);
	}

	ti += delta/2*(fn(x0)+fn(xn));

	return ti;
}
 
/*
simpson_integrate function receives from the calling program the name fn of
an external function program and the lower and upper limits of an
integration domain, x0 and xn, and must return the approximation 
to the integral of fn over the interval x0, xn given by Simpson's
formula based on a subdivision of the interval of integration into 
2*n equal subintervals.
*/

double simpson_integrate(double (*fn)(double), double x0, double xn, int n)
{
	double si=0.;
	double delta;

	delta = (xn-x0)/(2.*(double)n);

	for(int i = 1; i < 2*n; i++)
	{
		if(i & 1)
		{
			si += 4*fn(x0+i*delta);
		}
		else
		{
			si += 2*fn(x0+i*delta);
		}
	}

	si = delta/3.*(si+fn(x0)+fn(xn));

	return si;
}


/*
evolve_decay receives from the calling program the initial mass of
matter M, the decay rate lambda, the time step dt, and the number of
steps nsteps to evolve the system.  The function should then evolve M by
nsteps steps using the Euler method, and return the final value of M.
*/

double evolve_decay(double M, double lambda, double dt, int nsteps)
{
	for(int i = 0; i < nsteps; i++)
	{
		M = M*(1.-lambda*dt);
	}

	return M;
}
