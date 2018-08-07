#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void move_euler(double *theta, double *theta_dot, double dt, double omega0sq,
		double gamma, int system)
{

  double theta_old;

  if (system == 1)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= omega0sq * theta_old * dt;
  }

  else if (system == 2)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= omega0sq * sin(theta_old) * dt;
  } 

  else if (system == 3)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= (*theta_dot * gamma + omega0sq * sin(theta_old)) * dt;
  } 

}

/*2nd order Runge-Kutta integration of a single time step.*/

void move_runge_kutta(double *theta, double *theta_dot, double dt, 
                      double omega0sq, double gamma, int system)
{

  double theta_half, theta_dot_half;

  if (system == 1)
  {
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - omega0sq * * theta * dt/2;
  }

  else if (system == 2)
  { 
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - omega0sq * sin(*theta) * dt/2;
  } 

  else if (system == 3)
  {
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - (*theta_dot * gamma + omega0sq * sin(*theta)) * dt/2;
  } 

  if (system == 1)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= omega0sq * theta_half * dt;
  }

  else if (system == 2)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= omega0sq * sin(theta_half) * dt;
  } 

  else if (system == 3)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= (theta_dot_half * gamma + omega0sq * sin(theta_half)) * dt;
  } 

  

}
