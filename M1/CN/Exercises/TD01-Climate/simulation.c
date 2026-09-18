#include <math.h>
#include <stdio.h>
#include <string.h>

#define real double

// Solar constant W / m ^ 2
#define S0 1370

// Stefan - Boltzmann constant W / m2 / K4
#define SIGMA 0.00000005670367

// Temperature inertia (in years)
#define THETA 100.0

// Albedo, in this simulation albedo is considered constant
// in reality albedo can become lower with increased temperatures
// due to ice cap melting
#define ALBEDO 0.33

// Initial values

// Simulation starts in 2007
static const real t0 = 2007.0;
// Temperaturature in 2007 in K
static const real T0 = 288.45;
// CO2 concentration in 2007 in ppm
static const real CO20 = 370.0;

// RCP scenarios
typedef enum {
    RCP_CONSTANT,  // Keep CO2 constant at 2007 level
    RCP_26,        // RCP2.6 - Strong mitigation scenario
    RCP_60         // RCP6.0 - High emission scenario
} rcp_scenario_t;

// Global variable to select RCP scenario
static rcp_scenario_t current_rcp = RCP_CONSTANT;

// CO2 concentration in ppm as a function of time (linear approximation)
real CO2_concentration(real t) {
    switch(current_rcp) {
        case RCP_CONSTANT:
            return CO20;  // Keep constant at 2007 level (370 ppm)
            
        case RCP_26:
            // RCP2.6: Linear from 370 ppm (2007) to 420 ppm (2100)
            return CO20 + (420.0 - CO20) * (t - t0) / (2100.0 - t0);
            
        case RCP_60:
            // RCP6.0: Linear from 370 ppm (2007) to 670 ppm (2100)
            return CO20 + (670.0 - CO20) * (t - t0) / (2100.0 - t0);
            
        default:
            return CO20;
    }
}

// Greenhouse gaz fraction
static real G(real t, real T)
{
    return 3.35071874e-03 * T + 3.20986702e-05 * CO2_concentration(t) - 0.561593690144655;
}

real P_in (void)
{
    return (1 - ALBEDO) * S0 / 4.0;
}

real P_out(real t, real T)
{
    return (1-G(t,T))*SIGMA*T*T*T*T;
}

real F(real t, real T)
{
    return (P_in() - P_out(t, T)) / THETA;
}

// Euler explicit integration method
// t_final: end year (e.g., 2107 for 100-year simulation from 2007)
// steps: number of integration steps
real euler(real t_final, int steps)
{
    real h = (t_final - t0) / steps;  // Integration step size
    real t = t0;               // Current time, starting at t0 (2007)
    real T = T0;               // Current temperature, starting at T0
    
    // Print initial condition
    printf("%.1f %.6f\n", t, T);
    
    // Perform Euler iterations
    for (int i = 0; i < steps; i++) {
        T = T + h * F(t, T);   // Euler formula: T_{n+1} = T_n + h * F(t_n, T_n)
        t = t + h;
        printf("%.1f %.6f\n", t, T);
    }
    
    return T;  // Return final temperature
}

// Set the RCP scenario for simulation
void set_rcp_scenario(rcp_scenario_t rcp) {
    current_rcp = rcp;
}

// Run simulation for a specific RCP scenario and save to file
void run_rcp_simulation(rcp_scenario_t rcp, const char* filename) {
    set_rcp_scenario(rcp);
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot create file %s\n", filename);
        return;
    }
    
    real h = (2107.0 - t0) / 1000;  // 1000 steps for 100 years
    real t = t0;
    real T = T0;
    
    // Print initial condition
    fprintf(file, "%.1f %.6f\n", t, T);
    
    // Perform Euler iterations
    for (int i = 0; i < 1000; i++) {
        T = T + h * F(t, T);
        t = t + h;
        fprintf(file, "%.1f %.6f\n", t, T);
    }
    
    fclose(file);
    
    const char* scenario_name = (rcp == RCP_26) ? "RCP2.6" : 
                               (rcp == RCP_60) ? "RCP6.0" : "Constant";
    printf("%s: %.3f K (+%.3f)\n", scenario_name, T, T - T0);
}

// Calculate high precision reference value
real calculate_reference_value() {
    set_rcp_scenario(RCP_CONSTANT);  // Use constant CO2 for error analysis
    
    real h = (2107.0 - t0) / 5000;  // 5000 steps for high precision
    real t = t0;
    real T = T0;
    
    for (int i = 0; i < 5000; i++) {
        T = T + h * F(t, T);
        t = t + h;
    }
    
    return T;
}

// Simulate with given number of steps (no output)
real simulate_steps(int steps) {
    set_rcp_scenario(RCP_CONSTANT);  // Use constant CO2 for error analysis
    
    real h = (2107.0 - t0) / steps;
    real t = t0;
    real T = T0;
    
    for (int i = 0; i < steps; i++) {
        T = T + h * F(t, T);
        t = t + h;
    }
    
    return T;
}

// Error analysis function
void errors() {
    const real reference = 288.695127319877258;  // Reference value from 5000 steps
    
    printf("# Steps Error\n");
    
    for (int steps = 16; steps <= 65536; steps *= 2) {
        real result = simulate_steps(steps);
        real error = fabs(result - reference);
        printf("%d %.15e\n", steps, error);
    }
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "reference") == 0) {
        // Calculate reference value with 5000 steps
        real ref = calculate_reference_value();
        printf("Reference value (5000 steps, double precision): %.15f K\n", ref);
        return 0;
    }
    
    if (argc > 1 && strcmp(argv[1], "errors") == 0) {
        // Perform error analysis
        errors();
        return 0;
    }
    
    printf("Climate Simulation Results (2107):\n");
    
    run_rcp_simulation(RCP_CONSTANT, "output_constant.dat");
    run_rcp_simulation(RCP_26, "output_rcp26.dat");
    run_rcp_simulation(RCP_60, "output_rcp60.dat");
    
    return 0;
}