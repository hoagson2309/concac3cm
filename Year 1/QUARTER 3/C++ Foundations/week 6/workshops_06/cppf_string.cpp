#include "cppf_string.h"
#include <cstring>          //for std::strlen, std::strcpy, std::strcat, std::strncpy, std::strstr
#include <algorithm>        //for std::min 
#include <iostream>         //for std::istream

namespace cppf{

    //default constructor
    String::String() : storage_(new char[1]), length_(0) {
        storage_[0] = '\0';     //initialize with an empty string (only null terminator)
    }
    // Notes:
    // - Creates an empty string with a single null terminator.
    // - `storage_` is dynamically allocated to hold at least 1 character.
    // - `length_` is set to 0 because the string is empty.


    //constructor from C-string
    String::String(const char* str) : storage_(nullptr), length_(0) {
        if(str) {
            length_ = std::strlen(str);         //calculate the length of the input C-string
            storage_ = new char[length_ + 1];   //allocate memory for the string + null terminator
            std::strcpy(storage_, str);         //copy the input C-string into storage_
        } else {
            storage_ = new char[1];             //handle null input by creating the empty string
            storage_[0] = '\0';
        }
    }
    //Notes:
    // -Initialize the string with the content of a C-string
    // -Handle null input by creating an empty string
    // -Uses 'std::strlen' to determine the length of the input string

    //constructor from std::string 
    String::String(const std::string& str) : storage_(new char[str.size() + 1]), length_(str.size()){
        std::strcpy(storage_, str.c_str());   // copy the content of std::string into storage_
    }

    //copy constructor
    String::String(const String& other) : storage_(new char[other.length_ + 1]), length_(other.length_){
        std::strcpy(storage_, other.storage_);      //deep copy the content of the other string
    }

    //Notes:
    // -create a deep copy of another 'cppf::String' object
    // -Ensures that the new object has its own independent copy of the data 

    //destructor
    String::~String() {
        delete[] storage_;  //free the dynamically allocated memory to prevent memory leaks
    }

    //copy assignment operator
    String& String::operator=(const String& other){
        if(this != &other){                                     //check for self-assignment
            char* new_storage = new char[other.length_ + 1];    //allocate new memory (allocate memory with pointer )
            std::strcpy(new_storage, other.storage_);           //copy the content of the other string
            delete[] storage_;                  //free old memory
            storage_ = new_storage;             //update the pointer to the new memory
            length_ = other.length_;            //update the length
        }
        return *this;                   //return the current object for chaining
    }

    //Notes:
    // -Handles self-assignment to avoid unnecessary work
    // -performs a deep copy of the other string's data
    // -frees the old memory to avoid memory leaks

    //Accessors
    std::size_t String::size() const{
        return length_;
    }

    bool String::empty() const{
        return length_ == 0;
    }

    const char* String::c_str() const{
        return storage_;            //return the pointer to the internal C-string
    }

    char* String::data() {
        return storage_;        //return the pointer to the internal C-string
    }

    //const-overloaded functions
    char String::at(std::size_t index) const{
        if(index >= length_){
            throw std::out_of_range("Index out of range");  //- Throws `std::out_of_range` if the index is invalid.
        }
        return storage_[index];         // return the character at the specified index
    }  
    //Notes:
    // -Provides bounds-checked read access to characters.

    char& String::at(std::size_t index){
        if (index >= length_) {
            throw std::out_of_range("Index out of range");
        }
        return storage_[index];
    }

    char String::operator[](std::size_t index) const {
        return storage_[index];
    }
    // Notes:
    // - Provides unchecked read access to characters.
    // - Faster than `at()` but unsafe for invalid indices.
    

    char& String::operator[](std::size_t index) {
        return storage_[index];
    }


    const char* String::begin() const {
        return storage_;    // Return a pointer to the first character
    }
    // Notes:
    // - Provides read-only access to the beginning of the string.


    char* String::begin() {
        return storage_;
    }   
    // Notes:
    // - Provides read-write access to the beginning of the string.

    const char* String::end() const {
        return storage_ + length_;          // Return a pointer to one past the last character
    }
    // Notes:
    // - Provides read-only access to the end of the string.

    char* String::end() {
        return storage_ + length_;
    }
    // Notes:
    // - Provides read-write access to the end of the string.

