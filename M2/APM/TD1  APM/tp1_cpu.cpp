#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Simulate one GPU thread of the original kernel.
void kernel(const double* x, double* y, double alpha, int n,
            int block_idx, int block_dim, int thread_idx) {
    const int i = block_idx * block_dim + thread_idx;
    if (i < n) {
        y[i] = alpha * x[i] + y[i];
    }
}

int main() {
    constexpr int n = 1000;
    constexpr int block_dim = 64;
    constexpr int grid_dim = (n + block_dim - 1) / block_dim;
    constexpr double alpha = 3.14;

    std::vector<double> h_x(n), h_y(n);
    for (int i = 0; i < n; ++i) {
        h_x[i] = 1.0 / (1.0 + i);
        h_y[i] = (i - 1.0) / (i + 1.0);
    }

    // Separate arrays play the role of device memory.
    std::vector<double> d_x(n), d_y(n);
    std::copy(h_x.begin(), h_x.end(), d_x.begin());
    std::copy(h_y.begin(), h_y.end(), d_y.begin());

    for (int block_idx = 0; block_idx < grid_dim; ++block_idx) {
        for (int thread_idx = 0; thread_idx < block_dim; ++thread_idx) {
            kernel(d_x.data(), d_y.data(), alpha, n,
                   block_idx, block_dim, thread_idx);
        }
    }

    std::copy(d_y.begin(), d_y.end(), h_y.begin());

    double max_error = 0.0;
    for (int i = 0; i < n; ++i) {
        const double expected = (i + alpha - 1.0) / (i + 1.0);
        max_error = std::max(max_error, std::abs(h_y[i] - expected));
    }
    std::cout << "blocks=" << grid_dim << " threads_per_block=" << block_dim
              << " launched_threads=" << grid_dim * block_dim << '\n';
    std::cout << "y[0]=" << h_y[0] << " y[999]=" << h_y[999]
              << " max_error=" << max_error << '\n';
    return max_error < 1e-12 ? 0 : 1;
}
