#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char **argv)
{

double temp = 100;
double sol;
double try = 0;
double xo=0;
double yo=0;
double y=0;
double x=0;
double prob;
double p;
int i=0;


double range = 20;
double div = RAND_MAX/range;
xo = (rand()/div) - 10;
yo = (rand()/div) - 10;

while (temp > 0.001)
{

for (i=0; i<10000; i++)
{	

	double range = 20;
	double div = RAND_MAX/range;
	x = (rand()/div) - 10;
	y = (rand()/div) - 10;

	sol = 3*((1-xo)*(1-xo))*exp(-xo*xo - (yo+1)*(yo+1)) - 10*(xo/5 - xo*xo*xo - yo*yo*yo*yo*yo)*exp(-xo*xo-yo*yo) - 1/3*exp(-(xo+1)*(xo+1) - yo*yo);
	try = 3*((1-x)*(1-x))*exp(-x*x - (y+1)*(y+1)) - 10*(x/5 - x*x*x - y*y*y*y*y)*exp(-x*x-y*y) - 1/3*exp(-(x+1)*(x+1) - y*y);
	prob = 1/exp((try-sol)/temp);

	if (try < sol)
	{
		sol = try;
		xo=x;
		yo=y;
	}

	else
	{
		double range = 1;
		double div = RAND_MAX/range;
		p = (rand()/div);
		if (prob > p)
		{
			sol = try;
			xo=x;
			yo=y;
		}
	}
}

	printf("%lf %lf %lf\n", xo, yo, sol);
	temp = temp*.9;

}

	printf("FINAL:\n%lf %lf %lf\n", xo, yo, sol);

}
