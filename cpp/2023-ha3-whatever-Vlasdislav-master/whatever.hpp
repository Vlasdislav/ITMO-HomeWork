// whatever.hpp - header-only solution goes into this file.

#pragma once

#include <typeinfo>
#include <algorithm>

namespace utils {
    struct Interface {
        virtual ~Interface() = default;
        virtual Interface* clone() const = 0;
        virtual const std::type_info& type() const = 0;
    };
    template<typename T>
    struct Impl : Interface {
        T value;
        explicit Impl(const T& value) : value(value) {}
        Interface* clone() const override {
            return new Impl(value);
        }
        const std::type_info& type() const override {
            return typeid(T);
        }
    };
    class whatever {
        public:
            whatever() : value(nullptr) {}
            whatever(whatever &other) : value(other.value ? other.value->clone() : nullptr) {}
            whatever(const whatever &other) : value(other.value ? other.value->clone() : nullptr) {}
            template <typename T>
            whatever(const T& value) : value(new Impl<std::decay_t<const T&>>(value)) {}
            template <typename T>
            whatever(T& value) : value(new Impl<std::decay_t<T&>>(value)) {}
            ~whatever() {
                clear();
            }
            whatever& operator=(const whatever& other) {
                if (this != &other) {
                    clear();
                    value = other.value ? other.value->clone() : nullptr;
                }
                return *this;
            }
            template<typename T>
            whatever& operator=(T& other) {
                whatever tmp(other);
                std::swap(tmp.value, this->value);
                return *this;
            }
            bool empty() const {
                return value == nullptr;
            }
            void clear() {
                delete value;
                value = nullptr;
            }
        public:
            Interface* value;
    };
    void swap(whatever& lhs, whatever& rhs) {
        std::swap(lhs.value, rhs.value);
    }
    struct bad_whatever_cast : public std::bad_cast {
        const char* what() const noexcept override {
            return "bad whatever cast";
        }
    };
    template<typename T>
    T whatever_cast(const whatever& w) {
        using ValueType = typename std::remove_const<typename std::remove_reference<T>::type>::type;

        const Impl<ValueType>* implPtr = dynamic_cast<const Impl<ValueType>*>(w.value);
        if (implPtr) {
            return implPtr->value;
        }
        throw bad_whatever_cast();
    }
    template<typename T>
    T whatever_cast(whatever& w) {
        using ValueType = typename std::remove_const<typename std::remove_reference<T>::type>::type;

        Impl<ValueType>* implPtr = dynamic_cast<Impl<ValueType>*>(w.value);
        if (implPtr) {
            return implPtr->value;
        }
        throw bad_whatever_cast();
    }
    template<typename T>
    const T* whatever_cast(const whatever* ptr) {
        if (ptr == nullptr) {
            return nullptr;
        }
        using ValueType = typename std::remove_const<typename std::remove_reference<T>::type>::type;

        const Impl<ValueType>* implPtr = dynamic_cast<const Impl<ValueType>*>(ptr->value);
        if (implPtr) {
            return &implPtr->value;
        }
        return nullptr;
    }
    template<typename T>
    T* whatever_cast(whatever* ptr) {
        if (ptr == nullptr) {
            return nullptr;
        }
        using ValueType = typename std::remove_const<typename std::remove_reference<T>::type>::type;

        Impl<ValueType>* implPtr = dynamic_cast<Impl<ValueType>*>(ptr->value);
        if (implPtr) {
            return &implPtr->value;
        }
        return nullptr;
    }
}
