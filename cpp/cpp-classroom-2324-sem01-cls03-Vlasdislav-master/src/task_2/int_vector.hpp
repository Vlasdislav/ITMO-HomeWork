#pragma once

#include <cstddef>

struct IntVector {
    int* data;
    size_t size;
    size_t capacity_;
    IntVector();
};

void pushBack(IntVector& v, int value);
void popBack(IntVector& v);
void deallocate(IntVector& v);
