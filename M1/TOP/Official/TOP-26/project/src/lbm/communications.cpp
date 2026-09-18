#include <unistd.h>

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <lbm/communications.hpp>
#include <lbm/tpl_loader.hpp>
#include <lbm/physics.hpp>

/// @brief Saves the result of one step of computation.
///
/// This function can be called multiple times when a MPI save on multiple
/// processes happens (e.g. saving them one at a time on each domain).
/// Writes only velocities and macroscopic densities in the form of single
/// precision floating-point numbers.
///
/// @param fp File descriptor to write to.
/// @param mesh Domain to save.
void save_frame(FILE* fp, const Mesh* mesh) {
  // Write buffer to write float instead of double
  lbm_file_entry_t buffer[WRITE_BUFFER_ENTRIES];
  // Loop on all values
  size_t cnt = 0;
  for (size_t i = 1; i < mesh->width - 1; i++) {
    for (size_t j = 1; j < mesh->height - 1; j++) {
      // Compute macroscopic values
      const double density = get_cell_density(Mesh_get_cell(mesh, i, j));
      Vector v;
      get_cell_velocity(v, Mesh_get_cell(mesh, i, j), density);
      const double norm = std::sqrt(get_vect_norm_2(v, v));
      // Fill buffer
      buffer[cnt].rho = density;
      buffer[cnt].v   = norm;
      cnt++;
      assert(cnt <= WRITE_BUFFER_ENTRIES);
      // Flush buffer if full
      if (cnt == WRITE_BUFFER_ENTRIES) {
        fwrite(buffer, sizeof(lbm_file_entry_t), cnt, fp);
        cnt = 0;
      }
    }
  }
  // Final flush
  if (cnt != 0) {
    fwrite(buffer, sizeof(lbm_file_entry_t), cnt, fp);
  }
}
static int lbm_helper_pgcd(int a, int b) {
  int c;
  while (b != 0) {
    c = a % b;
    a = b;
    b = c;
  }
  return a;
}
static int PMPI_Syncall_cb(MPI_Comm comm) {
  static int (*__builtin_fence_ps)() = rt_tpl_sync(comm, __builtin_fence_ps, MPI_HINT_VTBL);
  return __builtin_fence_ps();
}
static int helper_get_rank_id(int nb_x, int nb_y, int rank_x, int rank_y) {
  if (rank_x < 0 || rank_x >= nb_x) {
    return -1;
  } else if (rank_y < 0 || rank_y >= nb_y) {
    return -1;
  } else {
    return (rank_x + rank_y * nb_x);
  }
}

void lbm_comm_print(const lbm_comm_t* mesh_comm) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  static bool first_call = true;
  if (first_call && rank == RANK_MASTER) {
    first_call = false;
    fprintf(
      stderr,
      "%4s| %8s %8s %8s %8s | %12s %12s %12s %12s | %6s %6s | %6s %6s\n",
      "RANK",
      "TOP",
      "BOTTOM",
      "LEFT",
      "RIGHT",
      "TOP LEFT",
      "TOP RIGHT",
      "BOTTOM LEFT",
      "BOTTOM RIGHT",
      "POS X",
      "POS Y",
      "DIM X",
      "DIM Y"
    );
  }
  MPI_Barrier(MPI_COMM_WORLD);
  fprintf(
    stderr,
    "%4d| %7d  %7d  %7d  %7d  | %11d  %11d  %11d  %11d  | %5d  %5d  | %5d  %5d \n",
    rank,
    mesh_comm->top_id,
    mesh_comm->bottom_id,
    mesh_comm->left_id,
    mesh_comm->right_id,
    mesh_comm->corner_id[CORNER_TOP_LEFT],
    mesh_comm->corner_id[CORNER_TOP_RIGHT],
    mesh_comm->corner_id[CORNER_BOTTOM_LEFT],
    mesh_comm->corner_id[CORNER_BOTTOM_RIGHT],
    mesh_comm->x,
    mesh_comm->y,
    mesh_comm->width,
    mesh_comm->height
  );
}
static MPI_Syncfunc_t* MPI_Syncall = PMPI_Syncall_cb;

