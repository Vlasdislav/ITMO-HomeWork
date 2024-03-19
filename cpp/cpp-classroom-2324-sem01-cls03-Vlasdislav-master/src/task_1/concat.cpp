#include "concat.hpp"

char const* concat(
    char const a[],
    std::size_t a_size,
    char const b[],
    std::size_t b_size,
    std::size_t& concat_size
) {
    concat_size = a_size + b_size;
    char* res = new char[concat_size];
    for (std::size_t i = 0; i < a_size; ++i) {
        res[i] = a[i];
    }
    for (std::size_t i = 0; i < b_size; ++i) {
        res[i + a_size] = b[i];
    }
    return res;
}