/*LINEAR, COSINE, AND LAGRANGE INTERPOLATION OF DATA*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv)
{


double x[100];
double y[100];
double a=0;
double s=1;
double t=1;
double k=0;
double m=0;
int n;
int i;
int j=0;
int d;


printf("Enter the number of data points: \n");
scanf("%d",&n); 
//stores number of data points as n

printf("\n Enter values for x and y (in the order x1, y1, x2, y2, etc.): \n");
    for(i=0; i<n; i++)
    {
        scanf ("%lf",&x[i]);
        scanf("%lf",&y[i]);
    }
//stores values of x and y in arrays

printf("\n Enter 1 for linear interpolation or 2 for Lagrangian interpolation: \n");
scanf("%d",&d);
//picks which interpolation method to use


while(d==(1||2))
{
/*LINEAR METHOD (data must be entered with x values in ascending or descending order)*/
while(d==1)
    {
        printf(" \n Enter a value for x \n");
        scanf("%lf",&a);

		for(i=0; i<n; i++)
		{
			if((x[i] < a && x[i+1] > a) || (x[i] > a && x[i+1] < a))
				{
					j=i;
					i=n;
				}
		}
		//printf("%lf %lf \n", x[j], x[j+1]); (uncomment to check bracketing points)
		m = (y[j+1]-y[j])/(x[j+1]-x[j]);
		//printf("%lf", m); (uncomment to check slope of interpolating line)
		k = m*(a-x[j])+y[j];

        printf("\n y = %lf",k);
        printf("\n Press 1 for linear, 2 for Lagrange, or any other key to exit");
        scanf("%d",&d);
    }


/*LAGRANGE METHOD (data can be in any order)*/
while(d==2)
    {
        printf(" \n Enter a value for x \n");
        scanf("%lf",&a);
		k=0;
        for(i=0; i<n; i++)
        {
            s=1;
            t=1;
            for(j=0; j<n; j++)
            {
                if(j!=i)
                {
                    s*=(a-x[j]);
                    t*=(x[i]-x[j]);
                }
            }
            k+=((s/t)*y[i]);
        }
        printf("\n y = %lf",k);
        printf("\n Press 1 for linear, 2 for Lagrange, or any other key to exit");
        scanf("%d",&d);
    }
}
}
