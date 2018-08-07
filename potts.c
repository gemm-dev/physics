/*
Mathematically, the Potts model is described
by the energy function

	E = J*(Sum over nearest neighbor spins i & j) (1.-delta(si,sj))

The constant J sets the energy scale, and we take J=1 without loss of
generality.  The spins can take any integer value in the range 0->q-1.
The function delta(si,sj) is the Kronecker delta function, which is 1 if
si=sj, and zero otherwise.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 20
#define Ny 20
#define Qmax 20

double erand48(unsigned short xseed[3]);

void update_spins(short spin[Nx][Ny], double beta, short q, 
		  unsigned short seed[3])
{
  int x, y;
  short trial_spin;
  double deltaE;

  for (x=0; x<Nx; x++) {
    for (y=0; y<Ny; y++) {

      deltaE = ((spin[x][y]==spin[(x+1)%Nx][y]) + 
		(spin[x][y]==spin[(x-1+Nx)%Nx][y]) +
		(spin[x][y]==spin[x][(y+1)%Ny]) + 
		(spin[x][y]==spin[x][(y-1+Ny)%Ny]));

      trial_spin = (spin[x][y] + 1 + (q-1)*erand48(seed));
      trial_spin = trial_spin%q;      

      deltaE -= ((trial_spin==spin[(x+1)%Nx][y]) + 
		 (trial_spin==spin[(x-1+Nx)%Nx][y]) +
		 (trial_spin==spin[x][(y+1)%Ny]) + 
		 (trial_spin==spin[x][(y-1+Ny)%Ny]));
	
      if (exp(-beta*deltaE)>erand48(seed))
	spin[x][y] = trial_spin;
    }
  }
}

double energy(short spin[Nx][Ny])
{
  int x, y;
  double E;

  E = 0;

  for (x=0; x<Nx; x++) {
    for (y=0; y<Ny; y++) {
      /* spin to the right */
      E += (1-(spin[x][y]==spin[(x+1)%Nx][y]));
      /* spin above */
      E += (1-(spin[x][y]==spin[x][(y+1)%Ny]));
    }
  }
  return E/(double)(2.*Nx*Ny);
}

void magnetization(short spin[Nx][Ny], short q, double M[Qmax])
{
  int s, x, y;

  for (s=0; s<q; s++) {
    M[s] = 0;
  }

  for (x=0; x<Nx; x++) {
    for (y=0; y<Ny; y++) {

      M[spin[x][y]]++;
    }
  }

  for (s=0; s<q; s++) {
    M[s] /= (double)(Nx*Ny);
  }

}

void init_spins(short spin[Nx][Ny], short q, unsigned short seed[3])
{
  int x, y;

  for (x=0; x<Nx; x++) {
    for (y=0; y<Ny; y++) {

      spin[x][y] = q*erand48(seed);

    }
  }
}
