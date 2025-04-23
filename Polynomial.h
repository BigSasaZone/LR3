#pragma once
#include "RedBlackTree.h"

template<typename T>
class Polynom {
private:
    struct data_ {
        size_t power;
        mutable T k;
        bool operator<(const data_& other) const;
    };
    Set<data_> set_;
public:
    Polynom() = default;
    Polynom(const Set<data_>& set);
    Polynom(size_t power, const T& coeff);
    Polynom(const Polynom& other) = default;
    Polynom(Polynom&& other) = default;
    Polynom<T>& operator=(const Polynom& other) = default;
    Polynom<T>& operator=(Polynom&& other) = default;
    ~Polynom() = default;
    Polynom<T>& operator+=(const Polynom& other);
    Polynom<T> operator+(const Polynom& other) const;
    Polynom<T>& operator*=(const Polynom& other);
    Polynom<T> operator*(const Polynom& other) const;
    Polynom<T> ProdScalar(const T& value) const;
    Polynom<T>& operator-=(const Polynom& other);
    Polynom<T> operator-(const Polynom& other) const;
    T ValueInPoint(const T& point) const;
    Polynom<T> SuperPosition(const Polynom& other) const;
    static Polynom<T> Power(const Polynom<T>& base, size_t exp);
    Set<data_> GetSet() const { return set_; }
};

template <typename T>
bool Polynom<T>::data_::operator<(const data_& other) const {
    return other.power < power;
}

template <typename T>
Polynom<T>::Polynom(const Set<data_>& set) {
    for (const auto& term : set.GoForward()) {
        if (term.k != T(0)) {
            set_.Insert({term.power, term.k});
        }
    }
}

template <typename T>
Polynom<T>::Polynom(size_t power, const T& coeff) {
    if (coeff != T(0)) {
        set_.Insert({power, coeff});
    }
}

template<typename T>
Polynom<T>& Polynom<T>::operator+=(const Polynom& other) {
    auto terms = other.set_.GoForward();
    for (size_t i = 0; i < terms.GetLenght(); ++i) {
        data_ elem = terms[i];
        auto iter_find = set_.Find(elem);
        if (iter_find != set_.end()) {
            iter_find->k += elem.k;
        } else {
            set_.Insert(elem);
        }
    }
    return *this;
}

template<typename T>
Polynom<T> Polynom<T>::operator+(const Polynom& other) const {
    Polynom result(*this);
    result += other;
    return result;
}

template<typename T>
Polynom<T>& Polynom<T>::operator*=(const Polynom& other) {
    Polynom<T> prod;
    auto terms1 = set_.GoForward();
    auto terms2 = other.set_.GoForward();
    for (size_t i = 0; i < terms1.GetLenght(); ++i) {
        for (size_t j = 0; j < terms2.GetLenght(); ++j) {
            size_t new_power = terms1[i].power + terms2[j].power;
            T new_k = terms1[i].k * terms2[j].k;
            data_ key{new_power, T()};
            auto existing = prod.set_.Find(key);
            if (existing != prod.set_.end()) {
                existing->k += new_k;
            } else {
                prod.set_.Insert({new_power, new_k});
            }
        }
    }
    *this = prod;
    return *this;
}

template<typename T>
Polynom<T> Polynom<T>::operator*(const Polynom& other) const {
    Polynom result(*this);
    result *= other;
    return result;
}

template<typename T>
Polynom<T> Polynom<T>::ProdScalar(const T& value) const {
    Polynom<T> result;
    if (set_.Size() == 0) {
        if (value != T(0)) {
            result.set_.Insert({0, value});
        }
    } else {
        auto terms = set_.GoForward();
        for (size_t i = 0; i < terms.GetLenght(); ++i) {
            T new_k = terms[i].k * value;
            if (new_k != T(0)) {
                result.set_.Insert({terms[i].power, new_k});
            }
        }
    }
    return result;
}

template<typename T>
Polynom<T>& Polynom<T>::operator-=(const Polynom& other) {
    Polynom<T> buffer = other;
    buffer = buffer.ProdScalar(T(-1));
    *this += buffer;
    return *this;
}

template<typename T>
Polynom<T> Polynom<T>::operator-(const Polynom& other) const {
    Polynom result(*this);
    result -= other;
    return result;
}

template<typename T>
Polynom<T> Polynom<T>::Power(const Polynom<T>& base, size_t exponent) {
    if (exponent == 0) {
        Polynom<T> one;
        one.set_.Insert({0, T(1)});
        return one;
    }
    Polynom<T> result = Power(base, exponent / 2);
    result *= result;
    if (exponent % 2 == 1) {
        result *= base;
    }
    return result;
}

template<typename T>
T Polynom<T>::ValueInPoint(const T& point) const {
    T value = T(0);
    auto terms = set_.GoForward();
    for (size_t i = 0; i < terms.GetLenght(); ++i) {
        T term_value = terms[i].k;
        if (terms[i].power > 0) {
            term_value *= static_cast<T>(std::pow(point, terms[i].power));
        }
        value += term_value;
    }
    return value;
}

template<typename T>
Polynom<T> Polynom<T>::SuperPosition(const Polynom& other) const {
    Polynom<T> result;
    auto terms = set_.GoForward();
    for (size_t i = 0; i < terms.GetLenght(); ++i) {
        Polynom<T> powered = Power(other, terms[i].power);
        result += powered.ProdScalar(terms[i].k);
    }
    return result;
}
