#include "shared_buffer.hpp"

SharedBuffer::SharedBuffer() : data_(new char[1]{}), size_(0), use_count(new size_t(1)) {}

SharedBuffer::SharedBuffer(const size_t size) : data_(new char[size + 1]{}), size_(size), use_count(new size_t(1)) {}

SharedBuffer::SharedBuffer(const SharedBuffer& other) : data_(other.data_), size_(other.size_), use_count(other.use_count) {
    ++(*use_count);
}

SharedBuffer::~SharedBuffer() {
    if (--(*use_count) == 0) {
        delete[] data_;
        delete use_count;
    }
}

SharedBuffer &SharedBuffer::operator=(const SharedBuffer& other) {
    if (this != &other) {
        if (--(*use_count) == 0) {
            delete[] data_;
            delete use_count;
        }
        data_ = other.data_;
        size_ = other.size_;
        use_count = other.use_count;
        ++(*use_count);
    }
    return *this;
}

size_t SharedBuffer::getSize() const {
    return size_;
}

char *SharedBuffer::getData() const {
    return data_;
}

size_t SharedBuffer::useCount() const {
    return *use_count;
}