#include <iostream>
#include <string>
#include <fstream>  // for std::ifstream, std::ofstream
#include "counter.h" // for sax::counter
#include "linked_list.h"

//split to 2 list
sax::linked_list_node<std::string>* split(sax::linked_list_node<std::string>* head){
    if(!head || !head->next) return nullptr;
                                        // apple -> pear -> banana -> lemon -> nullptr
    auto slow = head;                  //slow => apple
    auto fast = head->next;            //fast => pear
    while (fast && fast->next){
        slow = slow->next;              //slow moves 1 step
        fast = fast->next->next;        //fast moves 2 steps
    }
                                                                        //fast reach nullptr first
    sax::linked_list_node<std::string>* second_half = slow->next;        //apple -> pear(slow) -> banana -> lemon -> nullptr
    slow->next = nullptr;                                     //break => apple -> pear -> nullptr
    return second_half;                                       //      => banana -> lemon -> nullptr
}

//just merge can be unsorted
sax::linked_list_node<std::string>* merge(sax::linked_list_node<std::string>* l1, sax::linked_list_node<std::string>* l2){
    sax::linked_list_node<std::string> dummy;  //fake head
    auto tail = &dummy;

    while(l1 && l2){
        sax::counter::instance().inc_comparisons();  //keep track of the number of comparisons
        if(l1->data <= l2->data){
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        } 
        tail = tail->next;
    }                                        //dummy(tail) -> apple -> banana -> grape -> orange -> peach -> pear
    tail->next = (l1) ? l1 : l2;        //for longer list, merge it in
    return dummy.next;           //skip dummy => apple -> banana -> grape -> orange -> peach -> pear
}

//recursively sort any unsorted list and then merge sublists
sax::linked_list_node<std::string>* merge_sort(sax::linked_list_node<std::string>* head){
    if(!head || !head->next) return head;

    sax::linked_list_node<std::string>* second = split(head);
    head = merge_sort(head);            //each half keep splitting until every sublist has only 1 element
    second = merge_sort(second);            

    return merge(head, second);     //then merge each list and overall 2 lists  (check again)
}  //nlogn

int main() {
    /* TODO:
        Write a program that reads the names of two files from the standard input, 
        reads the strings from the first file into a linked list, sorts the linked list using merge sort,
        and then writes the sorted strings to the second file.

        When sorting the strings, the program should count the number of comparisons performed,
        and print this count to standard output.
        
        Use the sax::counter class for this (see counter.h and counter.cpp).
    */
    std::string input_file, output_file;
    std::getline(std::cin, input_file);
    std::getline(std::cin, output_file);

    std::ifstream fin(input_file);
    if(!fin){
        std::cerr << "Error opening input file " << input_file << "\n";
        return 1;
    }

    sax::linked_list_node<std::string>* head = nullptr;
    sax::linked_list_node<std::string>* tail = nullptr;
    std::string word;
                                                        //cannot use fin >> head; cuz the text is like "apple banna orange pear" not [apple -> banna -> orange -> pear]
    while (fin >> word){
        sax::linked_list_node<std::string>* new_node = new sax::linked_list_node<std::string>();
        new_node->data = word;
        new_node->next = nullptr;

        if(!head){
            head = new_node;            //first node
            tail = head;
        } else {
            tail->next = new_node;      //append new one 
            tail = new_node;
        }
    }
    
    fin.close();

    head = merge_sort(head);

    std::ofstream fout(output_file);
    if(!fout){
        std::cerr << "Error opening output file " << output_file << "\n";
        sax::linked_list_node<std::string>::cleanup(head);
        return 1;
    }

    //write 1 word per line
    auto* curr = head;
    while(curr){
        fout << curr-> data << "\n";
        curr = curr->next;
    }
    fout.close();

    std::cout << "Comparisons: " << sax::counter::instance().comparisons() << "\n";

    sax::linked_list_node<std::string>::cleanup(head);
    return 0;
}
