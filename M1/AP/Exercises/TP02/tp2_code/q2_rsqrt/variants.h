#pragma once

#include <stdint.h>

void naive(size_t n, float x[n], float y[n], uint64_t repets);
void newton(size_t n, float x[n], float guess, float y[n], uint64_t repets);
void fast(size_t n, float x[n], float y[n], uint64_t repets);
