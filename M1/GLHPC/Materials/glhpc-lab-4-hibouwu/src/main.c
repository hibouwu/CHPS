#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "compute_pi.h"
#include <assert.h>
#include <unistd.h>
#include <time.h>

// Structure to hold the benchmarking results
// Of the PI MC estimator
typedef struct {
    // The average of the computed Pi values
    double avg_pi;
    // The standard deviation of the computed Pi values
    double std_pi;
    // All the computed Pi values
    double *pis;
    // The average of the timings
    double avg_time;
    // The standard deviation of the timings
    double std_time;
    // All the timings
    double *timings;
    // The number of meta repetitions done (Thus the length of pis and timings arrays)
    int nmeta;
} BenchResults;

// Empty initializer for BenchResults
const BenchResults EMPTY_BENCH_RESULTS = {0, 0, NULL, 0, 0, NULL, 0};

/**
 * @brief Harness function to run the Monte-Carlo estimator multiple times and record results.
 * @param results Pointer to BenchResults structure to store the results.
 * @param n Number of random points for each Monte-Carlo estimation.
 * @param meta_repets Number of times to repeat the Monte-Carlo estimation.
 */
void mc_harness(BenchResults *results, const int n, const int meta_repets){
    if (results == NULL || n <= 0 || meta_repets <= 0) {
        printf("Error: Invalid arguments to mc_harness\n");
        exit(1);
    }
    // Allocate memory for storing results
    results->pis = malloc(meta_repets * sizeof(double));
    results->timings = malloc(meta_repets * sizeof(double));
    results->nmeta = meta_repets;
    
    if (!results->pis || !results->timings) {
        printf("Error: Memory allocation failed\n");
        exit(1);
    }

    for (int warmup = 0; warmup < 10; warmup++) {
        compute_pi_mc(1000);
    }
    
    double sum_pi = 0.0;
    double sum_time = 0.0;
    
    // Run the Monte-Carlo estimator meta_repets times
    for (int i = 0; i < meta_repets; i++) {
        struct timespec start, end;
        
        // Get start time using monotonic clock
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        // Run the Monte-Carlo estimation
        double pi = compute_pi_mc(n);
        
        // Get end time
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        
        // Calculate elapsed time in seconds
        double elapsed = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
        
        // Store results
        results->pis[i] = pi;
        results->timings[i] = elapsed;
        
        sum_pi += pi;
        sum_time += elapsed;
    }
    
    // averages
    results->avg_pi = sum_pi / meta_repets;
    results->avg_time = sum_time / meta_repets;

    // standard deviations
    double sum_sq_pi = 0.0;
    double sum_sq_time = 0.0;
    
    for (int i = 0; i < meta_repets; i++) {
        double diff_pi = results->pis[i] - results->avg_pi;
        double diff_time = results->timings[i] - results->avg_time;
        sum_sq_pi += diff_pi * diff_pi;
        sum_sq_time += diff_time * diff_time;
    }
    
    results->std_pi = sqrt(sum_sq_pi / meta_repets);
    results->std_time = sqrt(sum_sq_time / meta_repets);
}

// Serialize results to CSV file

void save_to_csv(BenchResults *res, const char *const output_path){
    if (res == NULL || output_path == NULL) {
        fprintf(stderr, "Invalid arguments to save_to_csv\n");
        exit(1);
    }

    FILE *f = fopen(output_path, "w");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    // Header
    fprintf(f, "NMeta,Pi,Time\n");

    // Rows: 1-based meta index, pi, timing (6 decimals)
    for (int i = 0; i < res->nmeta; ++i) {
        fprintf(f, "%d,%.10f,%.9f\n", i + 1, res->pis[i], res->timings[i]);
    }
    
    // Clean up
    if (res->pis) {
        free(res->pis);
    }
    if (res->timings) {
        free(res->timings);
    }

    fclose(f);
}


// Print results table to stdout
void print_results(BenchResults *res)
{
    if (res->nmeta == 0) {
        printf("No results to display.\n");
        return;
    }
    
    // Find min and max times
    double min_time = res->timings[0];
    double max_time = res->timings[0];
    
    for (int i = 1; i < res->nmeta; i++) {
        if (res->timings[i] < min_time) min_time = res->timings[i];
        if (res->timings[i] > max_time) max_time = res->timings[i];
    }
    
    printf("Avg. Pi\t\tStd Pi\t\tAvg. Time\tStd Time\tMin Time\tMax Time\n");
    printf("%.10f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\n", 
           res->avg_pi, res->std_pi, res->avg_time, res->std_time, min_time, max_time);
}

// ---------------------------------------- DO NOT EDIT BELOW THIS LINE

void parse_args(int *const n, int *const meta_repets, 
    const char **output_path, 
    char* argv[], const int argc)
{
    assert(n != NULL);
    assert(meta_repets != NULL);
    assert(output_path != NULL);

    if (argc < 2 || argc > 4)
    {
        printf("Invalid number of arguments.\n");
        printf("Usage: %s <n> (meta_repets) (output_path)\n", argv[0]);
        exit(1);
    }

    *n = atoi(argv[1]);
    if (argc >= 3)
        *meta_repets = atoi(argv[2]);
    else
        *meta_repets = 1;

    if (argc >= 4)
        *output_path = argv[3];
    else
        *output_path = "results.csv";
}

int main(int argc, char **argv)
{
    int n = 0, meta_repets = 0;
    const char *output_path = NULL;
    parse_args(&n, &meta_repets, &output_path, argv, argc);

    BenchResults res = EMPTY_BENCH_RESULTS;
    mc_harness(&res, n, meta_repets);
    print_results(&res);
    save_to_csv(&res, output_path);

    return 0;
}

// ---------------------------------------- DO NOT EDIT ABOVE THIS LINE