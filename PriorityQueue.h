#pragma once
#include <cstddef>
#include "dynamic_array.h"
#include <functional>

template <typename T, class Comparator = std::less<T>>
class PriorityQueue{
private:
    DynamicArray<T> data_;
    Comparator compare_;
private:
    void SiftUp(size_t index);
    void SiftDown(size_t index);
public:
    PriorityQueue(Comparator compare = Comparator());
    T Top() const;
    void Push(const T& value);
    void Pop();
    size_t Size() const;
    bool IsEmpty() const;
    PriorityQueue(const DynamicArray<T>& array);
    PriorityQueue<T, Comparator> Concat(const PriorityQueue<T>& queue1)const;
    template<class Unary>
    PriorityQueue<T, Comparator> Map(const Unary& unary) const;
    template<class Predicate>
    PriorityQueue<T, Comparator> Where(const Predicate& predicate) const;
};

template <typename T, class Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(Comparator compare):compare_(compare){}

template <typename T, class Comparator>
void PriorityQueue<T, Comparator>::SiftUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (compare_(data_[parent], data_[index])) {
            std::swap(data_[parent], data_[index]);
            index = parent;
        } else {
            break;
        }
    }
}

template <typename T, class Comparator>
void PriorityQueue<T, Comparator>::SiftDown(size_t index){
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    if(left >= data_.GetLenght()){
        return;
    }
    size_t best_index = index;
    if(compare_(data_[best_index], data_[left])){
        best_index = left;
    }
    if(right < data_.GetLenght()){
        if(compare_(data_[best_index], data_[right])){
            best_index = right;
        }
    }
    if(best_index == index){
        return;
    }
    std::swap(data_[index], data_[best_index]);
    SiftDown(best_index);
}

template <typename T,class Comparator>
T PriorityQueue<T, Comparator>::Top() const{
    return data_.GetFirst();
}

template <typename T, class Comparator>
void PriorityQueue<T, Comparator>::Push(const T& value){
    data_.Append(value);
    SiftUp(data_.GetLenght() - 1);
}

template <typename T, class Comparator>
void PriorityQueue<T, Comparator>::Pop(){
    std::swap(data_.GetFirst(),data_.GetLast());
    data_.PopBack();
    if((data_.IsEmpty())){
        return;
    }
    SiftDown(0);
}

template <typename T, class Comparator>
size_t PriorityQueue<T, Comparator>::Size() const{
    return data_.GetLenght();
}

template <typename T, class Comparator>
bool PriorityQueue<T, Comparator>::IsEmpty() const{
    return data_.GetLenght() == 0;
}

template <typename T, class Comparator>
PriorityQueue<T,Comparator>::PriorityQueue(const DynamicArray<T>& array):data_(array), compare_(Comparator()){
    size_t start_index = array.GetLenght()/2;
    for(size_t i = start_index; i > 0; --i){
        SiftDown(i - 1);
    }
}

template <typename T, class Comparator>
PriorityQueue<T, Comparator> PriorityQueue<T, Comparator>::Concat(const PriorityQueue<T>& queue) const {
    DynamicArray<T> data_array;
    for (size_t i = 0; i < data_.GetLenght(); ++i) {
        data_array.Append(data_[i]);
    }
    for (size_t i = 0; i < queue.data_.GetLenght(); ++i) {
        data_array.Append(queue.data_[i]);
    }
    PriorityQueue concat_queue(data_array);
    return concat_queue;
}
    
template <typename T, class Comparator>
template <class Unary>
PriorityQueue<T, Comparator> PriorityQueue<T, Comparator>::Map(const Unary& unary) const {
    DynamicArray<T> map_data;
    for(size_t i = 0; i < data_.GetLenght(); ++i) {
        map_data.Append(data_[i]);
        unary(map_data.GetLast());
    }
    PriorityQueue map_queue(map_data);
    return map_queue;
}
template <typename T, class Comparator>
template <class Predicate>
PriorityQueue<T, Comparator> PriorityQueue<T, Comparator>::Where(const Predicate& predicate) const {
    DynamicArray<T> filtered_data;
    for (size_t i = 0; i < data_.GetLenght(); ++i) {
        if (predicate(data_[i])) {
            filtered_data.Append(data_[i]);
        }
    }

    PriorityQueue filtered_queue(filtered_data);
    return filtered_queue;
}

