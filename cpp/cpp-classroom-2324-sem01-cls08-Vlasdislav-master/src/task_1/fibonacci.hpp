#pragma once

#include <cstddef>
#include <iostream>

namespace cls08 {
    template<size_t N>
    struct FibonacciNumber {
        static const size_t value = FibonacciNumber<N - 1>::value + FibonacciNumber<N - 2>::value;
    };
    template<>
    struct FibonacciNumber<0> {
        static const size_t value = 0;
    };
    template<>
    struct FibonacciNumber<1> {
        static const size_t value = 1;
    };
}