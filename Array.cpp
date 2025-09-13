#include "Array.h"
#include <iostream>
#include <stdexcept>

template <typename T>
Array<T>::Array() {
    m_cur_size = 0;
    m_max_size = 0;

    m_data = nullptr;
}

template <typename T>
Array<T>::Array(unsigned int length) {
    m_cur_size = length;
    m_max_size = length;
    
    m_data = new char[length];
}

template <typename T>
Array<T>::Array(unsigned int length, T fill) {
    m_cur_size = length;
    m_max_size = length;

    m_data = new T[length];
    for (int i = 0; i < length; i++) {
        m_data[i] = fill;
    }
}

template <typename T>
Array<T>::Array(const Array & arr) {
    m_cur_size = arr.get_size();
    m_max_size = arr.get_max_size();
    m_data = new char[m_cur_size];

    for (int i = 0; i < m_cur_size; i++) {
        m_data[i] = arr.get_element(i);
    }
}

template <typename T>
Array<T>::~Array() {
   delete [] m_data;
}

template <typename T>
unsigned int Array<T>::get_size() const {
    return m_cur_size;
}

template <typename T>
unsigned int Array<T>::get_max_size() const {
    return m_max_size;
}

template <typename T>
void Array<T>::set_element(unsigned int index, T el) {
    if (index > m_cur_size) {
        throw std::out_of_range("Index out of range.");
    }
    m_data[index] = el;
}

template <typename T>
T Array<T>::get_element(unsigned int index) const {
    if (index > m_cur_size) {
        throw std::out_of_range("Index out of range.");
    }
    return m_data[index];
}

template <typename T>
void Array<T>::resize(unsigned int length) {
    if (length > m_max_size) {
        reallocate_(length);
    } else {
        m_cur_size = length;
    }
}

template <typename T>
void Array<T>::shrink() {
    reallocate_(m_cur_size);
}

template <typename T>
int Array<T>::find(T target) const {
    for (int i = 0; i < m_cur_size; i++) {
        if (m_data[i] == target) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Array<T>::fill(T el) {
    for (int i = 0; i < m_cur_size; i++) {
        m_data[i] = el;
    }
}


template <typename T>
void Array<T>::reverse() {
    unsigned int head = 0;
    unsigned int mid = m_cur_size / 2;
    unsigned int tail = m_cur_size - 1;

    while (head < mid) {
        char temp = m_data[tail];
        m_data[tail] = m_data[head];
        m_data[head] = temp;

        head++;
        tail--;
    }
}

template <typename T>
Array<T> Array<T>::slice(unsigned int begin) const {
    if (begin > m_cur_size) {
        throw std::out_of_range("Index out of range.");
    }
    return slice(begin, m_cur_size);
}

template <typename T>
Array<T> Array<T>::slice(unsigned int begin, unsigned int end) const {
    if (begin > m_cur_size || end > m_cur_size) {
        throw std::out_of_range("Index out of range.");
    }

    unsigned int length = end - begin;
    Array arr = Array(length);

    for (int i = 0; i < length; i++) {
        char el = m_data[begin + i];
        arr.set_element(i, el);
    } 

    return arr;
}

template <typename T>
T & Array<T>::operator [] (unsigned int index) {
    return m_data[index];
}


template <typename T>
const T & Array<T>::operator [] (unsigned int index) const {
    return m_data[index];
}

template <typename T>
const Array<T> Array<T>::operator = (const Array & rhs) {
    m_cur_size = rhs.get_size();
    m_max_size = rhs.get_max_size();

    delete [] m_data;
    m_data = new char[m_cur_size];

    for (int i = 0; i < m_cur_size; i++) {
        m_data[i] = rhs.get_element(i);
    }

    return *this;
}

template <typename T>
bool Array<T>::operator == (const Array & rhs) const {
    if (&rhs == this) {
        return true;
    }

    if (m_cur_size == rhs.get_size()) {
        for (int i = 0; i < m_cur_size; i++) {
            if (m_data[i] != rhs.get_element(i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool Array<T>::operator != (const Array & rhs) const {
    return !(*this == rhs);
}

template <typename T>
void Array<T>::reallocate_(unsigned int length) {
    T * temp = new char[length];

    for (int i = 0; i < m_cur_size; i++) {
        temp[i] = m_data[i];
    }

    delete [] m_data;

    m_data = temp;

    m_cur_size = length;
    m_max_size = length;
}