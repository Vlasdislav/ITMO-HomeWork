#pragma once

#include <numeric>

char const* concat(
    char const a[],
    std::size_t a_size,
    char const b[],
    std::size_t b_size,
    std::size_t& concat_size
);
