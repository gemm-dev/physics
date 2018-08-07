#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159

double bracket_energy(double energy, double de, int nsteps, double *psi);
double bisect_energy(double e0, double e1, double tol, int nsteps, double *psi);
void normalize(double *psi, int nsteps) ;



int main(int argc, char **argv) 
{
  double energy, de, *psi;
  double tol;
  int n, nsteps, level;
  FILE *fp;

  printf("Starting energy: ");
  scanf("%lf", &energy);
  printf("Energy step de: ");
  scanf("%lf", &de);
  printf("Number of points to discretize the line nsteps: ");
  scanf("%d", &nsteps);

  tol = 1.e-8;

  psi = (double*) calloc(nsteps+1, sizeof(double));

  energy = bracket_energy(energy, de, nsteps, psi);
  energy = bisect_energy(energy, energy+de, tol, nsteps, psi);

  printf("Numerical energy of the 1D particle in a box = %lf\n", energy);
  level = rint(sqrt(2.*energy)/M_PI);
  energy = 0.5*((double)(level*level)*M_PI*M_PI);
  printf("Nearest exact quantum state is %d with energy %lf\n", level, energy);

  normalize(psi, nsteps);

  fp = fopen("psi.dat", "w");
  for (n=0; n<=nsteps; n++) 
    fprintf(fp, "%lf\t%lf\n", (double)n/(double)nsteps, psi[n]);
  fclose(fp);
}
