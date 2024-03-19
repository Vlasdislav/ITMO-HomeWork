#include "fizzbuzz.hpp"
#include <iostream>

void fizzbuzz(uint8_t n) {
    for (size_t i = 1; i <= static_cast<size_t>(n); ++i) {
        bool flag = true;
        if (i % 3 == 0) {
            std::cout << "Fizz";
            flag = false;
        }
        if (i % 5 == 0) {
            std::cout << "Buzz";
            flag = false;
        }
        if (flag) {
            std::cout << i;
        }
        std::cout << std::endl;
    }
}