#include "dictionary.h"

#include <stdexcept>
#include <fstream>

namespace demo
{
    std::ostream& operator<<(std::ostream& out, const Entry& entry)
    {
        out << '{' << entry.key << ": ";
        if (entry.value.size() > 40)
        {
            return out << entry.value.substr(0, 37) << "...}";
        }
        return out << entry.value << '}';
    }

    bool Dictionary::add(const std::string& key, const std::string& value)
    {

        if (contains(key))
        {
            return false;
        }

        ensure_capacity(count_ + 1);
        entries_[count_++] = {key, value};
        return true;
    }

    bool Dictionary::contains(const std::string& key) const
    {
        for (std::size_t i = 0; i < count_; ++i)
        {
            if (entries_[i].key == key)
            {
                return true;
            }
        }

        return false;
    }

    const std::string& Dictionary::at(const std::string& key) const
    {
        for (std::size_t i = 0; i < count_; ++i)
        {
            if (entries_[i].key == key)
            {
                return entries_[i].value;
            }
        }

        throw std::out_of_range("Key not found");
    }

    std::size_t Dictionary::count() const
    {
        return count_;
    }

    Entry * Dictionary::begin()
    {
        return entries_;
    }

    Entry * Dictionary::end()
    {
        return entries_ + count_;
    }

    const Entry * Dictionary::begin() const
    {
        return entries_;
    }

    const Entry * Dictionary::end() const
    {
        return entries_ + count_;
    }

    std::size_t read_from_file(const std::string& file_name, Dictionary& dict)
    {
        std::ifstream file{file_name};
        if (!file)
        {
            throw std::runtime_error("Cannot open file");
        }

        std::size_t count{0};
        std::string key;
        std::string value;

        while (file >> std::ws &&
               std::getline(file, key, ',') &&
               file >> std::ws &&
               std::getline(file, value) )
        {
            if (dict.add(key, value))
            {
                ++count;
            }
        }
        return count;
    }

    std::ostream& operator<<(std::ostream& out, const Dictionary& dict)
    {
        out << "[\n";
        for (const auto& entry : dict)
        {
            out << "  * " << entry << '\n';
        }
        out << ']';

        return out;
    }

    // Added functions
    Dictionary::Dictionary(std::size_t initial_capacity):
        capacity_{ initial_capacity },
        count_{ 0 },
        entries_{ new Entry[initial_capacity]{} }
    {}

    static const std::size_t DEFAULT_CAPACITY{ 4 };
    Dictionary::Dictionary():
        Dictionary{ DEFAULT_CAPACITY }
    {}

    Dictionary::~Dictionary()
    {
        delete[] entries_;
    }

    void Dictionary::ensure_capacity(std::size_t minimum_capacity)
    {
        if (minimum_capacity < capacity_)
        {
            return;
        }

        auto new_capacity = capacity_;
        while( new_capacity <= minimum_capacity )
        {
            new_capacity *= 2;
        }

        std::cout << "Resizing from " << capacity_ << " to " << new_capacity << '\n';
        auto array = new Entry[new_capacity]{};
        std::copy(entries_, entries_ + count_, array);

        delete[] entries_;

        entries_ = array;
        capacity_ = new_capacity;

    }
    /*
    Dictionary::Dictionary(const demo::Dictionary& other):
        capacity_{ other.capacity_ },
        count_{ other.count_ },
        entries_{ new Entry[ other.capacity_ ]{}}
    {
        std::copy(other.entries_, other.entries_ + other.count_, entries_);
    }

    Dictionary& Dictionary::operator=(const demo::Dictionary& other)
    {
       auto array = new Entry[other.capacity_]{};
       std::copy(other.entries_, other.entries_ + other.count_, array);

       delete[] entries_;

       entries_ = array;
       count_ = other.count_;
       capacity_ = other.capacity_;

       return *this;
    }
    */

    Dictionary::Dictionary(const demo::Dictionary& other):
        Dictionary{ other.capacity_ }
    {
        std::copy(other.entries_, other.entries_ + other.count_, entries_);
        // count must be adjusted because it's 0 now
        count_ = other.count_;
    }

    void Dictionary::swap(demo::Dictionary& other)
    {
        std::swap(count_, other.count_);
        std::swap(capacity_, other.capacity_);
        std::swap(entries_, other.entries_);
    }

    Dictionary& Dictionary::operator=(demo::Dictionary other)
    {
        // using copy-and-swap idiom
        swap(other);
        return *this;
    }
} // demo