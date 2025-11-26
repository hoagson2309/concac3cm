#ifndef DEMO_06_DICTIONARY_H
#define DEMO_06_DICTIONARY_H

#include <iostream>
#include <string>

namespace demo
{

struct Entry
{
    std::string key;
    std::string value;
};

std::ostream& operator<<(std::ostream& out, const Entry& dict);


class Dictionary
{
public:
    Dictionary();
    ~Dictionary();

    Dictionary(const Dictionary& other);
    Dictionary& operator=(Dictionary other);
    void swap(Dictionary& other);

    bool add(const std::string& key, const std::string& value);

    bool contains(const std::string& key) const;

    const std::string& at(const std::string& key) const;
    std::size_t count() const;

    Entry * begin();
    Entry * end();
    const Entry * begin() const;
    const Entry * end() const;

private:

    Dictionary(std::size_t initial_capacity);

    void ensure_capacity(std::size_t minimum_capacity);
    std::size_t capacity_{0};
    std::size_t count_{0};
    Entry * entries_{nullptr};
};

std::ostream& operator<<(std::ostream& out, const Dictionary& dict);

std::size_t read_from_file(const std::string& file_name, Dictionary& dict);

} // demo

#endif //DEMO_06_DICTIONARY_H
