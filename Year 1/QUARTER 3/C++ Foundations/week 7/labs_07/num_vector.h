#ifndef INCLUDED_NUM_VECTOR_H
#define INCLUDED_NUM_VECTOR_H

#include <initializer_list>

namespace num
{
    class NumericVector
    {
    public:
        NumericVector();
        NumericVector(std::initializer_list<double> values);

        NumericVector(const NumericVector& other);
        NumericVector& operator=(NumericVector& other);

        ~NumericVector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;
        double& at(std::size_t index);
        double at(std::size_t index) const;


        void push_back(double value);
        void pop_back();
        void clear();

        // operators & numeric functions

        double sum() const;
        double average() const;

        double& operator[](std::size_t index);
        double operator[](std::size_t index) const;

        NumericVector& operator+=(const NumericVector& other);
    
        bool operator==(const NumericVector& other) const;
        bool operator!=(const NumericVector& other) const;

    private:
        NumericVector(std::size_t capacity);
        void ensure_capacity(std::size_t capacity);

        std::size_t capacity_{0};
        std::size_t count_{0};
        double * data_{nullptr};
    };

    NumericVector operator+(const NumericVector& lhs, const NumericVector& rhs);

}

#endif // INCLUDED_NUM_VECTOR_H