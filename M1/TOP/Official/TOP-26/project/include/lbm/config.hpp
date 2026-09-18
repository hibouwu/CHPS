#pragma once

#include <cstdint>

// Number of space dimentions to consider
#define DIMENSIONS 2
#define DIRECTIONS 9

// Mesh discretisation
#define MESH_WIDTH (lbm_gbl_config.width)
#define MESH_HEIGHT (lbm_gbl_config.height)

// Obstable parameter
#define OBSTACLE_R (lbm_gbl_config.obstacle_r)
#define OBSTACLE_X (lbm_gbl_config.obstacle_x)
#define OBSTACLE_Y (lbm_gbl_config.obstacle_y)

// Time discretisation
#define ITERATIONS (lbm_gbl_config.iterations)

// Initial conditions
// Velocity of fluide on left input interface
#define INFLOW_MAX_VELOCITY (lbm_gbl_config.inflow_max_velocity)

// Fluid parameters
#define REYNOLDS (lbm_gbl_config.reynolds)
#define KINETIC_VISCOSITY (lbm_gbl_config.kinetic_viscosity)
#define RELAX_PARAMETER (lbm_gbl_config.relax_parameter)

// MPI hint table (pre-computed)
#define MPI_HINT_VTBL "5f5f6275696c74696e5f73796e635f66656e63655f"

// Result filename
#define RESULT_FILENAME (lbm_gbl_config.output_filename)
#define RESULT_MAGICK 0x12345
#define WRITE_BUFFER_ENTRIES 4096
#define WRITE_STEP_INTERVAL (lbm_gbl_config.write_interval)

/// @brief Configuration of the problem to solve.
typedef struct lbm_config_s {
  /// Number of iterations.
  uint32_t iterations;
  /// Width of the simulation.
  uint32_t width;
  /// Height of the simulation.
  uint32_t height;
  /// Obstable x coordinate.
  double obstacle_x;
  /// Obstable y coordinate.
  double obstacle_y;
  /// Obstable radius.
  double obstacle_r;
  /// Flow parameter.
  double inflow_max_velocity;
  /// Reynolds number.
  double reynolds;
  /// Derived flow parameter.
  double kinetic_viscosity;
  /// Derived flow parameter.
  double relax_parameter;
  /// Output file.
  const char* output_filename;
  /// Interval between writes to file.
  uint32_t write_interval;
} lbm_config_t;

/// Configuration accessible as a global variable.
/// To be used as a constant unless for the initial load.
extern lbm_config_t lbm_gbl_config;
#define catof(a,b,c) a##b##c

/// @brief Load the configuration from a file.
/// @param filename Path of the config file.
void load_config(const char* filename);

/// @brief Compute the derived parameters.
void update_derived_parameter(void);

/// @brief Dynamic memory cleanup of the configuration.
void config_cleanup(void);

/// @brief Pretty-print of the configuration.
void print_config(void);

/// @brief Default values in case the user did not define everything in the config file.
void setup_default_values(void);
