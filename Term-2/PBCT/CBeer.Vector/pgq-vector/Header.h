// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>

#ifndef INCLUDE_VECTOR_HEADER_HPP_
#define INCLUDE_VECTOR_HEADER_HPP_
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

template <class T>
class vector {
public:
    vector();
    vector(const vector<T>& vec);
    explicit vector(const size_t& size);
    ~vector();

    template <typename ValueType>
    class Iterator
        : public std::iterator<std::random_access_iterator_tag, ValueType> {
    public:
        Iterator() : pointer_(nullptr) {}
        explicit Iterator(ValueType* ptr) : pointer_(ptr) {}
        Iterator<ValueType>& operator+(const int& n) {
            pointer_ += n;
            return *this;
        }
        Iterator<ValueType>& operator-(const int& n) {
            pointer_ -= n;
            return *this;
        }
        size_t operator-(const Iterator<ValueType>& iter) {
            return pointer_ - iter.pointer_;
        }
        Iterator<ValueType>& operator+=(const ValueType& num) {
            *this = *this + num;
            return *this;
        }
        size_t& operator-=(const Iterator<ValueType>& iter) {
            *this = *this - iter;
            return *this;
        }
        Iterator<ValueType>& operator-=(const ValueType& num) {
            *this = *this - num;
            return *this;
        }

        Iterator<ValueType>& operator++(int) {
            pointer_++;
            return *this;
        }
        Iterator<ValueType>& operator--(int) {
            pointer_--;
            return *this;
        }
        Iterator<ValueType>& operator++() {
            ++pointer_;
            return *this;
        }
        Iterator<ValueType>& operator--() {
            --pointer_;
            return *this;
        }
        Iterator<ValueType>& operator=(const Iterator<ValueType> it) {
            if (this != &it) {
                pointer_ = it.pointer_;
            }
            return *this;
        }
        bool operator!=(const Iterator<ValueType>& it) {
            return pointer_ != it.pointer_;
        }
        bool operator==(const Iterator<ValueType>& it) {
            return pointer_ == it.pointer_;
        }
        bool operator>(const Iterator<ValueType>& it) {
            return pointer_ > it.pointer_;
        }
        bool operator<(const Iterator<ValueType>& it) {
            return pointer_ < it.pointer_;
        }
        ValueType& operator->() { return *pointer_; }
        ValueType& operator*() { return *pointer_; }
        friend class vector;

    private:
        ValueType* pointer_;
    };
    using iterator = Iterator<T>;

    vector<T>& operator=(const vector<T>& vec);
    template <class T1>
    friend std::ostream& operator<<(std::ostream& out, const vector<T1>& vec);
    iterator operator+=(const iterator& it) {}
    T& operator[](const size_t& index);
    T operator[](const size_t& index) const;
    T at(const size_t& index) const;
    T& at(const size_t& index);
    T& front() const noexcept;
    T& back() const noexcept;
    T* data() const noexcept;
    iterator begin() { return iterator(&front()); }
    iterator end() { return iterator(&back() + 1); }
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_t size() const noexcept;
    void reserve(const size_t& size);
    size_t capacity();
    void clear() noexcept;
    void insert(const size_t& index, const T& value);
    void push_back(const T& val);
    void pop_back();
    void swap(vector<T>& vec) noexcept;

private:
    T* data__;
    size_t size__;
    size_t capacity__;
};
template <class T>
vector<T>::vector() : size__(0), capacity__(0) {
    data__ = new T[1];
    data__[0] = 0;
}
template <class T>
vector<T>::vector(const size_t& size) : size__(size), capacity__(size) {
    data__ = new T[size__];
    for (size_t i = 0; i < size__; ++i) data__[i] = 0;
}
template <class T>
vector<T>::vector(const vector<T>& vec)
    : size__(vec.size__), capacity__(vec.capacity__) {
    data__ = new T[size__];
    for (size_t i = 0; i < vec.size__; ++i) {
        data__[i] = vec.data__[i];
    }
}
template <class T>
vector<T>::~vector() {
    delete[] data__;
}
template <class T>
vector<T>& vector<T>::operator=(const vector<T>& vec) {
    if (&vec != this) {
        delete[] this;
        size__ = vec.size__;
        data__ = new T[size__];
        for (size_t i = 0; i < size__; ++i) {
            data__[i] = vec.data__[i];
        }
    }
    return *this;
}
template <class T1>
std::ostream& operator<<(std::ostream& out, const vector<T1>& vec) {
    for (size_t i = 0; i < vec.size__; ++i) out << vec[i] << ' ';
    return out;
}
template <class T>
T& vector<T>::operator[](const size_t& index) {
    return data__[index];
}
template <class T>
T vector<T>::operator[](const size_t& index) const {
    return data__[index];
}
template <class T>
inline T vector<T>::at(const size_t& index) const {
    if (index >= capacity__) throw std::out_of_range("| Index was out of range!");
    return data__[index];
}
template <class T>
inline T& vector<T>::at(const size_t& index) {
    if (index >= capacity__) throw std::out_of_range("| Index was out of range!");
    return data__[index];
}
template <class T>
inline T& vector<T>::front() const noexcept {
    return *data__;
}
template <class T>
inline T& vector<T>::back() const noexcept {
    return *(data__ + size__ - 1);
}
template <class T>
inline T* vector<T>::data() const noexcept {
    return data__;
}
template <class T>
bool vector<T>::empty() const noexcept {
    return size__ == 0;
}
template <class T>
inline size_t vector<T>::capacity() {
    return capacity__;
}
template <class T>
size_t vector<T>::size() const noexcept {
    return size__;
}
template <class T>
void vector<T>::clear() noexcept {
    delete[] data__;
    data__ = nullptr;
    size__ = 0;
    capacity__ = 0;
}
template <class T>
inline void vector<T>::swap(vector<T>& vec) noexcept {
    if (&vec != this) {
        size_t i = 0;
        for (; i < (vec.size() > size__ ? size__ : vec.size()); ++i)
            std::swap(data__[i], vec.data__[i]);

        size_t count_minus = 0;
        if (i < vec.size()) {
            while (i < vec.size()) {
                (*this).push_back(vec[i]);
                ++i;
                ++count_minus;
            }
            vec.size__ -= count_minus;
        }
        else {
            while (i < size__) {
                vec.push_back(data__[i]);
                ++i;
                ++count_minus;
            }
            size__ -= count_minus;
        }
    }
}
template <class T>
inline void vector<T>::insert(const size_t& index, const T& value) {
    (*this).at(index) = value;
}
template <class T>
void vector<T>::reserve(const size_t& size) {
    capacity__ += size;
    T* temp_data = new T[size__];
    // coping the data to new array
    for (size_t i = 0; i < size__; ++i) temp_data[i] = data__[i];
    delete[] data__;
    data__ = new T[capacity__];
    // returning the data
    for (size_t i = 0; i < size__; ++i) data__[i] = temp_data[i];
    delete[] temp_data;
}
template <class T>
void vector<T>::pop_back() {
    if (empty()) {
        return;
    }
    --size__;
    if (size__ < (capacity__ / 2) && capacity__ / 1.5 > 5) {
        reserve(capacity__ * 1.5);
    }
}
template <class T>
inline void vector<T>::push_back(const T& val) {
    if (capacity__ == 0) {
        reserve(2);
    }
    else if (size__ >= capacity__) {
        reserve(capacity__ * 1.5);
    }
    ++size__;
    data__[size__ - 1] = val;
}

#endif  // INCLUDE_VECTOR_HEADER_HPP_
