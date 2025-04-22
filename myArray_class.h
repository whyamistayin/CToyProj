#include "Node_Class.h"
#include <cstdlib>
#include <cstring>
#include <new>
#include <sstream>
#include <iostream>

template <typename T>
class myArray
{
private:
    Node<T> *buffer;
    Node<T> *first;
    Node<T> *last;
    size_t len{0};
    size_t allocated;
    void extendMemory(size_t newAlloc);
    void initialMemory(size_t alloc);
    void insertionSort(bool reverse = false);
public:
    myArray();
    myArray(T &initial);
    myArray(const T *inputArray, size_t len2);
    myArray(const myArray &inputArray, size_t len2 = 0);
    myArray(myArray &&inputArray);
    ~myArray();
    size_t length() const { return len; };
    size_t memory() const { return allocated; };
    Node<T> &operator[](long long index) const;
    T pop(long long index = -1);
    size_t index(const T &element, size_t from = 0) const;
    bool in(const T &element) const;
    size_t count(const T &element) const;
    void append(const T &element);
    void reverse();
    void clear(bool shrink = true);
    myArray<T> copy() const;
    void sort(bool reverse = false);
    std::string str(std::string del = ", ") const;
    void extend(const myArray<T> &second);
    void vectorise(T (*func) (T));
    bool isSubarray(myArray<T> &other) const;
    int countIf(bool (*func) (T)) const;
    void insert(T element, long long index = 0);
    T front() const;
    T back() const;
    void operator+=(const myArray<T> &second);
    bool operator==(const myArray<T> &second) const;
    bool operator!() const { return len == 0; };
    std::ostringstream &operator<<(std::ostringstream &in);
    myArray<T> &operator=(const myArray &inputArray);
    myArray<T> &operator=(myArray &&inputArray) noexcept ;
    myArray<T> operator+(myArray<T> &other);
    size_t subarrayIndex(myArray<T> &other, size_t from = 0) const;
    void remove(T element);
    myArray<T> operator[](long long start, long long end, long long step = 1) const;
    T at(long long index) const;
    T max() const;
    T min() const;
    T sum() const;
};


template<typename T>
T myArray<T>::sum() const
{
    T result;
    for(size_t m = 0; m < len; m += 1)
        result = result + buffer[m].get_data();
    return result;
}


template<typename T>
T myArray<T>::at(long long int index) const
{
    return this->operator[](index).get_data();
}


template<typename T>
myArray<T> myArray<T>::operator[](long long start, long long end, long long step) const
{
    if(start < 0)
        start += len;
    if(end < 0)
        end += len;
    if(start >= len || start < 0 || end < 0 || end >= len || step == 0 || start > end)
        throw std::out_of_range("Index is out of range.");
    myArray<T> output;
    for(size_t i = step > 0 ? start : end; step > 0 ? i <= end : i >= start; i += step)
    {
        output.append(buffer[i].get_data());
        if(step == -1 && i == 0) break;
    }
    return output;
}


template<typename T>
void myArray<T>::insert(T element, long long int index)
{
    this->operator[](index);
    append(element);
    for(size_t i = len - 2; i >= index; --i)
        buffer[i + 1] = buffer[i];
    buffer[index] = element;
}


template<typename T>
void myArray<T>::operator+=(const myArray<T> &second)
{
    extend(second);
}

template<typename T>
bool myArray<T>::operator==(const myArray<T> &second) const
{
    if(len != second.length())
        return false;
    for(size_t n = 0; n < len; ++n)
        if(second[n] != buffer[n])
            return false;
    return true;
}

template<typename T>
T myArray<T>::back() const
{
    return last->get_data();
}

template<typename T>
T myArray<T>::front() const
{
    return first->get_data();
}

template<typename T>
int myArray<T>::countIf(bool (*func)(T)) const
{
    int output = 0;
    if(first == nullptr) return output;
    auto iter = first;
    do {
        if(func(iter->get_data()))
            output += 1;
        iter = iter->get_next();
    } while(iter != nullptr);
    return output;
}

template<typename T>
void myArray<T>::initialMemory(size_t alloc)
{
    buffer = (Node<T>*)std::malloc(alloc * sizeof(Node<T>));
    if (!buffer)
        throw std::bad_alloc();
    allocated = alloc;
}


template<typename T>
myArray<T>::myArray(): buffer(nullptr), first(nullptr), last(nullptr)
{
    initialMemory(10);
}

template<typename T>
myArray<T>::myArray(T &initial): buffer(nullptr), first(nullptr), last(nullptr)
{
    initialMemory(10);
    append(initial);
    first = *buffer[0];
    last = first;
}

