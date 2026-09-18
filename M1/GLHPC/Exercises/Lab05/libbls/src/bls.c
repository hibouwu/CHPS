#include "../include/bls.h"

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

BLSResult bls(double *t, double *f, int N, double Pmin, double Pmax, int Np, double qmin,
              double qmax, int Nq) {
  const int Nphase = 100;

  BLSResult *best_results;
  int nthreads = 0;
#pragma omp parallel
  {
#pragma omp single
    {
      // We need to get the number of threads used by OpenMP
      // to allocate one best_result per thread
      nthreads = omp_get_num_threads();
      best_results = malloc(nthreads * sizeof(BLSResult));
    }

    double *phi = malloc(N * sizeof(double));
    int tid = omp_get_thread_num();
    best_results[tid].power = -1;

#pragma omp for schedule(dynamic)
    for (int ip = 0; ip < Np; ip++) {
      double P = Pmin * pow(Pmax / Pmin, (double)ip / (Np - 1));  // log spacing

      // Fold data using the current trial period we are testing for
      // The phase is in [0, 1)
      const double inv_P = 1.0 / P;
      for (int i = 0; i < N; i++) {
        phi[i] = fmod(t[i], P) * inv_P;
      }

      for (int iq = 0; iq < Nq; iq++) {
        // We test multiple transit durations
        // linearly spaced between qmin and qmax
        const double q = qmin + (qmax - qmin) * iq / (Nq - 1);

        // Slide transit window over phases
        for (int iph = 0; iph < Nphase; iph++) {
          // The current position of the box in [0, 1) is defined as iph / Nphase
          // A bigger Nphase means finer sampling of the box position
          // but higher computational cost
          const double ph0 = (double)iph / Nphase;

          // Compute in-transit / out-of-transit averages
          double sum_in = 0, sum_out = 0;
          int nin = 0, nout = 0;

          for (int i = 0; i < N; i++) {
            double ph = phi[i];
            double val = f[i];
            if (!isfinite(val)) continue;

            double dph = ph - ph0;
            if (dph < 0) dph += 1.0;

            // If the current point is in transit
            // i.e. within the box defined by (ph0, ph0 + q)
            if (dph < q) {
              sum_in += val;
              nin++;
            } else {
              // Else, the point is out of transit
              sum_out += val;
              nout++;
            }
          }

          if (nin == 0 || nout == 0) continue;

          // Compute the statistics for the current box
          double avg_in = sum_in / nin;
          double avg_out = sum_out / nout;
          double depth = avg_out - avg_in;

          // Detection statistic ~ depth^2 * nin * nout / N
          double power = depth * depth * nin * nout / (double)N;
          if (power > best_results[tid].power) {
            best_results[tid].power = power;
            best_results[tid].period = P;
            best_results[tid].duration = q * P;
            best_results[tid].phase = ph0;
            best_results[tid].depth = depth;
          }
        }
      }
    }
    // Every thread allocated its own phi array
    // We need to free them here
    free(phi);
  }

  BLSResult best;
  best.power = -1;
  for (int i = 0; i < nthreads; i++) {
    if (best_results[i].power > best.power) {
      best = best_results[i];
    }
  }
  free(best_results);

  return best;
}

// This is just a copy-pasted and slightly modified version of the bls function above
// Its really not ideal to have this code duplication
// But i didn't want to spend too much time refactoring the code for the lab
double *bls_periodogram(double *t, double *f, int N, double Pmin, double Pmax, int Np, double qmin,
                        double qmax, int Nq, int *out_Nf) {
  const int Nphase = 100;

  // Store pairs of (period, power)
  double *out = malloc(2 * Np * sizeof(double));
  for (int i = 0; i < 2 * Np; i++) out[i] = -1;

  int nthreads = 0;
#pragma omp parallel
  {
    double *phi = malloc(N * sizeof(double));
    int tid = omp_get_thread_num();

#pragma omp for schedule(static)
    for (int ip = 0; ip < Np; ip++) {
      double P = Pmin * pow(Pmax / Pmin, (double)ip / (Np - 1));  // log spacing

      // Fold data using the current trial period we are testing for
      // The phase is in [0, 1)
      for (int i = 0; i < N; i++) {
        phi[i] = fmod(t[i], P) / P;
      }

      for (int iq = 0; iq < Nq; iq++) {
        // We test multiple transit durations
        // linearly spaced between qmin and qmax
        double q = qmin + (qmax - qmin) * iq / (Nq - 1);

        // Slide transit window over phases
        for (int iph = 0; iph < Nphase; iph++) {
          // The current position of the box in [0, 1) is defined as iph / Nphase
          // A bigger Nphase means finer sampling of the box position
          // but higher computational cost
          double ph0 = (double)iph / Nphase;

          // Compute in-transit / out-of-transit averages
          double sum_in = 0, sum_out = 0;
          int nin = 0, nout = 0;

          for (int i = 0; i < N; i++) {
            double ph = phi[i];
            double val = f[i];
            if (!isfinite(val)) continue;

            double dph = ph - ph0;
            if (dph < 0) dph += 1.0;

            // If the current point is in transit
            // i.e. within the box defined by (ph0, ph0 + q)
            if (dph < q) {
              sum_in += val;
              nin++;
            } else {
              // Else, the point is out of transit
              sum_out += val;
              nout++;
            }
          }

          if (nin == 0 || nout == 0) continue;

          // Compute the statistics for the current box
          double avg_in = sum_in / nin;
          double avg_out = sum_out / nout;
          double depth = avg_out - avg_in;

          // Detection statistic ~ depth^2 * nin * nout / N
          double power = depth * depth * nin * nout / (double)N;
          if (power > out[2 * ip]) {
            out[2 * ip] = power;
            out[2 * ip + 1] = P;
          }
        }
      }
    }
    free(phi);
  }
  *out_Nf = Np;
  return out;
}