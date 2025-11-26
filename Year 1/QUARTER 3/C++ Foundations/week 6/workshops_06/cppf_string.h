#ifndef CPPF_STRING_H
#define CPPF_STRING_H

#include <cstddef>  // For std::size_t
#include <string>
#include <stdexcept>

namespace cppf {

class String {
public:
    //constructor
    String();
    String(const char* str);
    String(const std::string& str);
    String(const String& other);

    //destructor
    ~String();

    //copy assignment operator
    String& operator=(const String& other);

    //Accessors
    std::size_t size() const;
    bool empty() const;
    const char* c_str() const;
    char* data();

    //const-overloaded functions
    char at(std::size_t index) const;
    char& at(std::size_t index);
    char operator[](std::size_t index) const;
    char& operator[](std::size_t index);
    const char* begin() const;
    char* begin();
    const char* end() const;
    char* end();

    //modifiers
    void append(const char* str);
    void append(const String& str);
    void append(const std::string& str);
    void append(char c);
    void clear();

    //optional functions
    String substr(std::size_t start, std::size_t length) const;
    String substr(std::size_t start) const;
    bool starts_with(const String& prefix) const;
    bool ends_with(const String& suffix) const;
    bool contains(const String& needle) const;
    std::size_t find(const String& needle) const;
    std::size_t find(const String& needle, std::size_t start) const;

    //static constant
    static const std::size_t npos = -1;

private:
    char* storage_;
    std::size_t length_;

    void resize(std::size_t new_length);
};

//stream extraction operator
std::istream& operator>>(std::istream& in, String& str);

} //namespace cppf

#endif //CPPF_STRING_H