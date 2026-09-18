#ifndef BLS_H
#define BLS_H

typedef struct
{
    double period;
    double duration;
    double phase;
    double depth;
    double power;
} BLSResult;

BLSResult bls(double *t, double *f, int N,
              double Pmin, double Pmax, int Np,
              double qmin, double qmax, int Nq);

double *bls_periodogram(double *t, double *f, int N,
                        double Pmin, double Pmax, int Np,
                        double qmin, double qmax, int Nq, int *out_Nf);

#endif // BLS_H