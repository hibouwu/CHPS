#include <chrono>
#include <cmath>
#include <locale>
#include <vector>

#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include <moldyn/avgvel.hpp>
#include <moldyn/ekin.hpp>
#include <moldyn/fcc.hpp>
#include <moldyn/forces.hpp>
#include <moldyn/init.hpp>
#include <moldyn/maxwell.hpp>
#include <moldyn/scale.hpp>
#include <moldyn/update.hpp>

#define MAXI
#if defined(MAXI)
constexpr int64_t DIM = 15;
#elif defined(MEDIUM)
constexpr int64_t DIM = 10;
#elif defined(MINI)
constexpr int64_t DIM = 7;
#else
#error "`NPART` is not correctly defined. To build: -DNPART=<MINI|MEDIUM|MAXI>"
#endif
constexpr int64_t NPART = 4 * DIM * DIM * DIM;

using std::chrono::high_resolution_clock;

constexpr double den        = 0.83134;
constexpr double side       = std::pow(double(NPART) / den, 0.3333333);
constexpr double t_ref      = 0.722;
constexpr double r_cutoff   = double(DIM) / 4.0;
constexpr double h          = 0.064;
constexpr int64_t i_reps    = 10;
constexpr int64_t i_stop    = 20;
constexpr int64_t i_print   = 5;
constexpr int64_t max_steps = 20;

constexpr double alpha    = side / double(DIM);
constexpr double h_sq     = h * h;
constexpr double half_hsq = h_sq * 0.5;
constexpr double t_scale  = 16.0 / (double(NPART) - 1.0);
constexpr double v_avg    = 1.13 * std::sqrt(t_ref / 24.0);

namespace md {

auto print_info(void) -> void {
  fmt::print(
    "┌{0:─^77}┐\n"
    "│{1: ^77}│\n"
    "│{2: ^77}│\n"
    "└{0:─^77}┘\n",
    "",
    "M1 CHPS TOP - LAB 1: TOOLCHAINS & HPC ENVIRONMENT",
    "MOLECULAR DYNAMICS SIMULATION"
  );
  fmt::print(
    "{:.<32} {:<6}\n"
    "{:.<32} {:<13.6f}\n"
    "{:.<32} {:<13.6f}\n"
    "{:.<32} {:<13.6f}\n"
    "{:.<32} {:<13.6f}\n"
    "{:.<32} {:<6}\n"
    "{:.<32} {:<6}\n"
    "{:.<32} {:<6}\n"
    "{:.<32} {:<6}\n",
    " Number of particles ",
    NPART,
    " Box side length ",
    side,
    " Cut off ",
    r_cutoff,
    " Time step ",
    h,
    " Reduced temperature ",
    t_ref,
    " Temperature scale interval ",
    i_reps,
    " Stop scaling at move ",
    i_stop,
    " Print interval ",
    i_print,
    " Total number of steps ",
    max_steps
  );
  fmt::println("{0:─^79}", "");
}

auto print_step(
  int64_t step, int64_t n, double e_kin, double e_pot, double t_scale, double vir, double vel, double count, double den
) {
  double ek   = 24.0 * e_kin;
  double ep   = 4.0 * e_pot;
  double et   = ek + ep;
  double temp = t_scale * e_kin;
  double pres = den * 16.0 * (e_kin - vir) / double(n);
  double v    = vel / double(n);
  double rp   = (count / double(n)) * 100.0;

  fmt::print(
    "{: >9}  {: > 13.4f}  {: > 13.4f}  {: > 13.4f}  {: > 9.3f}  {: > 9.3f}  {: > 9.3f}  {: > 9.3f}\n",
    step,
    ek,
    ep,
    et,
    temp,
    pres,
    v,
    rp
  );
}

} // namespace md

// Main program : Molecular Dynamics simulation.
auto main(void) -> int {
  md::print_info();

  std::vector<double> x(3 * NPART);
  std::vector<double> f(3 * NPART);
  std::vector<double> vh(3 * NPART);

  // Generate FCC lattice for atoms inside box
  md::fcc(DIM, alpha, x);

  // Initialize velocities and forces (which are zero in FCC positions)
  md::maxwell(NPART, vh, h, t_ref, t_scale);
  md::init_forces(f, 0.0);

  // Start of simulation
  fmt::print(
    "{1: >9}  {2: >13}  {3: >13}  {4: >13}  {5: >9}  {6: >9}  {7: >9}  {8: >9}\n"
    "{0:─^10} {0:─^14} {0:─^14} {0:─^14} {0:─^10} {0:─^10} {0:─^10} {0:─^10}\n",
    "",
    "i",
    "e_kin",
    "e_pot",
    "e_tot",
    "temp",
    "pres",
    "vel",
    "rp"
  );

  double e_pot, vir, count;
  auto t0 = high_resolution_clock::now();
  for (int64_t step = 1; step <= max_steps; ++step) {
    // Move the particles and partially update velocities
    md::update_particles(NPART, x, vh, f, side);

    // Compute forces in the new positions and accumulate the virial and
    // potential energy
    md::compute_forces(NPART, x, f, side, r_cutoff, e_pot, vir);

    // Scale forces, complete update of velocities and compute kinetic energy
    double e_kin = md::compute_kinetic_energy(NPART, f, vh, half_hsq, h_sq);

    // Average the velocity and temperature scale if desired
    double vel = md::compute_average_velocity(NPART, vh, v_avg, h, count);
    if ((step < i_stop && step % i_reps) == 0) {
      double sc = std::sqrt(t_ref / (t_scale * e_kin));
      md::scale_velocities(NPART, sc, vh);
      e_kin = t_ref / t_scale;
    }

    // Sum to get full potential energy and virial
    if (step % i_print == 0) {
      md::print_step(step, NPART, e_kin, e_pot, t_scale, vir, vel, count, den);
    }
  }
  auto t1 = high_resolution_clock::now();

  auto elapsed = std::chrono::duration<double>(t1 - t0);
  fmt::println("{:─^79}\nTime: {:.3}", "", elapsed);

  return 0;
}
