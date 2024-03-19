#pragma once

#include "shared_buffer.hpp"

class LazyString {
    private:
        class CharWrapper {
            public:
                CharWrapper(LazyString*, size_t);
                operator char() const;
                CharWrapper& operator=(const CharWrapper&);
                CharWrapper& operator=(const char);
                CharWrapper& operator++();
                char operator++(int);
            private:
                LazyString* str_;
                size_t index_;
        };
    public:
        LazyString();
        LazyString(char const*);
        LazyString(const LazyString&);
        LazyString& operator=(const LazyString);
        size_t getSize() const;
        char* cStr() const;
        size_t useCount() const;
        char at(const size_t) const;
        bool operator==(const LazyString&) const;
        LazyString& operator+=(const LazyString&);
        CharWrapper operator[](const size_t);
    private:
        SharedBuffer data_;
};

LazyString operator+(const LazyString&, const LazyString&);