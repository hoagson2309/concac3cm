#include "dictionary.h"

void Dictionary::add(const std::string& key, const std::string& value) {
    if (contains(key)) return;
    if (size_ < capacity_) {
        pairs_[size_].key = key;
        pairs_[size_].value = value;
        ++size_;
    }
}

bool Dictionary::contains(const std::string& key) const {
    for (int i = 0; i < size_; ++i) {
        if (pairs_[i].key == key) return true;
    }
    return false;
}

std::string Dictionary::get(const std::string& key) const {
    for (int i = 0; i < size_; ++i) {
        if (pairs_[i].key == key) return pairs_[i].value;
    }
    return "";
}

int Dictionary::size() const {
    return size_;
}

std::string Dictionary::key(int index) const {
    if (index >= 0 && index < size_) {
        return pairs_[index].key;
    }
    return "";
}