#include "int_vector.hpp"

IntVector::IntVector() : data(nullptr), size(0), capacity_(0) {}

inline void allocate(IntVector& v) {
    if (v.data == nullptr) {
        v.capacity_ = 1;
        v.data = new int[v.capacity_];
    }
}

void pushBack(IntVector& v, int value) {
    allocate(v);
    if (v.size < v.capacity_) {
        v.data[v.size++] = value;
    } else {
        v.capacity_ *= 2;
        int* data_copy = new int[v.capacity_];
        for (size_t i = 0; i < v.size; ++i) {
            data_copy[i] = v.data[i];
        }
        delete [] v.data;
        v.data = data_copy;
        pushBack(v, value);
    }
}

void popBack(IntVector& v) {
    allocate(v);
    v.size -= 1;
}

void deallocate(IntVector& v) {
    v.size = 0;
    v.capacity_ = 0;
    delete [] v.data;
    v.data = nullptr;
}