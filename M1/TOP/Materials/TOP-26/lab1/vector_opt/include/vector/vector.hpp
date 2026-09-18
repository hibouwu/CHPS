#pragma once

#include <cassert>
#include <cstdint>

template <typename T>
class Vector {
public:
  constexpr explicit Vector(int64_t size)
      : size_(size) {
    ptr_ = new T[size];
  }

  constexpr explicit Vector(int64_t size, T val)
      : Vector(size) {
    for (int64_t i = 0; i < size_; ++i) {
      ptr_[i] = val;
    }
  }

  ~Vector() noexcept {
    delete[] ptr_;
  }

  Vector(Vector const& other)                    = delete;
  Vector(Vector&& other)                         = delete;
  auto operator=(Vector const& other) -> Vector& = delete;
  auto operator=(Vector&& other) -> Vector&      = delete;

  constexpr auto operator[](int64_t n) noexcept -> T& {
    assert(n < size_);
    return *(ptr_ + n);
  }

  constexpr auto operator[](int64_t n) const noexcept -> T const& {
    assert(n < size_);
    return *(ptr_ + n);
  }

  static auto add(Vector& dest, Vector const& src1, Vector const& src2) -> void {
    assert(src1.size_ == src1.size_);
    assert(dest.size_ == src2.size_);
    for (int64_t i = 0; i < dest.size_; ++i) {
      dest[i] = src1[i] + src2[i];
    }
  }

private:
  int64_t size_;
  T* ptr_;
};
