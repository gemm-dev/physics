
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100

void store_terms(double terms[], double exponent);
int num_terms_needed(double terms[], double tolerance, double exact);


int main(int argc, char **argv)
{
	double exponent, tolerance, exact;
	double terms[MAX_TERMS];
	int ans;

	printf("Enter exponent: ");
	scanf("%lf", &exponent);
	printf("Enter tolerance: ");
	scanf("%lf", &tolerance);
		while(tolerance <=0 || tolerance >= 1)
		{
			printf("Tolerance must be between 0 and 1 exclusive\n");
			printf("Enter tolerance: ");
			scanf("%lf", &tolerance);
		}

	exact = exp(exponent);

	store_terms(terms, exponent);
	ans = num_terms_needed(terms, tolerance, exact);

	if(ans<=MAX_TERMS)
		printf("%d term(s) required\n", ans);
	else
		printf("Exceeded %d terms\n", MAX_TERMS);	


}

void store_terms(double terms[], double exponent)
{
	int n;
	
	terms[0]=1.;

	for(n=1; n < MAX_TERMS; n++)
		terms[n]=terms[n-1]*exponent/n;
}

int num_terms_needed(double terms[], double tolerance, double exact)
{
	int m=0;
	double sum=0.;
	double diff=2.;

	while(diff>tolerance && m<MAX_TERMS)
	{
		sum=sum+terms[m];
		diff=fabs(sum-exact)/exact;
		m++;
	}
	
	if(diff<=tolerance)
		return(m);
	else
		return(m+1);
}