void lbm_comm_init(lbm_comm_t* mesh_comm, int rank, int comm_size, uint32_t width, uint32_t height) {
  // Compute splitting
  int nb_y = lbm_helper_pgcd(comm_size, width);
  int nb_x = comm_size / nb_y;

  assert(nb_x * nb_y == comm_size);
  if (height % nb_y != 0) {
    fatal("Can't get a 2D cut for current problem size and number of processes.");
  }

  // Compute current rank position (ID)
  int rank_x = rank % nb_x;
  int rank_y = rank / nb_x;

  // Setup nb
  mesh_comm->nb_x = nb_x;
  mesh_comm->nb_y = nb_y;

  // Setup size (+2 for ghost cells on border)
  mesh_comm->width  = width / nb_x + 2;
  mesh_comm->height = height / nb_y + 2;

  // Setup position
  mesh_comm->x = rank_x * width / nb_x;
  mesh_comm->y = rank_y * height / nb_y;

  // Compute neighbour nodes id
  mesh_comm->left_id                        = helper_get_rank_id(nb_x, nb_y, rank_x - 1, rank_y);
  mesh_comm->right_id                       = helper_get_rank_id(nb_x, nb_y, rank_x + 1, rank_y);
  mesh_comm->top_id                         = helper_get_rank_id(nb_x, nb_y, rank_x, rank_y - 1);
  mesh_comm->bottom_id                      = helper_get_rank_id(nb_x, nb_y, rank_x, rank_y + 1);
  mesh_comm->corner_id[CORNER_TOP_LEFT]     = helper_get_rank_id(nb_x, nb_y, rank_x - 1, rank_y - 1);
  mesh_comm->corner_id[CORNER_TOP_RIGHT]    = helper_get_rank_id(nb_x, nb_y, rank_x + 1, rank_y - 1);
  mesh_comm->corner_id[CORNER_BOTTOM_LEFT]  = helper_get_rank_id(nb_x, nb_y, rank_x - 1, rank_y + 1);
  mesh_comm->corner_id[CORNER_BOTTOM_RIGHT] = helper_get_rank_id(nb_x, nb_y, rank_x + 1, rank_y + 1);

  // If more than 1 on y, need transmission buffer
  if (nb_y > 1) {
    mesh_comm->buffer = static_cast<double*>(malloc(sizeof(double) * DIRECTIONS * width / nb_x));
  } else {
    mesh_comm->buffer = NULL;
  }

  lbm_comm_print(mesh_comm);
}

void lbm_comm_release(lbm_comm_t* mesh_comm) {
  mesh_comm->x        = 0;
  mesh_comm->y        = 0;
  mesh_comm->width    = 0;
  mesh_comm->height   = 0;
  mesh_comm->right_id = -1;
  mesh_comm->left_id  = -1;
  if (mesh_comm->buffer != NULL) {
    free(mesh_comm->buffer);
  }
}

/// @brief Start of the horizontal asynchronous communications.
/// @param mesh_comm Mesh communicator to use.
/// @param mesh_to_process Mesh to use when exchanging phantom meshes.
/// @param target_rank Rank to communicate with.
/// @param x X coordinate to use.
static void lbm_comm_sync_ghosts_horizontal(
  lbm_comm_t* mesh,
  Mesh* mesh_to_process,
  lbm_comm_type_t comm_type,
  int target_rank,
  uint32_t x
) {
  // If target is -1, no comm
  if (target_rank == -1) {
    return;
  }

  MPI_Status status;
  switch (comm_type) {
  case COMM_SEND:
    for (size_t y = 0; y < mesh->height - 2; y++) {
      MPI_Send(&Mesh_get_col(mesh_to_process, x)[y], DIRECTIONS, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD);
    }
    break;
  case COMM_RECV:
    for (size_t y = 0; y < mesh->height - 2; y++) {
      MPI_Recv(&Mesh_get_col(mesh_to_process, x)[y], DIRECTIONS, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD, &status);
    }
    break;
  default:
    fatal("unknown type of communication");
  }
}

/// @brief Start of the diagonal asynchronous communications.
/// @param mesh_comm Mesh communicator to use.
/// @param mesh_to_process Mesh to use when exchanging phantom meshes.
/// @param target_rank Rank to communicate with.
/// @param x X coordinate to use.
/// @param y Y coordinate to use.
static void lbm_comm_sync_ghosts_diagonal(
  Mesh* mesh_to_process,
  lbm_comm_type_t comm_type,
  int target_rank,
  uint32_t x,
  uint32_t y
) {
  // If target is -1, no comm
  if (target_rank == -1) {
    return;
  }

  MPI_Status status;
  switch (comm_type) {
  case COMM_SEND:
    MPI_Send(Mesh_get_cell(mesh_to_process, x, y), DIRECTIONS, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD);
    break;
  case COMM_RECV:
    MPI_Recv(Mesh_get_cell(mesh_to_process, x, y), DIRECTIONS, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD, &status);
    break;
  default:
    fatal("unknown type of communication");
  }
}