template<typename T>
myArray<T>::myArray(const T* inputArray, size_t len2): buffer(nullptr),first(nullptr),last(nullptr),len(len2)
{
    initialMemory(2 * len2);
    Node<T> *prev = nullptr;
    for(size_t j = 0; j < len2; ++j)
    {
        buffer[j] = Node<T>(inputArray[j]);
        if (prev != nullptr)
        {
            prev->set_next(*buffer[j]);
            buffer[j].set_previous(prev);
        }
        prev = *buffer[j];
    }
    first = *buffer[0];
    last = *buffer[len - 1];
}

template<typename T>
myArray<T>::myArray(const myArray<T> &inputArray, size_t len2): buffer(nullptr),first(nullptr),last(nullptr),
                                                                len(len2 == 0 ? inputArray.length() : len2)
{
    initialMemory(2 * len);
    Node<T> *previous = nullptr;
    for(size_t j = 0; j < (len2 == 0 ? inputArray.length() : len2); ++j)
    {
        buffer[j] = Node<T>(inputArray.at(j), previous);
        if (previous != nullptr)
            previous->set_next(*buffer[j]);
        previous = &buffer[j];
    }
    first = *buffer[0];
    last = *buffer[len - 1];
}

template<typename T>
myArray<T>::myArray(myArray &&inputArray): len(inputArray.length()),buffer(nullptr),first(nullptr),last(nullptr)
{
    initialMemory(2 * inputArray.length());
    Node<T> *previous = nullptr;
    for(size_t j = 0; j < inputArray.length(); ++j)
    {
        buffer[j] = Node<T>(inputArray.at(j), previous);
        if (previous != nullptr)
            previous->set_next(*buffer[j]);
        previous = &buffer[j];
    }
    first = *buffer[0];
    last = *buffer[len - 1];
    inputArray.clear(true);
}

template<typename T>
myArray<T> &myArray<T>::operator=(const myArray &inputArray)
{
    if(inputArray.length() > allocated)
        extendMemory(inputArray.length() * 2);
    for(size_t i = 0; i < inputArray.length(); ++i)
        buffer[i] = inputArray.at(i);
    len = inputArray.length();
    first = *buffer[0];
    last = *buffer[len - 1];
    buffer[len - 1].set_next(nullptr);
}

template<typename T>
myArray<T> &myArray<T>::operator=(myArray &&inputArray) noexcept
{
    this->operator=(inputArray);
    inputArray.clear();
    return *this;
}

template<typename T>
Node<T> &myArray<T>::operator[](long long index) const
{
    if(index < 0)
        index = len + index;
    if(index >= len || index < 0)
        throw std::out_of_range("Index is out of range.");
    return buffer[index];
}

template<typename T>
void myArray<T>::extendMemory(size_t newAlloc)
{
    auto newBuffer = (Node<T> *) std::malloc(newAlloc * sizeof(Node<T>));
    if (!newBuffer)
        throw std::bad_alloc();
    if(len > 0)
        std::memcpy(newBuffer, buffer, newAlloc * sizeof(Node<T>));
    std::free(buffer);
    buffer = newBuffer;
    allocated = newAlloc;
}

template<typename T>
T myArray<T>::pop(long long index)
{
    if(len == 0)
        throw std::out_of_range("Pop from an empty list.\n");
    if(index < 0)
        index = len + index;
    if(index >= len || index < 0)
        throw std::out_of_range("Index is out of range.\n");
    auto output = at(index);
    if(index < len - 1)
    {
        do {
            buffer[index] = buffer[index + 1];
        } while(index++ < len - 2);
    }
    last = last->get_previous();
    last->set_next(nullptr);
    buffer[len-- - 1].set_previous(nullptr);
    return output;
}

template<typename T>
size_t myArray<T>::index(const T &element, size_t from) const
{
    for(size_t j = from; j < len; ++j)
        if(buffer[j] == element)
            return j;
    throw std::out_of_range("Object is not in list.\n");
}

template<typename T>
bool myArray<T>::in(const T &element) const
{
    auto iter = first;
    while(iter != nullptr)
    {
        if(element == iter->get_data())
            return true;
        iter = iter->get_next();
    }
    return false;
}

template<typename T>
size_t myArray<T>::count(const T &element) const
{
    long output(0);
    for(size_t j = 0; j < len; ++j)
        if(buffer[j] == element)
            ++output;
    return output;
}

