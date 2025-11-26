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