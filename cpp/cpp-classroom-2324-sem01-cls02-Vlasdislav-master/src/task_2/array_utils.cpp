#include "array_utils.hpp"
#include <algorithm>
#include <numeric>
#include <set>

using const_int_pointer_t = const int*;


int sum(const_int_pointer_t a, size_t s) {
    return std::accumulate(a, a + s, 0ll);
}

int countNumbers(const_int_pointer_t a, size_t s) {
    int b[10]{};
    for (size_t i = 0; i < s; ++i) {
        ++b[a[i]];
    }
    int res = 0;
    for (size_t i = 0; i < 10; ++i) {
        res += static_cast<bool>(b[i]);
    }
    return res;
}

void popZeros(const_int_pointer_t *a, size_t s) {
    size_t j = 0;
    for (size_t i = 0; i < s; ++i) {
        if (a[i] == nullptr || *a[i] != 0) {
            std::swap(a[i], a[j]);
            ++j;
        }
    }
}