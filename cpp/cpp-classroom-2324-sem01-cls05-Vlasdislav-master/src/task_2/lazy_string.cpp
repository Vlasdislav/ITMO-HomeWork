#include <stdexcept>

#include "lazy_string.hpp"

LazyString::LazyString() : data_() {}

LazyString::LazyString(char const* str) : data_(strlen(str)) {
    for (size_t i = 0; i < data_.getSize(); ++i) {
        data_.getData()[i] = str[i];
    }
}

LazyString::LazyString(const LazyString& other) : data_(other.data_) {}

LazyString &LazyString::operator=(const LazyString other) {
    if (this != &other) {
        data_ = other.data_;
    }
    return *this;
}

size_t LazyString::getSize() const {
    return data_.getSize();
}

char* LazyString::cStr() const {
    return data_.getData();
}

size_t LazyString::useCount() const {
    return data_.useCount();
}

char LazyString::at(const size_t index) const {
    if (index >= data_.getSize() || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data_.getData()[index];
}

bool LazyString::operator==(const LazyString& other) const {
    return data_.getSize() == other.getSize() && data_.getData() == other.cStr();
}

LazyString& LazyString::operator+=(const LazyString& other) {
    SharedBuffer newBuffer(getSize() + other.getSize());
    std::memcpy(newBuffer.getData(), cStr(), getSize());
    std::memcpy(newBuffer.getData() + getSize(), other.cStr(), other.getSize());
    data_ = newBuffer;
    return *this;
}

LazyString::CharWrapper LazyString::operator[](const size_t index) {
    return CharWrapper(this, index);
}

LazyString operator+(const LazyString& lhs, const LazyString& rhs) {
    SharedBuffer newBuffer(lhs.getSize() + rhs.getSize());
    std::memcpy(newBuffer.getData(), lhs.cStr(), lhs.getSize());
    std::memcpy(newBuffer.getData() + lhs.getSize(), rhs.cStr(), rhs.getSize());
    return LazyString(newBuffer.getData());
}

LazyString::CharWrapper::CharWrapper(LazyString* str, size_t index) : str_(str), index_(index) {}

LazyString::CharWrapper::operator char() const {
    return str_->at(index_);
}

LazyString::CharWrapper& LazyString::CharWrapper::operator=(const CharWrapper& other) {
    if (str_->useCount() > 1) {
        LazyString buff(str_->cStr());
        std::swap(buff.data_, str_->data_);
        str_->cStr()[index_] = other.str_->cStr()[index_];
    } else {
        str_->cStr()[index_] = other.str_->cStr()[index_];
    }
    return *this;
}

LazyString::CharWrapper &LazyString::CharWrapper::operator=(const char c) {
    if (str_->useCount() > 1) {
        LazyString buff(str_->cStr());
        std::swap(buff.data_, str_->data_);
        str_->cStr()[index_] = c;
    } else {
        str_->cStr()[index_] = c;
    }
    return *this;
}

LazyString::CharWrapper& LazyString::CharWrapper::operator++() {
    if (str_->useCount() > 1) {
        LazyString buff(str_->cStr());
        std::swap(buff.data_, str_->data_);
    }
    ++str_->cStr()[index_];
    return *this;
}

char LazyString::CharWrapper::operator++(int) {
    // if (str_->useCount() > 1) {
    //     LazyString buff(str_->cStr());
    //     std::swap(buff.data_, str_->data_);
    // }
    char tmp = str_->cStr()[index_];
    ++*this;
    return tmp;
}
