#pragma once
#include <cstddef>
#include "Stack.h"
#include <string>

class Ring{
private:
    std::string shape_;
    std::string colour_;
    const size_t order_;
public:
    Ring(const size_t order);
    const size_t GetOrder() const;
    std::string GetShape() const;
    std::string GetColour() const;
};

std::string Ring::GetShape() const{
    return shape_;
}

std::string Ring::GetColour() const{
    return colour_;
}

const size_t Ring::GetOrder() const{
    return order_;
}

Ring::Ring(const size_t order) :order_(order) {}

inline void Tower(const size_t n, Stack<Ring>& from, Stack<Ring>& to, Stack<Ring>& help) {
    if (n == 0) {
        return;
    }
    Tower(n - 1, from, help, to);
    to.Push(from.Pop());
    Tower(n - 1, help, to, from);
}


