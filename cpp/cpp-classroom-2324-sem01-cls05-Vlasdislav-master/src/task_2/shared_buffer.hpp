#pragma once

#include <cstring>

class SharedBuffer {
    public:
        SharedBuffer();
        explicit SharedBuffer(const size_t);
        SharedBuffer(const SharedBuffer&);
        ~SharedBuffer();
        SharedBuffer& operator=(const SharedBuffer&);
        size_t getSize() const;
        char* getData() const;
        size_t useCount() const;
    private:
        char* data_;
        size_t size_;
        size_t* use_count;
};