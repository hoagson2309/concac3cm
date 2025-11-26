#ifndef INCLUDED_WORD_COUNTER_H
#define INCLUDED_WORD_COUNTER_H

#include <array>
#include <string>

namespace counts
{

    struct Entry
    {
        std::string word;
        std::size_t count;
    };



    class WordCounter
    {
    public:
        WordCounter();  //constructor
        // TODO 2: add the destructor declaration here
        ~WordCounter(); //destructor (Add destructor for RAII)

        void increment(const std::string& word);
        void decrement(const std::string& word);
        std::size_t get(const std::string& word) const;

        Entry * begin();
        const Entry * begin() const;

        Entry * end();
        const Entry * end() const;
        
        std::size_t size() const;
        
    private:
        // TODO 6: uncomment the following declaration and implement it in word_counter.cpp

/*
        /// @brief Resizes the dynamic entries_ array to the specified minimum capacity if needed
        /// @param minimum_capacity the minimum capacity of the dynamic entries_ array
        /// @return true if the capacity was increased, false if it was already sufficient
        
*/
        bool ensure_capacity(std::size_t minimum_capacity); //uncomment and implement

        static const std::size_t INITIAL_CAPACITY = 128;

        Entry* find(const std::string& word);
        const Entry* find(const std::string& word) const;

        // TODO 1: replace `std::array` with a dynamic array of `Entry` objects (still called `entries_`)
        
        // std::array<Entry, INITIAL_CAPACITY> entries_; (remove and replace this)
        Entry * entries_; //DYNAMIC ARRAY

        std::size_t count_;
        std::size_t capacity_{INITIAL_CAPACITY};
    };
}


#endif // INCLUDED_WORD_COUNTER_H