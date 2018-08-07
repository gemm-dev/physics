#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void bracket_min(double (*fn)(double), double start, double bracket[3], 
		 double step, int maxit);
double golden_section(double (*fn)(double), double a, double b, double c,
		      double tol, int maxit);

double parabola(double x);
double rough_parabola(double x);

int main(int argc, char **argv)
{
  double start, bracket[3], a, b, c;
  double minimum, tol, step;
  double (*fn)(double);
  int maxit;
  int fn_choice, ask_user;

  printf("** Minimization Search **\n\n");

  ask_user = 1;
  while (ask_user) {
    printf("Choose the function to minimize:\n");
    printf("\t1: Simple parabola, fn(x) = x^2\n");
    printf("\t2: Wiggly parabola, fn(x) = x^2 + cos(11*x) + sin(7*x)\n");
    printf("Choose 1 or 2: ");
    scanf("%d", &fn_choice);
    if ((fn_choice==1) || (fn_choice==2)) 
      ask_user = 0;
    else 
      printf("Invalid choice!\n");
  }
  printf("Enter starting point for search: ");
  scanf("%lf", &start);
  tol = -1;
  while (tol < 0) {
    printf("Enter the tolerance for your minimum (>0): ");
    scanf("%lf", &tol);
  }
  step = 0;
  while (step <= tol) {
    printf("Enter bracket step size (bigger than tolerace!): ");
    scanf("%lf", &step);
  }
  maxit = -1;
  while (maxit <=0) {
    printf("Enter maximum number of allowed iterations: ");
    scanf("%d", &maxit);
  }
  
  if (fn_choice==1) 
    fn = &parabola;
  else
    fn = &rough_parabola;

  bracket_min(fn, start, bracket, step, maxit);
  a = bracket[0];  b = bracket[1];  c = bracket[2];
  printf("\nBracketed mimimum to the interval (%lf, %lf)\n", a, c);
  
  minimum = golden_section(fn, a, b, c, tol, maxit);
  
  printf("\nGolden section search minimum at %le\n", minimum);
  printf("Function value at minimum = %le\n\n", fn(minimum));
}

double parabola(double x)
{
  return x*x;
}

double rough_parabola(double x)
{
  return x*x + (cos(11.*x) + sin(7.*x));
}
