#include "IntVector.h"

#include <cstring>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace exam
{
    static const std::size_t INITIAL_CAPACITY = 16;

    //default constructor
    IntVector::IntVector()
        : size_{0}, capacity_{INITIAL_CAPACITY}, data_{new long[capacity_]} {}
    
    IntVector::~IntVector(){
        delete[] data_;
    }

    IntVector::IntVector(const IntVector& other) : data_(new long[other.capacity_]), size_(other.size_), capacity_(other.capacity_){
        std::copy(other.data_, other.data_ + other.size_, data_);    //not including null terminator so no + 1 for capacity
    }

    IntVector& IntVector::operator=(const IntVector& other){
        if(this != &other){
            delete[] data_;                             //free old memory
            data_ = new long[other.capacity_ ];      //allocate new memory, no +1 for null terminator cuz not a string
            size_ = other.size_;                        //update size
            capacity_ =  other.capacity_;               //update capacity
            std::copy(other.data_, other.data_ + other.size_, data_);   //copy data_ to other.data_
        }
        return *this;
    }
    
    void IntVector::push_back(long value)
    {
        ensure_capacity();
        data_[size_++] = value;
    }

    std::size_t IntVector::size() const
    {
        return size_;
    }

    long IntVector::operator[](std::size_t index) const
    {
        return data_[index];
    }

    long* IntVector::begin()
    {
        return data_;
    }

    long* IntVector::end()
    {
        return data_ + size_;
    }

    const long* IntVector::begin() const
    {
        return data_;
    }

    const long* IntVector::end() const
    {
        return data_ + size_;
    }

    void IntVector::sort()
    {
        std::sort(begin(), end());
    }

    void IntVector::unique()
    {
        // an ugly quadratic, manual implementation of unique. but hey, it's at least stable!
        auto current = begin();
        auto last = end();
        while (current != last)
        {
            auto next = current + 1;
            while (next != last)
            {
                if (*current == *next)
                {
                    std::copy(next + 1, last, next);
                    --last;
                }
                else
                {
                    ++next;
                }
            }
            ++current;
        }
        size_ = last - begin();
    }

    void IntVector::resize(size_t new_capacity){
        long* new_data = new long[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void IntVector::ensure_capacity(){
        if(size_ == capacity_){
            resize(capacity_ * 2); // double the capacity
        }
    }

    std::ostream& operator<<(std::ostream& os, const IntVector& v){
        os << "[";
        for(size_t i = 0; i < v.size(); i++){
            if(i != 0) os << ", ";
            os << v.operator[](i);
        }
        os << "]";
        return os;
    }

    
}



