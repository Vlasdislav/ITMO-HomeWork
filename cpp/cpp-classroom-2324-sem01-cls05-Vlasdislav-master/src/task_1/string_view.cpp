#include "string_view.hpp"

StringView::StringView() : str_(nullptr), size_(0) {}
StringView::StringView(const char *str, size_t size) : str_(const_cast<char*>(str)), size_(size) {}
StringView::StringView(const char *str) : str_(const_cast<char*>(str)), size_(strlen(str)) {}
StringView::StringView(const std::string& str) : str_(const_cast<char*>(str.data())), size_(str.size()) {}
StringView::StringView(const StringView& other) : str_(other.str_), size_(other.size_) {}

StringView &StringView::operator=(const StringView& other) {
    str_ = other.str_;
    size_ = other.size_;
    return *this;
}

StringView &StringView::operator=(const char* other) {
    str_ = const_cast<char*>(other);
    size_ = strlen(other);
    return *this;
}

StringView &StringView::operator=(const std::string& other) {
    str_ = const_cast<char*>(other.data());
    size_ = other.size();
    return *this;
}

const char* StringView::data() const {
    return str_;
}

size_t StringView::size() const {
    return size_;
}

StringView StringView::substr(size_t begin, size_t end) const {
    if (begin > end) {
        end = std::max(end, size_);
        begin = std::min(begin, size_);
        return StringView(str_ + begin, 0);
    } else {
        begin = std::min(begin, size_);
        end = std::min(end, size_);
        return StringView(str_ + begin, end - begin);
    }
}

const char& StringView::operator[](size_t index) const {
    return str_[index];
}

size_t StringView::find(const char c) const {
    const char* result = std::find(str_, str_ + size_, c);
	return result != str_ + size_ ? result - str_ : npos;
}

size_t StringView::find(const StringView sub) const {
    if (size_ == 0 && sub.size_ == 0) {
        return 0;
    }
    const char* res = std::search(str_, str_ + size_, sub.str_, sub.str_ + sub.size_);
	return res != str_ + size_ ? res - str_ : npos;
}

size_t StringView::findFirstOf(const StringView& chars, size_t start) const {
    if (start >= size_) {
        return npos;
    }
    for (size_t i = start; i < size_; ++i) {
        if (chars.find(str_[i]) != npos) {
            return i;
        }
    }
    return npos;
}

size_t StringView::findFirstOf(const char ch, size_t start) const {
    return findFirstOf(StringView(&ch, 1), start);
}

bool StringView::startsWith(StringView sub) const {
    if (size_ < sub.size_) {
        return false;
    }
    for (size_t i = 0; i < sub.size_; ++i) {
        if (str_[i] != sub.str_[i]) {
            return false;
        }
    }
    return true;
}

bool StringView::startsWith(const char c) const {
    return size_ > 0 && str_[0] == c;
}

bool StringView::endsWith(StringView sub) const {
    if (size_ < sub.size_) {
        return false;
    }
    size_t start = size_ - sub.size_;
    for (size_t i = 0; i < sub.size_; ++i) {
        if (str_[start + i] != sub.str_[i]) {
            return false;
        }
    }
    return true;
}

bool StringView::endsWith(const char c) const {
    return size_ > 0 && str_[size_ - 1] == c;
}

size_t StringView::findFirstNotOf(StringView sub, size_t begin) const {
    if (begin >= size_) {
        return npos;
    }
    for (size_t i = begin; i < size_; ++i) {
        if (sub.find(str_[i]) == npos) {
            return i;
        }
    }
    return npos;
}

size_t StringView::findFirstNotOf(const char c, size_t begin) const {
    return findFirstNotOf(StringView(&c, 1), begin);
}

void StringView::removePrefix(size_t to) {
    if (to < size_) {
        str_ += to;
        size_ -= to;
    } else {
        str_ = nullptr;
        size_ = 0;
    }
}