# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 12/3/2025

# LABS
```cpp
//NUMBERS.H
#ifndef INCLUDED_NUMBERS_H
#define INCLUDED_NUMBERS_H

#include <cstddef>
#include <iostream>


namespace numeric
{
    class Numbers
    {
    public:
        Numbers();
        ~Numbers();

        // Only function prototypes go here. The implementations should be in numbers.cpp

        // TODO 1: Implement swap member function
        void swap(Numbers& other) noexcept;

        // TODO 2: Implement the copy constructor:
        Numbers(const Numbers& other);

        // TODO 3: Implement the copy assignment operator
        Numbers& operator=(const Numbers& other);

        // TODO 4: Implement a clone function that makes a full copy of the object (yes it works like the copy constructor)
        Numbers clone() const;

        std::size_t size() const;

        void push_back(double value);
        double pop_back();

        double front() const;
        double& front();

        double back() const;
        double& back();


        double * begin();
        double * end();

        const double * begin() const;
        const double * end() const;
        
        double at(std::size_t index) const;
        double& at(std::size_t index);

        double operator[](std::size_t index) const;
        double& operator[](std::size_t index);

        friend std::ostream& operator<<(std::ostream& os, const Numbers& numbers);

    private:

        double * array_;
        std::size_t size_;
        std::size_t capacity_;
    };

    std::ostream& operator<<(std::ostream& os, const Numbers& numbers);
}


#endif // INCLUDED_NUMBERS_H

//NUMBERS.CPP
#include "numbers.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace numeric
{
    static constexpr std::size_t INITIAL_CAPACITY = 16;

    Numbers::Numbers() : 
        array_(new double[INITIAL_CAPACITY]{}), 
        size_(0), 
        capacity_(INITIAL_CAPACITY)
    {
    }

    Numbers::~Numbers()
    {
        delete[] array_;
    }

    //copy constructor
    Numbers::Numbers(const Numbers& other) : 
        array_(new double[other.capacity_]), //Allocate new memory for the array
        size_(other.size_),                  //Copy the size from the other object
        capacity_(other.capacity_) {         //Copy the capacity from the other object
            std::copy(other.begin(), other.end(), array_);  //Deep copy: Copy all elements from 'other' to the new array
        }

    //copy assignment operator
    Numbers& Numbers::operator=(const Numbers& other){
        if(this != &other){         //Check for self-assignment (e.g., numbers1 = numbers1) (Check if the object is being assigned to itself. This avoids unnecessary work and potential bugs.)
            Numbers temp(other);    //Create a temporary copy of 'other' (uses the copy constructor)
            swap(temp);             //Swap the current object's data with the temporary object
        }
        return *this;               //Return the current object to allow chaining (e.g., numbers1 = numbers2 = numbers3)
    }

    //swap function
    void Numbers::swap(Numbers& other) noexcept{ //noexcept: Indicates that this function does not throw exceptions, making it safe to use in critical operations.
        std::swap(array_, other.array_);    //Swap the pointers to the dynamic arrays
        std::swap(size_, other.size_);      //swap sizes
        std::swap(capacity_, other.capacity_);   //swap capacities
    }

    //clone function
    Numbers Numbers::clone() const{
        return Numbers(*this); // Use the copy constructor to create a new object that is a copy of the current object.
    }

    std::size_t Numbers::size() const
    {
        return size_;
    }

// Copy Constructor: Ensures a deep copy when a new object is created from an existing one.
// Copy Assignment Operator: Ensures a deep copy when assigning one object to another.
// Swap Function: Efficiently swaps the contents of two objects, used in the copy assignment operator for strong exception safety.
// Clone Function: Provides an explicit way to create a copy of an object.
    

    void Numbers::push_back(double value)
    {
        if (size_ == capacity_)
        {
            capacity_ *= 2;
            double * temp = new double[capacity_];
            std::copy(begin(), end(), temp);
            delete[] array_;
            array_ = temp;
        }
        array_[size_++] = value;
    }

    double Numbers::pop_back()
    {
        if (size_ == 0)
        {
            throw std::out_of_range("pop_back() called on empty Numbers object");
        }
        return array_[--size_];
    }

    double Numbers::front() const
    {
        if (size_ == 0)
        {
            throw std::out_of_range("front() called on empty Numbers object");
        }
        return array_[0];
    }

    double& Numbers::front()
    {
        if (size_ == 0)
        {
            throw std::out_of_range("front() called on empty Numbers object");
        }
        return array_[0];
    }

    double Numbers::back() const
    {
        if (size_ == 0)
        {
            throw std::out_of_range("back() called on empty Numbers object");
        }
        return array_[size_ - 1];
    }

    double& Numbers::back()
    {
        if (size_ == 0)
        {
            throw std::out_of_range("back() called on empty Numbers object");
        }
        return array_[size_ - 1];
    }

    double * Numbers::begin()
    {
        return array_;
    }

    double * Numbers::end()
    {
        return array_ + size_;
    }

    const double * Numbers::begin() const
    {
        return array_;
    }

    const double * Numbers::end() const
    {
        return array_ + size_;
    }

    double Numbers::at(std::size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("at() called with index out of range");
        }
        return array_[index];
    }

    double& Numbers::at(std::size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("at() called with index out of range");
        }
        return array_[index];
    }

    double Numbers::operator[](std::size_t index) const
    {
        return array_[index];
    }

    double& Numbers::operator[](std::size_t index)
    {
        return array_[index];
    }

    std::ostream& operator<<(std::ostream& os, const Numbers& numbers)
    {
        os << "Numbers {capacity: " << numbers.capacity_ << ", size: " << numbers.size_ << "}: ";
        os << "[";
        if (numbers.size() > 0)
        {
            os << numbers[0];
            // if size is greater than 20 only print the first 10 and last 10
            if (numbers.size() > 20)
            {
                for (std::size_t i = 1; i < 10; ++i)
                {
                    os << ", " << numbers[i];
                }
                os << ", ...";
                for (std::size_t i = numbers.size() - 10; i < numbers.size(); ++i)
                {
                    os << ", " << numbers[i];
                }
            }
            else{
                for (std::size_t i = 1; i < numbers.size(); ++i)
                {
                    os << ", " << numbers[i];
                }
            }
        }
        os << "]";
        return os;
    }

}

//MAIN.CPP
#include "numbers.h"

int main()
{
    using namespace numeric;
    
    Numbers numbers1{};
    numbers1.push_back(3.14);
    numbers1.push_back(2.71);
    numbers1.push_back(1.61);

    Numbers numbers2{numbers1}; // copy constructor

    Numbers numbers3{};
    numbers3 = numbers1; // copy assignment operator

    numbers2.pop_back();
    numbers2.push_back(1.41);

    std::cout << numbers1 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41]
    std::cout << numbers2 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41] (yes!)
    std::cout << numbers3 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41] (yes! again)
}

```