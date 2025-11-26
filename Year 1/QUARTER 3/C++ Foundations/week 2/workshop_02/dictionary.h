#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <array>
#include <string>

struct KeyValue {
    std::string key;
    std::string value;
};

struct Dictionary {
    static constexpr int capacity_ = 100;
    std::array<KeyValue, capacity_> pairs_;
    int size_ = 0;

    void add(const std::string& key, const std::string& value);
    bool contains(const std::string& key) const;
    std::string get(const std::string& key) const;
    int size() const;
    std::string key(int index) const;
};

#endif // DICTIONARY_H