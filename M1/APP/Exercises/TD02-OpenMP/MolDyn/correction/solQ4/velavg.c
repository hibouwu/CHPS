#include <math.h>

double vel;

/*
 *  Compute average velocity
 */
  double
  velavg(int npart, double vh[], double vaver, double h){
    int i;
    double vaverh=vaver*h;
    double sq;
    extern double count;

#pragma omp single
    {
    count=0.0;
    vel = 0.0;
    }
#pragma omp for reduction(+:count,vel) private(sq)
    for (i=0; i<npart*3; i+=3){
      sq=sqrt(vh[i]*vh[i]+vh[i+1]*vh[i+1]+vh[i+2]*vh[i+2]);
      if (sq>vaverh) count++;
      vel+=sq;
    }
#pragma omp single
    {
    vel/=h;
    }

    return(vel);
  }
