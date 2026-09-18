#pragma once

#include <vector>

#include <omp.h>

namespace stream {

template <typename T>
auto init(std::vector<T>& a, T val) -> void {
  int size = a.size();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    a[i] = val;
  }
}

template <typename T>
auto copy(std::vector<T>& c, std::vector<T> const& a) -> void {
  int size = c.size();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    c[i] = a[i];
  }
}

template <typename T>
auto mul(std::vector<T>& c, T alpha, std::vector<T> const& a) -> void {
  int size = c.size();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    c[i] = alpha * a[i];
  }
}

template <typename T>
auto add(std::vector<T>& c, std::vector<T> const& a, std::vector<T> const& b) -> void {
  int size = c.size();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    c[i] = a[i] + b[i];
  }
}

template <typename T>
auto triad(std::vector<T>& c, T alpha, std::vector<T> const& a, std::vector<T> const& b) -> void {
  int size = c.size();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    c[i] = alpha * a[i] + b[i];
  }
}

template <typename T>
auto dot(std::vector<T> const& a, std::vector<T> const& b) -> T {
  int size = a.size();
  T sum{0};
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}

} // namespace stream
