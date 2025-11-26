#include "IntVector.h"

#include <algorithm>
#include <stdexcept>
#include <sstream>

namespace exam
{
    static const std::size_t INITIAL_CAPACITY = 16;

    IntVector::IntVector()
        : size_{0}, capacity_{INITIAL_CAPACITY}, data_{new long[capacity_]}
    {}

    IntVector::~IntVector(){
        delete[] data_;
    }

    IntVector::IntVector(const IntVector& other) : size_{other.size_}, capacity_{other.capacity_}, data_{new long[other.capacity_]} {
        std::copy(other.data_, other.data_ + other.size_, data_); // 0 cong 1 vi la long k phai string
    }

    IntVector& IntVector::operator=(const IntVector& other){
        if(this != &other){
            long* new_data = new long[other.capacity_];
            std::copy(other.data_, other.data_ + other.size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = other.capacity_;
            size_ = other.size_;
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
        if(index >= size_) throw std::out_of_range("Index out of bound\n");
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
            size_t new_capacity = capacity_ * 2;
            resize(new_capacity);
        }
    }

    std::ostream& operator<<(std::ostream& out, const IntVector& v){
        out << "[";
        for (size_t i = 0; i < v.size(); ++i){
            if(i > 0) out << ',';
            out << v.operator[](i);
        }
        out << "]";
        return out;
    }
}

