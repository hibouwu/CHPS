#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <omp.h>

#include <fmt/chrono.h>
#include <fmt/core.h>

constexpr uint64_t NSTEPS = 1'000;

enum class CellType : uint8_t { Fluid, Boundary, Ghost, Object, Unknown };

struct Cell {
  int id_;
  double velocity_;
  char name_abrev_;
  float pressure_;
  bool is_ghost_;
  uint16_t x_;
  double acceleration_;
  uint16_t y_;
  CellType kind_;

  static auto build(int32_t id, char name_abrev, uint16_t max_x, uint16_t max_y) -> Cell {
    CellType kind = CellType::Unknown;
    switch (name_abrev) {
    case 'f':
      kind = CellType::Fluid;
      break;
    case 'b':
      kind = CellType::Boundary;
      break;
    case 'g':
      kind = CellType::Ghost;
      break;
    case 'o':
      kind = CellType::Object;
      break;
    default:
      kind = CellType::Unknown;
    }
    bool is_ghost       = name_abrev == 'g' ? true : false;
    float pressure      = float(drand48()) * float(lrand48() % 1'000'000);
    double acceleration = drand48();
    double velocity     = drand48();
    uint16_t x          = (uint16_t)(lrand48() % max_x);
    uint16_t y          = (uint16_t)(lrand48() % max_y);

    return Cell(id, velocity, name_abrev, pressure, is_ghost, x, acceleration, y, kind);
  }

private:
  explicit Cell(
    int id,
    double velocity,
    char name_abrev,
    float pressure,
    bool is_ghost,
    uint16_t x,
    double acceleration,
    uint16_t y,
    CellType kind
  ) noexcept
      : id_(id),
        velocity_(velocity),
        name_abrev_(name_abrev),
        pressure_(pressure),
        is_ghost_(is_ghost),
        x_(x),
        acceleration_(acceleration),
        y_(y),
        kind_(kind) {}
};

struct Mesh {
  uint16_t nx_;
  uint16_t ny_;
  Cell* cells_;

  Mesh(uint16_t nx, uint16_t ny)
      : nx_(nx), ny_(ny) {
    size_t size = nx * ny;
    cells_      = (Cell*)malloc(size * sizeof(Cell));
  }

  ~Mesh() {
    free(cells_);
  }

  Mesh(Mesh const& rhs)                    = delete;
  Mesh(Mesh&& rhs)                         = delete;
  auto operator=(Mesh const& rhs) -> Mesh& = delete;
  auto operator=(Mesh&& rhs) -> Mesh&      = delete;

  auto init() -> void {
    for (size_t id = 0; id < nx_ * ny_; ++id) {
      char rnd = (char)(lrand48() % 5);
      char name_abrev;
      switch (rnd) {
      case 0:
        name_abrev = 'f';
        break;
      case 1:
        name_abrev = 'b';
        break;
      case 2:
        name_abrev = 'g';
        break;
      case 3:
        name_abrev = 'o';
        break;
      case 4:
        name_abrev = 'u';
        break;
      default:
        __builtin_unreachable();
      }

      cells_[id] = Cell::build((int)id, name_abrev, nx_, ny_);
    }
  }

  auto compute_velocity(int nthreads) -> void {
#pragma omp parallel for num_threads(nthreads)
    for (size_t i = 0; i < nx_; ++i) {
      cells_[i].acceleration_ = 0.0;
      for (size_t j = 0; j < ny_; ++j) {
        if (i != j) {
          cells_[i].acceleration_ += 0.1337 * (cells_[j].x_ - cells_[i].x_) + (cells_[j].y_ - cells_[i].y_);
        }
      }
    }

#pragma omp parallel for num_threads(nthreads)
    for (size_t c = 0; c < nx_ * ny_; ++c) {
      cells_[c].velocity_ += cells_[c].acceleration_;
    }
  }
};

auto main(int argc, char* argv[]) -> int {
  if (argc < 4) {
    fmt::print(stderr, "Usage: %s <NCELLS_X> <NCELLS_Y> <NTHREADS>\n", argv[0]);
    return -1;
  }

  auto nx       = uint16_t(std::atoi(argv[1]));
  auto ny       = uint16_t(std::atoi(argv[2]));
  auto nthreads = std::atoi(argv[3]);

  auto mesh = Mesh(nx, ny);
  mesh.init();

  auto t0 = std::chrono::high_resolution_clock::now();
  for (size_t it = 0; it < NSTEPS; ++it) {
    mesh.compute_velocity(nthreads);
  }
  auto t1            = std::chrono::high_resolution_clock::now();
  auto total_elapsed = std::chrono::duration<double, std::milli>(t1 - t0);
  auto avg_step      = total_elapsed / NSTEPS;
  fmt::print("{} {:.6} {:.6}\n", nthreads, total_elapsed, avg_step);

  return 0;
}
