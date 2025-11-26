#include <iostream>
#include "utils.h"
#include <vector>
#include <string>
#include <bits/hash_bytes.h>

using namespace std;

struct string_hash{
    size_t operator()(const string& str) const{
        return std::_Hash_bytes(str.data(), str.size(), static_cast<size_t>(0xc70f6907UL));
    }
};

int main() {
    /* TODO:
        Write a program that inputs an integer followed by a list of strings (given as a comma-separated list
        between square brackets, e.g. [apple, banana, cherry], use the utils.h header to read this array into a vector).

        The list represents the strings to be inserted into a hash table that uses linear probing for collision
        resolution, and the integer represents the number of slots in the hash table.

        The program must insert the strings into the hash table in the order they are given, and print the
        resulting hash table as a comma-separated list between square brackets, where empty slots are
        represented by the string "EMPTY".

        The hash table must implement a *set*, meaning that duplicate strings should not be inserted multiple
        times. In other words, if the same string appears more than once in the input list, it should only
        appear once in the output hash table.

        You must use the std::hash<std::string> struct from the C++ Standard Library to compute the hash value
        of a string. When determining whether a string is already present in the hash table, you must not search
        the entire table. Instead, you should use the same probing sequence that would be used for insertion,
        stopping when you either find the string or reach an empty slot.

        Example input:
            ((2 3 4) 5 (6 7 8)) (3 5 10)
        Example output:
            [3, 5]
    */

    // Hint: write a function to find an empty slot using linear probing
    int table_size;
    char c;
    cin >> table_size >> c;
    vector<string> table(table_size, "EMPTY"); //table(5, "EMPTY") => [EMPTY, EMPTY, EMPTY, EMPTY, EMPTY]
    string word;

    string_hash hasher;

    while(cin >> word){
        if(word.back() == ',') word.pop_back();  //check for "[" first
        if(word.back() == ']') word.pop_back();

        size_t index = hasher(word) % table_size;  //tryna find index in a table ( size_t index = string_hash{}(str) % table_size; )

        for(int i = 0; i < table_size; i++){
            size_t probe = (index + i) % table_size;  //wrap around the table check for empty slot

            if(table[probe] == "EMPTY"){
                table[probe] = word;
                break;
            } else if (table[probe] == word){
                //if duplicate => ignore
                break;
            }
        }
        if(word.back() == ']') break;
    }
    cout << "[";
    for(int i = 0; i < table_size; i++){
        cout << table[i];
        if(i != table_size - 1) cout << ", ";
    }
    cout << "]" << endl;
    return 0;
}

