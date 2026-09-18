/// ***************************************************************************
/// PSEUDO-RANDOM NUMBER GENERATOR
/// ***************************************************************************
///
/// A simple linear congruential random number generator (Numerical Recipies
/// chapter 7, 1st ed.) with parameters from the table on page 198j.
///
/// Uses a linear congruential generator to return a value between 0 and 1,
/// then scales and shifts it to fill the desired range.  This range is set
/// when the random number generator seed is called.
///
/// # USAGE
///
/// Pseudo-random sequence is seeded with a range:
///
///   void seed(lower_limit, higher_limit);
///
/// And then subsequent calls to the random number generator generates values
/// in the sequence:
///
///   double random();
///
/// # HISTORY
///
/// - 09/2007: Written by Tim Mattson;
/// - 01/2015: Adapted for TOP course by Julien Jaeger;
/// - 03/2025: Updated by Gabriel Dos Santos.

#ifndef TOP_PRNG_H
#define TOP_PRNG_H

/// @brief Set PRNG seed and range.
///
/// @param lo_bound PRNG lower bound.
/// @param hi_bound PRNG higher bound.
void prng_seed(double lo_bound, double hi_bound);

/// @brief Generate a pseudo-random value.
///
/// @return A double-precision value in the range 0 and 1, and shift it to the
///         range provide in `seed`, if any.
double prng_random();

#endif // TOP_PRNG_H