    //modifiers
    void String::append(const char* str){
        if(str){
            std::size_t new_length = length_ + std::strlen(str);    //calculate the new length
            resize(new_length);               //resize the storage to accommodate the new content
            std::strcat(storage_, str);       //append the input string to the current string            
            length_ = new_length;             //update the length
        }
    }
    // Notes:
    // - Appends a C-string to the current string.
    // - Uses `resize()` to ensure sufficient memory is available.

    void String::append(const String& str){
            append(str.c_str());    // Append the content of another `cppf::String`
        }
        // Notes:
        // - Calls the `append(const char*)` function to avoid code duplication.
        
        void String::append(const std::string& str) {
            append(str.c_str());    //append the content of a 'std::string
        }
        // Notes:
        // - Calls the `append(const char*)` function to avoid code duplication.

        void String::append(char c){
            char temp[2] = {c, '\0'};   //Create a temporary C-string with the single character
            append(temp);               //append the temporary C-string
        }
        // Notes:
        // - Appends a single character by converting it to a C-string.

        //*****************CAC FUNCTION DUOI 'append' LA CALL LAI FUNCTION DAU void append(const string& str) DE MODIFY**********************

        void String::clear(){
            resize(0);          //resize the storage to 0
            storage_[0] = '\0'; //ensure the string is null-terminated
            length_ = 0;        //update the length to 0
        }

        //optional functions
        String String::substr(std::size_t start, std::size_t length) const{
            if (start >= length_){
                throw std::out_of_range("Start index out of range");    //throw an exception for the invalid start index
            }
            std::size_t actual_length = std::min(length, length_ - start);  //calculate the actual length of the substring
            String result;
            result.resize(actual_length);                                       //resize the result string hold the substring with actual length
            std::strncpy(result.storage_, storage_ + start, actual_length);     //copy the substring    
            result.storage_[actual_length] = '\0';                      //ensure the result is null-terminated
            return result;
        }

        String String::substr(std::size_t start) const {
            if (start >= length_){
                throw std::out_of_range("Start index out of range");    //throw an exception for the invalid start index
            }
            return substr(start, length_ - start);              //extract a substring from the start to the end of the string
        }

        bool String::starts_with(const String& prefix) const{
            if(prefix.length_ > length_){           //// The prefix cannot be longer than the string
                return false;
            }
            return std::strncmp(storage_, prefix.storage_, prefix.length_) == 0; // Compare the prefix
        }
        // Notes:
        // - Checks if the string starts with the specified prefix.

        bool String::ends_with(const String& suffix) const{
            if(suffix.length_ > length_){               // The suffix cannot be longer than the string
                return false;
            }
            return std::strncmp(storage_ + length_ - suffix.length_, suffix.storage_, suffix.length_) == 0; // Compare the suffix
        }
        // Notes:
        // - Checks if the string ends with the specified suffix.


        bool String::contains(const String& needle) const{
            return find(needle) != npos;            // Check if the needle is found in the string (!= npos => pos => found)
        }


        std::size_t String::find(const String& needle) const{
            return find(needle, 0);                 // Start searching from the beginning
        }
        // Notes:
        // - Finds the first occurrence of the needle in the string.


        std::size_t String::find(const String& needle, std::size_t start) const{
            if(start >= length_ || needle.length_ > length_- start){
                return npos;        // Return `npos` if the needle cannot fit in the remaining string
            }
            const char* pos = std::strstr(storage_ + start, needle.storage_);   // Search for the needle
            return pos ? pos - storage_ : npos;     // Return the index or `npos` if not found
        }

        // Notes:
        // - Finds the first occurrence of the needle starting from `start`.
        // - Uses `std::strstr` for efficient searching.

        //Private helper function
        void String::resize(std::size_t new_length) {
            char* new_storage = new char [new_length + 1];         //allocate new memory
            std::strncpy(new_storage, storage_, new_length);       //copy the old content   
            new_storage[new_length] = '\0';                         //ensure the new string is null-terminated
            delete[] storage_;                                      //free the old memory
            storage_ = new_storage;                                 //update the pointer to the new memory
            length_ = new_length;                                   //update the length
        }    
        // Notes:
    // - Resizes the internal storage to accommodate a new length.
    // - Copies the old content and ensures null termination.
        
        // Stream extraction operator
    std::istream& operator>>(std::istream& in, String& str) {
        std::string temp;
        in >> temp;                 //read from the input stream
        str = String(temp);         //assign the content to the 'cppf::String' object
        return in;
    }
    // Notes:
    // - Reads a word from the input stream and assigns it to the string.
    // - Uses `std::string` for intermediate storage.

} // namespace cppf





