#ifndef ARRAY_H
#define ARRAY_H


/**
 * @class Array 
 * 
 * Class representing a standard array of characters
*/
template <typename T>
class Array {
    public:
        
        // Default constructor
        Array();

        /**
         * Parameterized constructor
         * 
         * @param[in] length: the length of the array 
         */
        Array(unsigned int length);

        /**
         * Parameterized constructor
         * 
         * @param[in] length: the length of the array
         * @param[in] fill: initial value for each element
        */
        Array(unsigned int length, T fill);


        /**
         * Copy constructor
         * 
         * @param[in] Array: reference to the Array object to be copied
        */
        Array(const Array & arr);

        // Destructor
        ~Array();

        // returns the current size of the Array
        unsigned int get_size() const;

        // returns the maximum size of the Array
        unsigned int get_max_size() const;

        /**
         * returns the element at the specified index
         * 
         * @throws std::out_of_range: if index is greater than current size
         */ 
        T get_element(unsigned int index) const;

        /**
         * sets the element at specified index to character el 
         * 
         * @throws std::out_of_range: if index is greater than current size
        */
        void set_element(unsigned int index, T el);

        /**
         * Sets a new size for the Array
         * 
         * If given length is greater than the max size, reallocate.
         * If length is smaller, Array is truncated. 
         * 
         * @param[in] length: new size for the array
        */
        void resize(unsigned int length);

        // shrink the array to reclaim unused space.
        void shrink();

        /**
         * Locate specified character in the array
         * 
         * @param[in] target: character to be found
         * @return index of first occurence of character
         * @retval -1 if character not found
        */
        int find(T target) const;

        // replace all elements in the array with given character
        void fill(T el);

        // reverse the array in place
        void reverse();
 
        /**
         * Returns a portion of the Array
         * 
         * @param[in] begin: the first index to be included in the slice (inclusive)
         * @param[in] end: the final index (exclusive)
         * @return a new Array
        */
        Array slice(unsigned int begin, unsigned int end) const;

        /**
         * Returns a portion of the Array from provided beginning index
         * to the end of the Array
         * 
         * @param[in] begin: the first index to be included in the slice (inclusive)
        */
        Array slice(unsigned int begin) const;


        /**
         * Get the character at the specified index. If the index is not
         * within the range of the array, then std::out_of_range exception
         * is thrown.
         *
         * @param[in] index: Zero-based location
         * @throws std::out_of_range: Invalid index value
         */
        T & operator [] (unsigned int index);

        /**
         * @overload
         *
         * The returned character is not modifiable.
         */
        const T & operator [] (unsigned int index) const;

        // assignment operator
        const Array operator = (const Array & rhs);
        
        /**
         * Equality operator
         * 
         * @param[in] rhs: reference to the right side of the == 
         * @retval true: lhs is equal to rhs (same core array)
         * @retval false: lhs is not equal to rhs
        */
        bool operator == (const Array & rhs) const;

        /**
         * Inequality operator
         * 
         * @param[in] rhs: reference to the right side of the != 
         * @retval true: lhs is not equal to rhs 
         * @retval false: lhs is equal to rhs (same core array)
        */
        bool operator != (const Array & rhs) const;

    private:
        T * m_data;
        unsigned int m_cur_size;
        unsigned int m_max_size;

        /**
         * helper function that deletes and reallocates the core C-style array
         * 
         * @param[in] length: length of new allocation
         */
        void reallocate_(unsigned int length);

};


// --- TEMPLATE CLASS DEFINITION --- //

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

#endif 