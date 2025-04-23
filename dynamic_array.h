#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class DynamicArray {
 private:
  T* data_;
  size_t lenght_;
  size_t capacity_;

public:
    DynamicArray();
    DynamicArray(size_t lenght);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray(DynamicArray<T>&& other);
    ~DynamicArray();
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(DynamicArray<T>&& other);
    T& operator[](size_t index);
    T& Get(size_t index);
    T& GetLast();
    T& GetFirst();
    const T& operator[](size_t index) const;
    const T& Get(size_t index) const;
    const T& GetLast() const;
    const T& GetFirst() const;
    size_t GetLenght() const;
    size_t GetCapacity() const;
    bool IsEmpty() const;
    void Set(size_t index, const T& value);
    void ReSize(size_t new_size);
    void Reserve(size_t new_capacity);
    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, size_t index);
    template <class Predicate>
    DynamicArray<T> Where(const Predicate& predicate) const;
    template <class Unary>
    DynamicArray<T> Map(const Unary& unary) const;
    void PopBack();
};

template <typename T>
DynamicArray<T>::DynamicArray() : lenght_(0), data_(nullptr), capacity_(0) {
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t lenght) : lenght_(lenght), data_(new T[lenght]), capacity_(lenght) {
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : lenght_(other.lenght_), data_(new T[other.lenght_]), capacity_(other.capacity_) {
  for (size_t i = 0; i < lenght_; ++i) {
    data_[i] = other.data_[i];
  }
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other):lenght_(other.lenght_), capacity_(other.capacity_), data_(other.data_){
    other.data_ = nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  delete[] data_;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) {
        return *this;
    }
    DynamicArray<T> copy_other = other;
    std::swap(lenght_, copy_other.lenght_);
    std::swap(capacity_, copy_other.capacity_);
    std::swap(data_, copy_other.data_);
    return *this;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=( DynamicArray<T>&& other){
    delete [] data_;
    data_ = other.data_;
    lenght_ = other.lenght_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    return *this;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T& DynamicArray<T>::Get(size_t index) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T& DynamicArray<T>::GetLast() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[lenght_ - 1];
}

template <typename T>
T& DynamicArray<T>::GetFirst() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[0];
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
  }
    return data_[index];
}

template <typename T>
const T& DynamicArray<T>::Get(size_t index) const {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& DynamicArray<T>::GetLast() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[lenght_ - 1];
}

template <typename T>
const T& DynamicArray<T>::GetFirst() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[0];
}

template <typename T>
size_t DynamicArray<T>::GetLenght() const {
    return lenght_;
}

template <typename T>
void DynamicArray<T>::Set(size_t index, const T& value) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    data_[index] = value;
}

template <typename T>
size_t DynamicArray<T>::GetCapacity() const {
    return capacity_;
}

template <typename T>
bool DynamicArray<T>::IsEmpty() const {
    return lenght_ == 0;
}

template <typename T>
void DynamicArray<T>::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < lenght_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

template <typename T>
void DynamicArray<T>::ReSize(size_t new_size) {
  if (new_size > capacity_) {
    capacity_ = new_size;
    T* new_data = new T[capacity_];
    for (size_t i = 0; i < lenght_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }
    lenght_ = new_size;
}

template <typename T>
void DynamicArray<T>::Append(const T& item) {
  if (lenght_ == capacity_) {
    size_t new_capacity;
    if (capacity_ == 0) {
      new_capacity = 1;
    } else {
      new_capacity = capacity_ * 2;
    }
    Reserve(new_capacity);
  }
  data_[lenght_] = item;
  lenght_++;
}

template <typename T>
void DynamicArray<T>::Prepend(const T& item) {
    if (lenght_ == capacity_) {
        size_t new_capacity;
        if (capacity_ == 0) {
            new_capacity = 1;
    } else {
        new_capacity = capacity_ * 2;
        }
    Reserve(new_capacity);
    }
    for (size_t i = lenght_; i > 0; --i) {
        data_[i] = data_[i - 1];
    }
    data_[0] = item;
    lenght_++;
}

template <typename T>
void DynamicArray<T>::InsertAt(const T& item, size_t index) {
    if (index >= lenght_) {
    throw std::out_of_range("Index out of range");
    }
    if (lenght_ == capacity_) {
    size_t new_capacity;
    if (capacity_ == 0) {
      new_capacity = 1;
    } else {
      new_capacity = capacity_ * 2;
    }
    Reserve(new_capacity);
    }
    for (size_t i = lenght_; i > index; --i) {
    data_[i] = data_[i - 1];
    }
    data_[index] = item;
    lenght_++;
}

template <typename T>
template <class Predicate>
DynamicArray<T> DynamicArray<T>::Where(const Predicate& predicate) const {
    DynamicArray<T> copy_array;
    for (size_t i = 0; i < lenght_; ++i) {
    if (predicate(data_[i])) {
      copy_array.Append(data_[i]);
    }
    }
  return copy_array;
}

template <typename T>
template <class Unary>
DynamicArray<T> DynamicArray<T>::Map(const Unary& unary) const {
    DynamicArray<T> copy_array;
    for (size_t i = 0; i < lenght_; ++i) {
        copy_array.Append(data_[i]);
        unary(copy_array.GetLast());
    }
    return copy_array;
}

template <typename T>
void DynamicArray<T>::PopBack(){
    --lenght_;
}



