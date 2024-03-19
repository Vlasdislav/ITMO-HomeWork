#pragma once

#include <deque>
#include <cstddef>
#include <algorithm>

namespace cls08 {
    template<typename Type, typename Comparator=std::less<Type>> struct priority_queue {
        public:
            priority_queue() = default;
            explicit priority_queue(const Comparator& compare) : comp(compare) {}
            priority_queue(std::deque<Type>& a) : q(a) {
                std::make_heap(q.begin(), q.end());
            }
            priority_queue(const priority_queue<Type>& other) : q(other.q) {}
            priority_queue<Type>& operator=(const priority_queue<Type>& other) {
                if (this != &other) {
                    q = other.q;
                }
                return *this;
            }
            ~priority_queue() = default;
            void push(const Type& x) {
                q.emplace_back(x);
                auto comparator = [this](const Type& lhs, const Type& rhs) {
                    return comp(lhs, rhs);
                };
                std::make_heap(q.begin(), q.end(), comparator);
            }
            void pop() {
                q.pop_front();
                auto comparator = [this](const Type& lhs, const Type& rhs) {
                    return comp(lhs, rhs);
                };
                std::make_heap(q.begin(), q.end(), comparator);
            }
            const Type& front() const {
                return q.front();
            }
            size_t size() const {
                return q.size();
            }
        private:
            std::deque<Type> q;
            Comparator comp;
    };
}

