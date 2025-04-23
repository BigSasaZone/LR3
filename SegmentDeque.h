#pragma once
#include <cstddef>
#include <stdexcept>
#include "dynamic_array.h"

template <typename T, size_t SegmentSize = 64>
class SegmentDeque {
private:
    DynamicArray<DynamicArray<T>> segments_;
    size_t front_offset_;
    size_t size_;
private:
    void Shift(size_t index);
    template <class Comparator>
    void Sort(const Comparator& compare, size_t begin, size_t end);
public:
    SegmentDeque();
    SegmentDeque(size_t all_size);
    SegmentDeque(const SegmentDeque& other) = default;
    ~SegmentDeque() = default;
    SegmentDeque<T,SegmentSize>& operator=(const SegmentDeque& other) = default;
    const T& operator[](size_t index) const;
    T& operator[](size_t index);
    SegmentDeque<T,SegmentSize>& operator=( SegmentDeque&& other) = default;
    void PushBack(const T& value);
    void PushFront(const T& value);
    size_t GetSize();
    void InsertAt(const T& value, size_t index);
    template <class Comparator>
    void Sort(const Comparator& compare);
    template <class Unary>
    SegmentDeque<T, SegmentSize> Map(const Unary& unary) const;
    template <class Predicate>
    SegmentDeque<T, SegmentSize> Where(const Predicate& predicate) const;
    SegmentDeque<T, SegmentSize> TakeDeque(size_t begin, size_t end) const;
    SegmentDeque<T, SegmentSize> Concat(const SegmentDeque& deque) const;
};

template <typename T, size_t SegmentSize>
size_t SegmentDeque<T, SegmentSize>::GetSize(){
    return size_;
}

template <typename T, size_t SegmentSize>
SegmentDeque<T, SegmentSize>::SegmentDeque(): front_offset_(0), size_(0) {}

template <typename T, size_t SegmentSize>
SegmentDeque<T, SegmentSize>::SegmentDeque(size_t all_size) : front_offset_(0), size_(all_size) {
    if (all_size == 0){
        return;
    }
    size_t count_of_segment = (all_size + SegmentSize - 1) / SegmentSize;
    for (size_t i = 0; i < count_of_segment; ++i) {
        segments_.Append(DynamicArray<T>(SegmentSize));
    }
    for (size_t i = 0; i < size_; ++i) {
        (*this)[i] = T();
    }
}

template <typename T, size_t SegmentSize>
void SegmentDeque<T, SegmentSize>::PushBack(const T& value) {
    if (front_offset_ + size_ == SegmentSize * segments_.GetLenght()) {
        segments_.Append(DynamicArray<T>(SegmentSize));
    }
    ++size_;
    (*this)[size_ - 1] = value;
}

template <typename T, size_t SegmentSize>
void SegmentDeque<T, SegmentSize>::PushFront(const T& value) {
    if (front_offset_ == 0) {
        segments_.Prepend(DynamicArray<T>(SegmentSize));
        front_offset_ = SegmentSize;
    }
    --front_offset_;
    ++size_;
    (*this)[0] = value;
}

template <typename T, size_t SegmentSize>
void SegmentDeque<T, SegmentSize>::Shift(size_t index) {
    PushBack(T());
    for(size_t i = size_ - 1; i > index; --i){
        (*this)[i] = (*this)[i - 1];
    }
}

template <typename T, size_t SegmentSize>
void SegmentDeque<T, SegmentSize>::InsertAt(const T& value, size_t index) {
    if (index > size_) {
        throw std::out_of_range("Index out of range");
    }
    if (index == size_) {
        PushBack(value);
        return;
    }
    Shift(index);
    (*this)[index] = value;
}

template <typename T, size_t SegmentSize>
T& SegmentDeque<T, SegmentSize>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    const size_t adjusted_index = index + front_offset_;
    const size_t num_of_segment = adjusted_index / SegmentSize;
    const size_t pos_in_segment = adjusted_index % SegmentSize;
    return segments_[num_of_segment][pos_in_segment];
}

template <typename T, size_t SegmentSize>
const T& SegmentDeque<T, SegmentSize>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    const size_t adjusted_index = index + front_offset_;
    const size_t num_of_segment = adjusted_index / SegmentSize;
    const size_t pos_in_segment = adjusted_index % SegmentSize;
    return segments_[num_of_segment][pos_in_segment];
}

template <typename T, size_t SegmentSize>
template <class Comparator>
void SegmentDeque<T, SegmentSize>::Sort(const Comparator& compare, size_t begin, size_t end) {
    if (begin >= end) return;

    size_t pivot_idx = begin + (end - begin) / 2;
    T pivot = (*this)[pivot_idx];
    size_t left = begin;
    size_t right = end;

    while (left <= right) {
        while (compare((*this)[left], pivot)) ++left;
        while (compare(pivot, (*this)[right])) --right;

        if (left <= right) {
            std::swap((*this)[left], (*this)[right]);
            ++left;
            --right;
        }
    }

    Sort(compare, begin, right);
    Sort(compare, left, end);
}
template <typename T, size_t SegmentSize>
template <class Comparator>
void SegmentDeque<T, SegmentSize>::Sort(const Comparator& compare){
    if(size_ == 0){
        return;
    }
    Sort(compare, 0, size_ - 1);
}

template <typename T, size_t SegmentSize>
template <class Unary>
SegmentDeque<T, SegmentSize> SegmentDeque<T, SegmentSize>::Map(const Unary& unary) const {
    SegmentDeque<T, SegmentSize> copy_deque;
    for (size_t i = 0; i < size_; ++i) {
        T transformed_value = unary((*this)[i]);
        copy_deque.PushBack(transformed_value);
    }
    return copy_deque;
}

template <typename T, size_t SegmentSize>
template <class Predicate>
SegmentDeque<T, SegmentSize> SegmentDeque<T, SegmentSize>::Where(const Predicate& predicate) const {
    SegmentDeque<T, SegmentSize> filtered_deque;
    for (size_t i = 0; i < size_; ++i) {
        if (predicate((*this)[i])) {
            filtered_deque.PushBack((*this)[i]);
        }
    }
    return filtered_deque;
}

template <typename T, size_t SegmentSize>
SegmentDeque<T, SegmentSize> SegmentDeque<T, SegmentSize>::TakeDeque(size_t begin, size_t end) const {
    if (begin >= size_ || end > size_ + 1 || begin > end) {
        throw std::out_of_range("Invalid range: [begin, end] is out of bounds or begin > end");
    }
    SegmentDeque<T, SegmentSize> sub_deque;
    for (size_t i = begin; i <= end; ++i) {
        sub_deque.PushBack((*this)[i]);
    }
    return sub_deque;
}

template <typename T, size_t SegmentSize>
SegmentDeque<T, SegmentSize> SegmentDeque<T, SegmentSize>::Concat(const SegmentDeque& deque) const {
    SegmentDeque concat_deque;
    for (size_t i = 0; i < size_; ++i) {
        concat_deque.PushBack((*this)[i]);
    }
    for (size_t i = 0; i < deque.size_; ++i) {
        concat_deque.PushBack(deque[i]);
    }
    return concat_deque;
}


