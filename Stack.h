#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
private:
    struct Node_ {
        Node_* next;
        T data;
        Node_(Node_* next, const T& data) : next(next), data(data) {}
        Node_(Node_* next, T&& data) : next(next), data(std::move(data)) {}
    };

    size_t size_;
    Node_* top_;

public:
    Stack() : size_(0), top_(nullptr) {}
    ~Stack() { Clear(); }
    void Push(const T& data) {
        top_ = new Node_(top_, data);
        ++size_;
    }
    void Push(T&& data) {
        top_ = new Node_(top_, std::move(data));
        ++size_;
    }
    T Pop() {
        if (Empty()) {
            throw std::out_of_range("Cannot pop from empty stack");
        }
        Node_* to_delete = top_;
        T result = std::move(top_->data);
        top_ = top_->next;
        delete to_delete;
        --size_;
        return result;
    }
    T& Top() {
        if (Empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top_->data;
    }
    const T& Top() const {
        if (Empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top_->data;
    }
    size_t Size() const { return size_; }
    bool Empty() const { return top_ == nullptr; }
    void Clear() {
        while (top_ != nullptr) {
            Node_* buffer = top_;
            top_ = top_->next;
            delete buffer;
        }
        size_ = 0;
    }
};

