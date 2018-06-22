#include <iostream>
#include <initializer_list>
#include <stdexcept>

template<class T>
class vector
{
    friend bool operator==(vector<T>& op1, vector<T>& op2);
    friend bool operator!=(vector<T>& op1, vector<T>& op2);
    friend bool operator<=(vector<T>& op1, vector<T>& op2);
    friend bool operator>=(vector<T>& op1, vector<T>& op2);
    friend bool operator<(const vector<T>& op1, const vector<T>& op2);
    friend bool operator>(const vector<T>& op1, const vector<T>& op2);

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = std::size_t;

private:
    size_type reserved_size;
    size_type vector_size;
    T* storage;
    void realocate();

public:

    vector():reserved_size(0),vector_size(0)
    {
        storage = new T[reserved_size];
    };
    vector(std::initializer_list<T> _list)
    {
        vector_size = 0;
        reserved_size = _list.size()*2;
        storage = new T[reserved_size];

        for(typename std::initializer_list<T>::iterator i = _list.begin(); i != _list.end(); ++i )
        {
            push_back(*i);
        }
    }

    vector(const vector& _vector)
    {
        storage = new T[_vector.reserved_size];

        for(iterator i = this->begin(), j = _vector.begin();
                i < this->end(); ++i, ++j)
        {
            *i = *j;
        }
    }
    ~vector()
    {
        delete [] storage;
    }
    // Element access

    reference at(size_type pos);
    reference operator[](size_type pos);
    reference front();
    reference back();
    T* data()noexcept;

    // Iterators
    iterator begin();
    const_iterator cbegin()const noexcept;
    iterator end();
    const_iterator cend()const noexcept;

    //Capacity
    bool empty()const;
    size_type size()const;
    size_type max_size()const;
    size_type capacity()const noexcept;

    //Modifiers
    void push_back(const T& value);
    void pop_back();
    void clear();
    void swap(vector<T>& other);
};

//Element access
template<class T>
typename vector<T>::reference vector<T>::at(size_type pos)
{
    if(pos >= vector_size)
        throw std::out_of_range("'Pos' should be < size of vector!");
    return storage[pos];
}

template<class T>
typename vector<T>::reference vector<T>::operator[](size_type pos)
{
    return storage[pos];
}

template<class T>
typename vector<T>::reference vector<T>::front()
{
    return storage[0];
}

template<class T>
typename vector<T>::reference vector<T>::back()
{
    return storage[vector_size-1];
}

template<class T>
T* vector<T>::data() noexcept
{
    return storage;
}
//----------------------------------------------------------------
// Iterators

template<class T>
typename vector<T>::iterator vector<T>::begin()
{
    return storage;
}

template<class T>
typename vector<T>::const_iterator vector<T>::cbegin()const noexcept
{
    return storage;
}

template<class T>
typename vector<T>::iterator vector<T>::end()
{
    return storage + vector_size;
}

template<class T>
typename vector<T>::const_iterator vector<T>::cend()const noexcept
{
    return storage + vector_size;
}

//-----------------------------------------------------------------
//Capacity

template<class T>
bool vector<T>::empty()const
{
    return vector_size == 0;
}

template<class T>
typename vector<T>::size_type vector<T>::size()const
{
    return vector_size;
}

template<class T>
typename vector<T>::size_type vector<T>::max_size()const
{
    return 18446744073709551615;
}

template<class T>
typename vector<T>::size_type vector<T>::capacity()const noexcept
{
    return reserved_size;
}
//----------------------------------------------------------------
//Modifiers

template<class T>
void vector<T>::push_back(const T& value)
{
    if(vector_size==reserved_size)
    {
        reserved_size *=2;
        realocate();
    }
    storage[vector_size++] = value;
}

template<class T>
void vector<T>::pop_back()
{
    storage[--vector_size].~T();
}

template<class T>
void vector<T>::clear()
{
    if(vector_size > 0)
        --vector_size;
    for(; vector_size!=0; --vector_size)
        storage[vector_size].~T();
}

template<class T>
void vector<T>::swap(vector<T>& other)
{
    for(typename vector<T>::iterator i = this->begin(), j = other.begin(); i != this->end(); ++i, ++j)
        std::swap(*i, *j);
}
//-------------------------------------------------------------------
//Non-member functions

template<class T>
bool operator==(vector<T>& op1, vector<T>& op2)
{
    if(op1.size()!=op2.size())
        return false;
    for(typename vector<T>::iterator i = op1.begin(),j = op2.begin();
            i < op1.end() || j < op2.end(); ++i, ++j)
    {
        if(*i != *j)
        {
            return false;
        }
    }
    return true;
}

template<class T>
bool operator!=(vector<T>& op1, vector<T>& op2)
{
    return !(op1.storage == op2.storage);
}

template<class T>
bool operator<(vector<T>& op1, vector<T>& op2)
{
    for(typename vector<T>::iterator i = op1.begin(), j = op2.begin(); i != op1.end(); ++i, ++j)
    {
        if(*i < *j)
            return true;
        if(*j < *i)
            return false;
    }
}

template<class T>
bool operator>(vector<T>& op1, vector<T>& op2)
{
    for(typename vector<T>::iterator i = op1.begin(), j = op2.begin(); i != op1.end(); ++i, ++j)
    {
        if(*i > *j)
            return true;
        if(*j < *i)
            return false;
    }
}

template<class T>
bool operator<=(vector<T>& op1, vector<T>& op2)
{

}

template<class T>
bool operator>=(vector<T>& op1, vector<T>& op2)
{

}

template<class T>
void vector<T>::realocate()
{
    T* temp = new T[reserved_size];
    for(int i = 0; i < vector_size; ++i)
    {
        temp[i] = storage[i];
    }
    delete [] storage;
    storage = temp;
}


int main()
{
    vector<int> arr{1,1,1,1};
    vector<int> arr1{1,2,3,4};
    arr.swap(arr1);

    for(vector<int>::iterator i = arr1.begin(); i != arr1.end(); ++i)
        std::cout << *i;
    return 0;
}