template<typename T>
void myArray<T>::append(const T &element)
{
    if(len == allocated)
        extendMemory((allocated + 1) * 2);
    buffer[len] = Node<T>(element, len > 0 ? *buffer[len - 1] : nullptr);
    buffer[len - 1].set_next(*buffer[len]);
    len += 1;
    last = *buffer[len - 1];
    if(first == nullptr) first = last;
}

template<typename T>
void myArray<T>::reverse()
{
    long border = len / 2;
    for(size_t i = 0; i < border; ++i)
    {
        auto temp = buffer[len - i - 1];
        buffer[len - i - 1] = buffer[i];
        buffer[i] = temp;
    }
}

template<typename T>
void myArray<T>::extend(const myArray<T> &second)
{
    size_t leng = second.length();
    if(len + leng > allocated)
        extendMemory((len + leng) * 2);
    for(size_t i = 0; i < leng; ++i)
        append(second.at(i));
}

template<typename T>
void myArray<T>::clear(bool shrink)
{
    for(size_t i = 0; i < len; ++i)
        buffer[i].~Node();
    len = 0;
    if(shrink)
        extendMemory(10);
}

template<typename T>
myArray<T>::~myArray()
{
    clear(false);
    std::free(buffer);
}

template<typename T>
myArray<T> myArray<T>::copy() const
{
    myArray<T> output;
    for(size_t i = 0; i < len; i += 1)
        output.append(at(i));
    return output;
}

template<typename T>
void myArray<T>::insertionSort(bool reverse)
{
    if(len < 2) return;
    for(size_t i = 1; i < len; ++i)
    {
        T key = buffer[i].get_data();
        size_t j = i - 1;
        while(reverse ? buffer[j] < key : buffer[j] > key)
        {
            buffer[j + 1] = buffer[j];
            if(j == 0)
                break;
            j -= 1;
        }
        buffer[j == 0 ? 0 : j + 1] = key;
    }
}

template<typename T>
void myArray<T>::sort(bool reverse)
{
    insertionSort(reverse);
}

template<typename T>
std::string myArray<T>::str(std::string del) const
{
    std::ostringstream output;
    for(size_t i = 0; i < len; ++i)
    {
        if(!output.str().empty())
            output << del;
        output << at(i);
    }
    return output.str();
}

template<typename T>
void myArray<T>::vectorise(T (*func) (T))
{
    if(first == nullptr) return;
    for(size_t i = 0; i < len; ++i)
        buffer[i] = func(buffer[i].get_data());
}

template<typename T>
bool myArray<T>::isSubarray(myArray<T> &other) const
{
    try {
        subarrayIndex(other);
        return true;
    } catch (std::out_of_range &e) {
        return false;
    }
}

template<typename T>
size_t myArray<T>::subarrayIndex(myArray<T> &other, size_t from) const
{
    size_t m = other.length();
    auto lps = new size_t[m+1];
    size_t j = 0;
    size_t i = 1;
    while (i < m) {
        if (other.at(i) == other.at(j)) {
            j++;
            lps[i] = j;
            i++;
        }
        else {
            if (j != 0)
                j = lps[j-1];
            else
                lps[i++] = 0;
        }
    }
    i = from;
    j = 0;
    while (i < len) {
        if (this->at(i) == other.at(j)) {
            i++;
            j++;
            if (j == m) {
                delete [] lps;
                return i - j;
            }
        }
        else {
            if (j == 0)
                i++;
            else
                j = lps[j-1];
        }
    }
    delete [] lps;
    throw std::out_of_range("Not a subarray");
}

template<typename T>
void myArray<T>::remove(T element)
{
    try {
        auto ind = index(element);
        pop(ind);
    } catch (std::out_of_range &e) {
        return;
    }
}


template<typename T>
T myArray<T>::min() const
{
    auto iter = first;
    T mx;
    if (len == 0) throw std::out_of_range("Empty list.");
    while(iter != nullptr)
    {
        if(iter->get_data() < mx)
            mx = iter->get_data();
        iter = iter->get_next();
    }
    return mx;
}

template<typename T>
T myArray<T>::max() const
{
    auto iter = first;
    if (len == 0) throw std::out_of_range("Empty list.");
    T mx;
    while(iter != nullptr)
    {
        if(iter->get_data() > mx)
            mx = iter->get_data();
        iter = iter->get_next();
    }
    return mx;
}


template<typename T>
myArray<T> myArray<T>::operator+(myArray<T> &other)
{
    myArray<T> newArr = copy();
    newArr.extend(other);
    return newArr;
}

template<typename T>
std::ostringstream &myArray<T>::operator<<(std::ostringstream &in)
{
    in << str();
    return in;
}