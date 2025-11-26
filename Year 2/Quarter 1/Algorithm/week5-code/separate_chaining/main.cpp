#include <iostream>
#include "utils.h"
#include <vector>
#include <forward_list>
#include <bits/hash_bytes.h>

using namespace std;

struct string_hash{
    size_t operator()(const string& str) const {
        return std::_Hash_bytes(str.data(), str.size(), static_cast<size_t>(0xc70f6907UL));
    }
};

//insert with separate chaining(prepending)
void insert_string(vector<forward_list<string>>& table, const string& word, string_hash& hasher){
    size_t index = hasher(word) % table.size();

    //check for duplicate
    for(auto& s : table[index]){
        if(s == word) return;
    }
    table[index].push_front(word); //prepending
}

int main()
{
    /* TODO:
        Write a program that reads a integer followed by a list of strings from its standard input (given as a
        comma-separated list between square brackets, e.g. `[apple,banana,cherry]` - see week 1).

        The list represents the strings to be inserted into a hash table that uses *separate chaining* for
        collision resolution, and the integer represents the number of slots in the hash table.

        The program must insert the strings into the hash table in the order they are given, and print the
        resulting hash table as a comma-separated list between square brackets, where each slot is printed
        as a linked list in the form `[<string1> -> <string2> -> ...]` (empty slots will be represented by
        a pair of brackets, i.e. "[]").

        The hash table must implement a *set*, meaning that duplicate strings should not be inserted multiple
        times. In other words, if the same string appears more than once in the input list, it should only
        appear once in the output hash table.

        To determine the index for a string, you *must* use the `std::hash<std::string>` struct from the C++
        Standard Library to compute the hash value of the string.

        When determining whether a string is already present in the hash table, you must not search the entire
        table. Instead, you should use the same probing sequence that would be used for insertion, stopping
        when you either find the string or reach the end of the linked list.
    */

    // Hint: use a vector of singly linked lists as the underlying data structure for the hash table.
    int k, n;
    vector<string> words;
    cin >> k >> words >> n;

    string_hash hasher; 
    //step 1 build initial table
    vector<forward_list<string>> table(k);   //using forward_list because it's -> (forward_list), not <-> (list)
    for(auto& word : words){   //word from input
        insert_string(table, word, hasher);
    }

    //step 2 rehash into new table
    vector<forward_list<string>> new_table(n);
    for(auto& bucket : table){  
        for(auto& word : bucket){ //word from last table
            insert_string(new_table, word, hasher);
        }       
    }

    //step 3: print the final rehashed table
    cout << new_table << endl;
    return 0;
}
