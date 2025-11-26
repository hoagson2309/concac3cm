#ifndef INCLUDED_LIBPTR_UNIQUE_PTR_H
#define INCLUDED_LIBPTR_UNIQUE_PTR_H

// You can use sax::DefaultDeleter from deleter.hpp if you are implementing the optional part
#include "deleter.hpp"

namespace sax
{
    template <typename T>
    class UniquePtr
    {   
    public:
        using Pointer = T*;
        using ElementType = T;
    
    private:
        // the real pointer
        Pointer ptr_{nullptr};

    public:
        // Constructors etc.


        // Modifiers


        // Observers


        // Pointer-like operators
    
    };
}

#endif /* INCLUDED_LIBPTR_UNIQUE_PTR_H */
