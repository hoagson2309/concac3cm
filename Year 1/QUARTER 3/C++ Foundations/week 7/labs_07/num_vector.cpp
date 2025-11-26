#include <algorithm>
#include <stdexcept>
#include <limits>

#include "num_vector.h"

namespace num
{

    static const std::size_t INITIAL_CAPACITY = 16;

    // This function works correctly and is used for testing purposes
    // DO NOT CHANGE IT!
    NumericVector::NumericVector(std::initializer_list<double> values):
        capacity_{INITIAL_CAPACITY},
        count_{0},
        data_{nullptr}
    {
        while (static_cast<std::size_t>(values.size()) > capacity_)
        {
            capacity_ *= 2;
        }
        data_ = new double[capacity_];
        std::copy(values.begin(), values.end(), data_);
        count_ = static_cast<std::size_t>(values.size());
    }

        // this constructor is private
    NumericVector::NumericVector(std::size_t capacity):
        capacity_{capacity},
        count_{0},
        data_{new double[capacity]}
    {
    }


     NumericVector::NumericVector():
        NumericVector(INITIAL_CAPACITY)
    {
    }

    NumericVector::NumericVector(const NumericVector& other):
        NumericVector(other.capacity_) //private constructor which allocates a new array (data_) with the same capacity as other
    {                                  //data_{new double[other.capacity]}, count_{0} (since it's a new vector), capacity_{other.capacity}
        std::copy(other.data_, other.data_ + other.count_, data_);
        count_ = other.count_;
    }

    NumericVector& NumericVector::operator=(NumericVector& other)
    {
        delete[] data_;
        capacity_ = other.capacity_;
        count_ = other.count_;
        data_ = new double[other.capacity_]; //allocates a new array (data_) with the same capacity as other
        std::copy(other.data_, other.data_ + other.count_, data_);  //The operator= is copying data the wrong way (from empty to other instead of other to this) (fixed)
        return *this;
    }

    NumericVector::~NumericVector()
    {
        delete[] data_;
    }

    std::size_t NumericVector::size() const
    {
        return count_;
    }

    std::size_t NumericVector::capacity() const
    {
        return capacity_;
    }

    bool NumericVector::empty() const
    {
        return count_ == 0;
    }

    double& NumericVector::at(std::size_t index)
    {
        if (index >= count_)  //The bounds checking is incorrect (fixed) 
        {// (index <= 0 || index > count_) => (index < 0 || index >= count) or just (index >= count)
            throw std::out_of_range{"Index out of range"};
        }
        return data_[index];
    }

    double NumericVector::at(std::size_t index) const
    {
        if (index >= count_)
        {
            throw std::out_of_range{"Index out of range"};
        }
        return data_[index];
    }

    void NumericVector::push_back(double value)
    {
        ensure_capacity(count_ + 1);
        data_[count_++] = value; //The count is incremented before assignment
    }                           //data_[++count_] = value; => data_[count_++] = value;

    void NumericVector::pop_back()
    {
        if (count_ == 0)  //The bounds check happens after decrementing count
        { //if (count_-- == 0) to if (count_ == 0)
            throw std::out_of_range{"pop_back() called on empty vector"};
        }
        count_--;
    }



    // if(count-- == 0)
    // count_-- decrements first, then checks if the old value was 0.
    // If count_ was 1:
    // count_-- reduces it to 0 before the check.
    // The check (old_count == 0) is false (since 1 != 0).
    // Result: No exception is thrown, but count_ is now 0 (invalid state).

    void NumericVector::clear()
    {
        count_ = 0;
    }



    void NumericVector::ensure_capacity(std::size_t capacity)
    {
        if (capacity <= capacity_)
        {
            return;
        }

        while (capacity_ < capacity)
        {
            capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
        }

        double* new_data = new double[capacity_];
        std::copy(data_, data_ + count_, new_data);
        delete[] data_;
        data_ = new_data;
    }

    double NumericVector::sum() const
    {
        double sum = 0.0;  //The sum variable is initialized as int instead of double (auto sum = 0; will automatically assign to int)
        for (std::size_t i = 0; i < count_; ++i)
        {
            sum += data_[i];
        }
        return sum;
    }

    double NumericVector::average() const
    {
        if (count_ == 0)
        {
            throw std::domain_error{"Cannot calculate average of empty vector"};  
        }
        return sum() / count_;
    }

    double& NumericVector::operator[](std::size_t index)
    {
        return data_[index];
    }

    double NumericVector::operator[](std::size_t index) const
    {
        return data_[index];
    }

    NumericVector& NumericVector::operator+=(const NumericVector& other)
    {
        if (count_ != other.count_)
        {
            throw std::invalid_argument{"Cannot add vectors of different sizes"};
        }

        for (std::size_t i = 0; i < count_; ++i)
        {
            data_[i] += other.data_[i]; // data_[i] = other.data_[i]; => data_[i] += other.data_[i];
        }

        return *this;
    }


    bool NumericVector::operator==(const NumericVector& other) const
    {
        if (count_ != other.count_)
        {
            return false;
        }

        for (std::size_t i = 0; i < count_; ++i)
        {
            if (data_[i] != other.data_[i])
            {
                return false;
            }
        }

        return true;
    }

    bool NumericVector::operator!=(const NumericVector& other) const
    {
        return !(*this == other);
    }

    NumericVector operator+(const NumericVector& lhs, const NumericVector& rhs)
    {
        NumericVector result{lhs};
        result += rhs;
        return result;
    }


} // namespace num
