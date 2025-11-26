# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 12/3/2025

# LABS
```cpp
//WORD_COUNTER.H
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

//WORD_COUNTER.CPP
#include "word_counter.h"


namespace counts
{
    WordCounter::WordCounter():
        entries_{ new Entry[INITIAL_CAPACITY] }, // TODO 4: once you replace `std::array` with a dynamic array, initialize entries_ properly
        count_{ 0 },
        capacity_{ INITIAL_CAPACITY }
    {}

    // TODO 5: implement the destructor
    WordCounter::~WordCounter(){
        delete[] entries_; //release the dynamically allocated array to prevent leaks
    }

    // TODO 7: implement ensure_capacity function
    bool WordCounter::ensure_capacity(std::size_t minimum_capacity){
        if(minimum_capacity <= capacity_){ // checks whether the current capacity of the array is already sufficient to meet the requested minimum_capacity
            return false; //no resizing needed
        }

        //resize the array
        std::size_t new_capacity = capacity_;
        while(new_capacity < minimum_capacity){
            new_capacity *= 2; //double the size of capacity
        }

        Entry* new_entries = new Entry[new_capacity]; //allocate new array
        //std::copy(start_source, end_source, start_destination);
        //It copies all elements in the range [start_source, end_source) to the destination, starting at start_destination.
        std::copy(entries_, entries_ + count_, new_entries); //copy the existing entries

        delete[] entries_;  //free old array to avoid memory leak
        entries_ = new_entries; //point to the new array
        capacity_ = new_capacity; //update capacity 

        return true;
    }

    //increment fuction
    void WordCounter::increment(const std::string& word)
    {
        // if word already in counter, increment its count
        
        if (auto entry = find(word); entry) // Entry* entry = find(word); // Declare and initialize entry
        {                                    //if (entry) { // Check if entry is not nullptr
            ++entry->count; //increment count if  word exists
        }
        else
        {
            if (count_ >= capacity_)
            {
                // TODO 8: implement ensure_capacity function and call it here
                // instead of returning
                ensure_capacity(capacity_ + 1); //ensure there's enough space 
            }                                   //ensures the entries_ array has enough space to add one more element. If the array is full (count_ == capacity_),
            // entries_[count_].word = word;
            // entries_[count_].count = 1;
            // ++count_;
            entries_[count_++] = { word, 1 };   
        }
    }

    //begin function (non-const)
    Entry* WordCounter::begin()
    {
        // TODO 3a: once you have removed `std::array` from the class, change to: 
        // return entries_;

        return entries_; //return the start of the dynamic array
    }

    //begin function (const)
    const Entry* WordCounter::begin() const
    {
        // TODO 3b: once you have removed `std::array` from the class, change to: 
        // return entries_;

        return entries_; //return the start of the dynamic array
    } 

    //decrement function
    void WordCounter::decrement(const std::string& word){
        if (auto entry = find(word); entry) // Entry* entry = find(word); // Declare and initialize entry
        {                                   //if (entry) { // Check if entry is not nullptr
            if (entry->count > 1)
            {
                --entry->count; //decrement count if word exists and count > 1
            }
        }
    }

    //get function
    std::size_t WordCounter::get(const std::string& word) const
    {
        if (auto entry = find(word); entry)
        {
            return entry->count; //return count if word exists
        }
        return 0; //word not found
    }

    //end function (non-const)
    Entry* WordCounter::end()
    {
        return entries_ + count_; //return the end of the dynamic array (entries is a pointer point to the very first index of the array)
    }

    //end function (const)
    const Entry* WordCounter::end() const
    {
        return entries_ + count_; //return the end of the dynamic array(entries is a pointer point to the very first index of the array)
    }
    
    //size function
    std::size_t WordCounter::size() const
    {
        return count_; //return the number of entries
    }
    
    //find function (non-const)
    Entry* WordCounter::find(const std::string& word)
    {
        for (std::size_t i = 0; i < count_; ++i)
        {
            if (entries_[i].word == word)
            {
                return &entries_[i]; //return the pointer to the entry if found
            }
        }
        return nullptr;  //word not found
    }
    //find function (const)
    const Entry* WordCounter::find(const std::string& word) const
    {
        for (std::size_t i = 0; i < count_; ++i)
        {
            if (entries_[i].word == word)
            {
                return &entries_[i];// Return pointer to the entry if found
            }
        }
        return nullptr;//word not found
    }
}
```