#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NMAX 20
#define NDIM 2

void center_of_mass(int N, double mass[NMAX], double r[NMAX][NDIM], 
		    double rcm[NDIM]);
double angular_mom(int N, double mass[NMAX], double r[NMAX][NDIM], 
		   double v[NMAX][NDIM]);
double kinetic_energy(int N, double mass[NMAX], double v[NMAX][NDIM]);
double potential(int N, double mass[NMAX], double r[NMAX][NDIM]);
void move_euler(int N, double mass[NMAX], double r[NMAX][NDIM], 
		double v[NMAX][NDIM], int nsteps, double dt);
void move_runge_kutta(int N, double mass[NMAX], double r[NMAX][NDIM], 
		      double v[NMAX][NDIM], int nsteps, double dt);

void init_window(int size, int *argc, char **argv);
void plot2d(int N, int size, double scale, double rold[NMAX][NDIM], 
	    double r[NMAX][NDIM]);

int main(int argc, char **argv)
{
  int N, i, k;
  int t1, t2, n_draw, n_per_draw, nsteps, size;
  double r[NMAX][NDIM], rold[NMAX][NDIM], v[NMAX][NDIM], mass[NMAX];
  double rcm[NDIM], vcm[NDIM];
  double kin, pot, dt, scale;
  char answer;
  FILE *fp;

  printf("Do you wish to read initial positions from a data file? ");
  scanf("%c", &answer);
  if (answer == 'y' || answer == 'Y') {
    if ((fp=fopen("gravity.dat", "r"))==NULL) {
      printf("Could not open file gravity.dat");
      exit(0);
    }

    fscanf(fp, "%d", &N);
    /*
    mass = (double*) calloc(N, sizeof(double));
    r = (double**) calloc(N, sizeof(double*));
    v = (double**) calloc(N, sizeof(double*));
    for (i=0; i<N; i++) {
      r[i] = (double*) calloc(NDIM, sizeof(double));
      v[i] = (double*) calloc(NDIM, sizeof(double));
    }
    */
    for (i=0; i<N; i++) {
      fscanf(fp, "%lf", &mass[i]);
      for (k=0; k<NDIM; k++) {
	fscanf(fp, "%lf", &r[i][k]);
      }
      for (k=0; k<NDIM; k++) {
	fscanf(fp, "%lf", &v[i][k]);
      }
    }
  }
  else {
    N = NMAX+1;
    while (N>NMAX || N<1) {
      printf("Enter the number of objects (<%d) you would like to simulate: ",
	     NMAX);
      scanf("%d", &N);
      if (N>NMAX || N<1) 
	printf("Invalid number of objects; try again.\n");
    }

    for (i=0; i<N; i++) {
      printf("\tObject %d mass:", i);
      scanf("%lf", &mass[i]);

      printf("\tObject %d position:\n", i);
      for (k=0; k<NDIM; k++) {
	printf("\t\tcoordinate %d: ", k);
	scanf("%lf", &r[i][k]);
      }

      printf("\tObject %d velocity:\n", i);
      for (k=0; k<NDIM; k++) {
	printf("\t\tcoordinate %d: ", k);
	scanf("%lf", &v[i][k]);
      }
    }
  }

  /* rescale coordinates so that the center of mass is fixed */
  printf("\nRescaling positions and velocities so that the\n");
  printf("center of mass is fixed at the origin\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);
   
  for (i=0; i<N; i++) {
    for (k=0; k<NDIM; k++) {
      r[i][k] -= rcm[k];
      v[i][k] -= vcm[k];
    }
  }

  scanf("%c", &answer);       /* flush the carraige return */
  printf("Enter 'r' for Runga Kutta, or 'v' for velocity Verlet: ");
  scanf("%c", &answer);

  printf("Time step dt: ");
  scanf("%lf", &dt);
  printf("Number of time steps: ");
  scanf("%d", &nsteps);
  printf("Enter scale factor for drawing (around 20): ");
  scanf("%lf", &scale);
  n_per_draw = 100;
  n_draw = nsteps/100;

  printf("\nINITIAL CONDITIONS:\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);

  printf("\tCOM position: %lf %lf\n", rcm[0], rcm[1]);
  printf("\tCOM velocity: %lf %lf\n", vcm[0], vcm[1]);
  /*  printf("\tAngular momentum: %lf\n", angular_mom(N, mass, r, v));*/
  kin = kinetic_energy(N, mass, v);
  pot = potential(N, mass, r);
  printf("\tEnergies:\n\tKinetic: %lf\n\tPotential: %lf\n\tTotal: %lf\n",
	 kin, pot, kin+pot);

  size = 600;
  init_window(size, &argc, argv);

  for (t1=0; t1<n_draw; t1++) {

    for (i=0; i<N; i++) 
      for (k=0; k<NDIM; k++)
	rold[i][k] = r[i][k];
	  
    if (answer=='r')
      move_runge_kutta(N, mass, r, v, n_per_draw, dt);
    else if (answer=='v')
      move_velocity_verlet(N, mass, r, v, n_per_draw, dt);

    /* draw */
    plot2d(N, size, scale, rold, r);
  }

  printf("\nFINAL STATE:\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);

  printf("\tCOM position: %lf %lf\n", rcm[0], rcm[1]);
  printf("\tCOM velocity: %lf %lf\n", vcm[0], vcm[1]);
  /*  printf("\tAngular momentum: %lf\n", angular_mom(N, mass, r, v));*/
  kin = kinetic_energy(N, mass, v);
  pot = potential(N, mass, r);
  printf("\tEnergies:\n\tKinetic: %lf\n\tPotential: %lf\n\tTotal: %lf\n",
	 kin, pot, kin+pot);

  /* sleep so that the window stays to observe */
  sleep(5);
}
