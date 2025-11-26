#include "IntVector.h"

#include <algorithm>
#include <stdexcept>

namespace exam
{
    static const std::size_t INITIAL_CAPACITY = 16;

    IntVector::IntVector() :
        size_{0}, capacity_{INITIAL_CAPACITY}, data_{new long[capacity_]}
    {
    }

    // A private constructor that allows to create a vector with a given capacity
    // It's added, because it simplifies the implementation of ensure_capacity and copy constructor
    // During the exam, you are allowed to add private functions that make your life easier

    IntVector::IntVector(std::size_t capacity):
        size_{0}, capacity_{capacity}, data_{new long[capacity]}
    {}

    /*
    // alternative, without using the existing constructor
    IntVector::IntVector(const IntVector& other)
        : size_{other.size_}, capacity_{other.capacity_}, data_{new long[other.capacity_]}
    {
        std::copy(other.data_, other.data_ + size_, data_);
    }
     */

    IntVector::IntVector(const IntVector& other)
        : IntVector{other.capacity_}    // delegating work to the private constructor
    {
        size_ = other.size_;
        std::copy(other.data_, other.data_ + size_, data_);
    }

    void IntVector::swap(IntVector& other)
    {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

    IntVector& IntVector::operator=(const exam::IntVector& other)
    {
        if (this == &other) return *this;

        auto copy = other;
        swap(copy);

        /*
        // alternative, without copy-and-swap
        auto temp = new long[other.capacity_];

        std::copy(other.data_, other.data_ + other.size_, temp);
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] data_;
        data_ = temp;
         */
        return *this;
    }

    IntVector::~IntVector()
    {
        delete[] data_;
    }

    void IntVector::ensure_capacity()
    {
        if (size_ == capacity_)
        {
            /*
            // alternative, without just creating a new vector and swapping
            auto cap = 2 * capacity_;
            auto temp = new long[cap];
            std::copy(data_, data_ + size_, temp);
            capacity_ = cap;
            delete[] data_;
            data_ = temp;
             */

            IntVector big{capacity_ * 2};
            std::copy(data_, data_ + size_, big.data_);
            big.size_ = size_;
            swap(big);
        }
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
        // an ugly O(n^2), manual implementation of unique. but hey, it's at least stable!
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


}