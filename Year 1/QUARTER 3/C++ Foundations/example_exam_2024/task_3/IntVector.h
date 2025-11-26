#ifndef INCLUDED_INT_VECTOR_H
#define INCLUDED_INT_VECTOR_H

#include <cstddef>
#include <iostream>

namespace exam
{
    class IntVector
    {
    public:
        IntVector();
        //rules of three
        IntVector(const IntVector& other);
        IntVector& operator=(const IntVector& other);
        //destructor
        ~IntVector();


        void push_back(long value);
        std::size_t size() const;
        long operator[](std::size_t index) const;
        long * begin();
        long * end();
        const long * begin() const;
        const long * end() const;

        void sort();
        void unique();
        
    private:
        
        std::size_t size_;
        std::size_t capacity_;
        long* data_;

        void resize(size_t new_capacity);
        void ensure_capacity();
    };
    std::ostream& operator<<(std::ostream& os, const IntVector& v);
}


#endif // INCLUDED_INT_VECTOR_H
