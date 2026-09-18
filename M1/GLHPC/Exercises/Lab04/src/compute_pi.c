#define _GNU_SOURCE
#include "compute_pi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/**
 * Compute an estimate of π using the Monte Carlo method.
 * This function generates random points in a square and counts how many fall inside a quarter circle.
 * 
 * @param n The number of random points to generate.
 * @return An estimate of π.
 */
double compute_pi_mc(int n) {
    int points_inside_circle = 0;

    int seed = rand(); // Warm up the random number generator

    #pragma omp parallel reduction(+:points_inside_circle) // Each thread has its own copy of points_inside_circle
    {
        //Each thread uses its own seed based on thread ID and time
        struct drand48_data buffer;
        int thread_id = omp_get_thread_num();

        // Time setting different seed for each thread
        srand48_r(seed + thread_id * 1000, &buffer);

        #pragma omp for schedule(static)
        for (int i = 0; i < n; i++) {
            double rand_x, rand_y;
            
            // thread-safe drand48_r
            drand48_r(&buffer, &rand_x);
            drand48_r(&buffer, &rand_y);
            
            // Random point in [-1, 1] x [-1, 1]
            double x = 2.0 * rand_x - 1.0;  // Random number between -1 and 1
            double y = 2.0 * rand_y - 1.0;  // Random number between -1 and 1

            // Check if point is inside unit circle (x² + y² ≤ 1)
            if (x * x + y * y <= 1.0) {
                points_inside_circle++;
            }
        }
    }
    
    // π ≈ 4 * (points_inside_circle / n)
    // This is because the area of unit circle is π and area of square is 4
    double pi_estimate = 4.0 * points_inside_circle / n;
    
    return pi_estimate;
}