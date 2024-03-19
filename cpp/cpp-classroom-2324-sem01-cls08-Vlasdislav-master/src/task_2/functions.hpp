#pragma once

namespace cls08 {
    template<typename ForwardIterator, typename T>
    void fill(ForwardIterator begin, ForwardIterator end, const T& value) {
        for (auto it = begin; it != end; ++it) {
            *it = value;
        }
    }
    template<typename ForwardIterator, typename F>
    void generate(ForwardIterator begin, ForwardIterator end, F f) {
        for (auto it = begin; it != end; ++it) {
            *it = f();
        }
    }
    template<typename ForwardIterator, typename Iterator>
    void copy(ForwardIterator begin, ForwardIterator end, Iterator begin_) {
        for (; begin != end;) {
            *(begin_++) = *begin++;
        }
    }
    template<typename ForwardIterator, typename F>
    void for_each(ForwardIterator begin, ForwardIterator end, F f) {
        for (auto it = begin; it != end; ++it) {
            f(*it);
        }
    }
}