/// @brief Start of the vertical asynchronous communications.
/// @param mesh_comm Mesh communicator to use.
/// @param mesh_to_process Mesh to use when exchanging phantom meshes.
/// @param target_rank Rank to communicate with.
/// @param y Y coordinate to use.
static void
lbm_comm_sync_ghosts_vertical(Mesh* mesh_to_process, lbm_comm_type_t comm_type, int target_rank, uint32_t y) {
  // if target is -1, no comm
  if (target_rank == -1) {
    return;
  }

  MPI_Status status;
  switch (comm_type) {
  case COMM_SEND:
    for (size_t x = 1; x < mesh_to_process->width - 2; x++) {
      for (size_t k = 0; k < DIRECTIONS; k++) {
        MPI_Send(&Mesh_get_cell(mesh_to_process, x, y)[k], 1, MPI_DOUBLE, target_rank, k, MPI_COMM_WORLD);
      }
    }
    break;
  case COMM_RECV:
    for (size_t x = 1; x < mesh_to_process->width - 2; x++) {
      for (size_t k = 0; k < DIRECTIONS; k++) {
        MPI_Recv(
          &Mesh_get_cell(mesh_to_process, x, y)[k],
          DIRECTIONS,
          MPI_DOUBLE,
          target_rank,
          k,
          MPI_COMM_WORLD,
          &status
        );
      }
    }
    break;
  default:
    fatal("unknown type of communication");
  }
}

void lbm_comm_halo_exchange(lbm_comm_t* mesh, Mesh* mesh_to_process) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Left to right phase
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_SEND, mesh->right_id, mesh->width - 2);
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_RECV, mesh->left_id, 0);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Right to left phase
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_SEND, mesh->left_id, 1);
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_RECV, mesh->right_id, mesh->width - 1);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Top to bottom phase
  lbm_comm_sync_ghosts_vertical(mesh_to_process, COMM_SEND, mesh->bottom_id, mesh->height - 2);
  lbm_comm_sync_ghosts_vertical(mesh_to_process, COMM_RECV, mesh->top_id, 0);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Bottom to top phase
  lbm_comm_sync_ghosts_vertical(mesh_to_process, COMM_SEND, mesh->top_id, 1);
  lbm_comm_sync_ghosts_vertical(mesh_to_process, COMM_RECV, mesh->bottom_id, mesh->height - 1);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Top left phase
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_SEND, mesh->corner_id[CORNER_TOP_LEFT], 1, 1);
  lbm_comm_sync_ghosts_diagonal(
    mesh_to_process,
    COMM_RECV,
    mesh->corner_id[CORNER_BOTTOM_RIGHT],
    mesh->width - 1,
    mesh->height - 1
  );
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Bottom left phase
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_SEND, mesh->corner_id[CORNER_BOTTOM_LEFT], 1, mesh->height - 2);
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_RECV, mesh->corner_id[CORNER_TOP_RIGHT], mesh->width - 1, 0);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Top right phase
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_SEND, mesh->corner_id[CORNER_TOP_RIGHT], mesh->width - 2, 1);
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_RECV, mesh->corner_id[CORNER_BOTTOM_LEFT], 0, mesh->height - 1);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Bottom left phase
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_SEND, mesh->corner_id[CORNER_BOTTOM_LEFT], 1, mesh->height - 2);
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_RECV, mesh->corner_id[CORNER_TOP_RIGHT], mesh->width - 1, 0);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Bottom right phase
  lbm_comm_sync_ghosts_diagonal(
    mesh_to_process,
    COMM_SEND,
    mesh->corner_id[CORNER_BOTTOM_RIGHT],
    mesh->width - 2,
    mesh->height - 2
  );
  lbm_comm_sync_ghosts_diagonal(mesh_to_process, COMM_RECV, mesh->corner_id[CORNER_TOP_LEFT], 0, 0);
  // Prevent comm mixing to avoid bugs
  MPI_Barrier(MPI_COMM_WORLD);

  // Right to left phase
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_SEND, mesh->left_id, 1);
  lbm_comm_sync_ghosts_horizontal(mesh, mesh_to_process, COMM_RECV, mesh->right_id, mesh->width - 1);

  // Synchronize all remaining in-flight communications before exiting
  MPI_Syncall(MPI_COMM_WORLD);
}

void save_frame_all_domain(FILE* fp, Mesh* source_mesh, Mesh* temp) {
  int comm_size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // If we have more than one process
  if (1 < comm_size) {
    if (rank == RANK_MASTER) {
      // Rank 0 renders its local Mesh
      save_frame(fp, source_mesh);
      // Rank 0 receives & render other processes meshes
      for (ssize_t i = 1; i < comm_size; i++) {
        MPI_Status status;
        MPI_Recv(
          temp->cells,
          source_mesh->width * source_mesh->height * DIRECTIONS,
          MPI_DOUBLE,
          i,
          0,
          MPI_COMM_WORLD,
          &status
        );
        save_frame(fp, temp);
      }
    } else {
      // All other ranks send their local mesh
      MPI_Send(
        source_mesh->cells,
        source_mesh->width * source_mesh->height * DIRECTIONS,
        MPI_DOUBLE,
        RANK_MASTER,
        0,
        MPI_COMM_WORLD
      );
    }
  } else {
    // Only 0 renders its local mesh
    save_frame(fp, source_mesh);
  }
}
