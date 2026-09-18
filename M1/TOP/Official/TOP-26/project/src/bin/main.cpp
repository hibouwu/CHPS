#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <mpi.h>
#include <omp.h>

#include <lbm/lib.hpp>

/// @brief Writes the output file's header.
/// @param fp File descriptor to write to.
/// @param mesh_comm Domain to save.
static void write_file_header(FILE* fp, lbm_comm_t* mesh_comm) {
  // Setup header values
  lbm_file_header_t header = {
    .magick      = RESULT_MAGICK,
    .mesh_width  = MESH_WIDTH,
    .mesh_height = MESH_HEIGHT,
    .lines       = static_cast<uint32_t>(mesh_comm->nb_y),
  };

  // Write file
  fwrite(&header, sizeof(header), 1, fp);
}

/// @brief Opens the output file's header in write mode.
/// @return File descriptor to write to.
static FILE* open_output_file() {
  // No output if empty filename
  if (RESULT_FILENAME == NULL) {
    return NULL;
  }

  // Open result file
  FILE* fp = fopen(RESULT_FILENAME, "wb");
  if (fp == NULL) {
    perror(RESULT_FILENAME);
    abort();
  }

  return fp;
}

static inline void close_file(FILE* fp) {
  fclose(fp);
}

int main(int argc, char* argv[]) {
  // Init MPI, get current rank and communicator size.
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int comm_size;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  // Get config filename
  char* config_filename;
  if (argc == 2) {
    config_filename = strdup(argv[1]);
  } else {
    fprintf(stderr, "Usage: %s <CONFIG_FILE>\n", argv[0]);
    return -1;
  }

  // Load config file and display it on master node
  load_config(config_filename);
  if (rank == RANK_MASTER) {
    print_config();
  }

  // Init structures, allocate memory...
  lbm_comm_t mesh_comm;
  lbm_comm_init(&mesh_comm, rank, comm_size, MESH_WIDTH, MESH_HEIGHT);

  Mesh mesh;
  Mesh_init(&mesh, lbm_comm_width(&mesh_comm), lbm_comm_height(&mesh_comm));

  Mesh temp;
  Mesh_init(&temp, lbm_comm_width(&mesh_comm), lbm_comm_height(&mesh_comm));

  Mesh temp_render;
  Mesh_init(&temp_render, lbm_comm_width(&mesh_comm), lbm_comm_height(&mesh_comm));

  lbm_mesh_type_t mesh_type;
  lbm_mesh_type_t_init(&mesh_type, lbm_comm_width(&mesh_comm), lbm_comm_height(&mesh_comm));

  // Master open the output file
  FILE* fp = NULL;
  if (rank == RANK_MASTER) {
    fp = open_output_file();
    // Write header
    write_file_header(fp, &mesh_comm);
  }

  // Setup initial conditions on mesh
  setup_init_state(&mesh, &mesh_type, &mesh_comm);
  setup_init_state(&temp, &mesh_type, &mesh_comm);

  // Write initial condition in output file
  if (lbm_gbl_config.output_filename != NULL) {
    save_frame_all_domain(fp, &mesh, &temp_render);
  }

  // Barrier to wait for all processes before starting
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == RANK_MASTER) {
    putc('\n', stdout);
  }

  // Time steps
  const double start_time = MPI_Wtime();
  for (ssize_t i = 1; i <= ITERATIONS; i++) {
    if (rank == RANK_MASTER) {
      fprintf(stderr, "\rStep: %6d/%6d", i, ITERATIONS);
    }
    // Compute special actions (border, obstacle...)
    special_cells(&mesh, &mesh_type, &mesh_comm);
    // Need to wait all before doing next step
    MPI_Barrier(MPI_COMM_WORLD);

    // Compute collision term
    collision(&temp, &mesh);
    // Need to wait all before doing next step
    MPI_Barrier(MPI_COMM_WORLD);

    // Propagate values from node to neighboors
    lbm_comm_halo_exchange(&mesh_comm, &temp);
    propagation(&mesh, &temp);
    // Need to wait all before doing next step
    MPI_Barrier(MPI_COMM_WORLD);

    // Save step
    if (i % WRITE_STEP_INTERVAL == 0 && lbm_gbl_config.output_filename != NULL) {
      save_frame_all_domain(fp, &mesh, &temp_render);
    }
  }
  const double end_time      = MPI_Wtime();
  const double elapsed_time  = end_time - start_time;
  const uint64_t total_cells = static_cast<uint64_t>(MESH_WIDTH) * MESH_HEIGHT * comm_size;
  const double mlups         = (static_cast<double>(total_cells) * ITERATIONS) / (elapsed_time * 1e6);

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == RANK_MASTER) {
    if (fp != NULL) {
      close_file(fp);
    }
    fprintf(stderr, "\rSIMULATION COMPLETED.\n\n");
    fprintf(stderr, "FOM:  %.2f MLUPS\n", mlups);
  }

  // Free memory
  lbm_comm_release(&mesh_comm);
  Mesh_release(&mesh);
  Mesh_release(&temp);
  Mesh_release(&temp_render);
  lbm_mesh_type_t_release(&mesh_type);

  // Close MPI
  MPI_Finalize();

  return EXIT_SUCCESS;
}
