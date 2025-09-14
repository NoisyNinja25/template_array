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

#include "Array.inl"

#endif