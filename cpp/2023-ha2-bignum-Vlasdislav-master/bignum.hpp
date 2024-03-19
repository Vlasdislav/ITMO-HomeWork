// bignum.hpp - header-only solution goes into this file.
#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <regex>

namespace mp {
    class bignum {
        private:
            std::vector<uint32_t> num_;
        public:
            bignum();
            bignum(uint32_t);
            explicit bignum(std::string);
            bignum(const bignum&);
            bignum& operator=(const bignum&);
            explicit operator uint32_t() const;
            operator bool() const;
            std::string to_string() const;
            bignum operator+(const bignum&) const;
            bignum operator*(const bignum&) const;
            bignum& operator+=(const bignum&);
            bignum& operator*=(const bignum&);
            std::pair<mp::bignum, uint32_t> div_mod(uint32_t);
    };
    class polynomial {
        private:
            std::vector<uint32_t> poly_;
        public:
            polynomial(std::string);
            uint32_t at(uint32_t) const;
            uint32_t& at(uint32_t);
            template<typename T>
            T operator()(T) const;
    };
}

inline mp::bignum::bignum() : num_(std::vector<uint32_t>(1)) {}

inline mp::bignum::bignum(uint32_t val) {
    num_.emplace_back(val);
}

inline mp::bignum::bignum(std::string str) {
    bignum cur(str[0] - '0');
    for (size_t i = 1; i < str.size(); ++i) {
        cur *= 10;
        cur += str[i] - '0';
    }
    std::swap(this->num_, cur.num_);
}

inline mp::bignum::bignum(const mp::bignum& other) : num_(other.num_) {}

inline mp::bignum& mp::bignum::operator=(const mp::bignum& other) {
    if (this != &other) {
        num_ = other.num_;
    }
    return *this;
}

inline mp::bignum::operator uint32_t() const {
    return num_[0];
}

inline mp::bignum::operator bool() const {
    return !(num_.size() == 1 && num_[0] == 0);
}

inline std::pair<mp::bignum, uint32_t> mp::bignum::div_mod(uint32_t mod) {
    mp::bignum quotient(*this);
    uint64_t remainder = 0;
    for (int i = quotient.num_.size() - 1; i >= 0; --i) {
        uint64_t cur = quotient.num_[i] + (static_cast<uint64_t>(remainder) << 32);
        quotient.num_[i] = cur / mod;
        remainder = cur % mod;
    }
    while (quotient.num_.size() > 1 && quotient.num_.back() == 0) {
        quotient.num_.pop_back();
    }
    return { quotient, remainder };
}

inline std::string mp::bignum::to_string() const {
    std::string res;
    mp::bignum num_cpy = *this;
    do {
        std::pair<mp::bignum, uint32_t> div_res = num_cpy.div_mod(10);
        num_cpy = div_res.first;
        res = std::to_string(div_res.second) + res;
    } while (num_cpy);
    return res;
}

inline std::ostream& operator<<(std::ostream& out, const mp::bignum& num) {
    out << num.to_string();
    return out;
}
inline std::istream& operator>>(std::istream& in, mp::bignum& num) {
    std::string str;
    in >> str;
    num = mp::bignum(str);
    return in;
}
inline mp::bignum mp::bignum::operator+(const bignum &other) const {
    mp::bignum new_num = *this;
    new_num += other;
    return new_num;
}
inline mp::bignum mp::bignum::operator*(const bignum& other) const {
    mp::bignum new_num = *this;
    new_num *= other;
    return new_num;
}

inline mp::bignum& mp::bignum::operator+=(const bignum& other) {
    size_t n = num_.size();
    size_t m = other.num_.size();
    uint32_t remains = 0;
    size_t len = std::min(n, m);
    num_.resize(std::max(n, m));
    for (size_t i = 0; i < len; ++i) {
        uint64_t sum = remains * 1ull + num_[i] + other.num_[i];
        num_[i] = sum;
        sum >>= 32;
        remains = sum;
    }
    for (size_t i = len; i < n; ++i) {
        uint64_t sum = remains * 1ull + num_[i];
        num_[i] = sum;
        sum >>= 32;
        remains = sum;
    }
    for (size_t i = len; i < m; ++i) {
        uint64_t sum = remains * 1ull + other.num_[i];
        num_[i] = sum;
        sum >>= 32;
        remains = sum;
    }
    if (remains) {
        num_.emplace_back(remains);
    }
    return *this;
}

inline mp::bignum &mp::bignum::operator*=(const bignum& other) {
    size_t n = num_.size();
    size_t m = other.num_.size();
    std::vector<uint32_t> res(n + m);
    for (size_t i = 0; i < n; ++i) {
        int64_t remains = 0;
        for (size_t j = 0; j < m || remains != 0; ++j) {
            __int128_t prod = (i + j < res.size() ? num_[i] * 1ull * (j < m ? other.num_[j] : 0) : 0);
            __int128_t sum = res[i + j] + prod + remains;
            res[i + j] = sum;
            sum >>= 32;
            remains = sum;
        }
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    num_ = res;
    return *this;
}

inline mp::polynomial::polynomial(std::string input) {
    std::regex pattern("(-?\\d*)\\*?x\\^(\\d+)");
    std::smatch matches;
    auto it = input.cbegin();
    while (std::regex_search(it, input.cend(), matches, pattern)) {
        std::string coefficient = matches[1].str();
        if (coefficient.empty()) {
            coefficient = "1";
        }
        uint32_t deg = std::stoll(matches[2]);
        uint32_t coef = std::stoll(coefficient);
        if (poly_.size() <= deg) {
            poly_.resize(deg + 1);
        }
        poly_[deg] = coef;
        it = matches.suffix().first;
    }
}

inline uint32_t mp::polynomial::at(uint32_t ind) const {
    return poly_[ind];
}

inline uint32_t &mp::polynomial::at(uint32_t ind) {
     if (poly_.size() <= ind) {
        poly_.resize(ind + 1);
    }
    return poly_[ind];
}

template <typename T>
inline T mp::polynomial::operator()(T x) const {
    T res = 0;
    for (size_t i = poly_.size() - 1; i > 0; --i) {
        res = static_cast<T>(poly_[i]) + res * x;
    }
    return static_cast<T>(poly_[0]) + res * x;
}