#include "compute_fib.hpp"
#include <iostream>
#include <cstdint>
#include <fstream>
#include <algorithm>

int64_t compute_fib() {
    std::ifstream fin("input.txt");
    size_t n;
    fin >> n;
    if (n <= 2) {
        return std::min(static_cast<int>(n), 1);
    }
    int64_t a = 1, b = 1;
    for (size_t i = 2; i < n; ++i) {
        std::swap(a, b);
        b += a;
    }
    return b;
}