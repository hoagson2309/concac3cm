#include <iostream>
#include "linked_list.h"

int main() {
    /* TODO:
        Write a program that reads a singly linked list of strings from standard input,
        followed by a string to insert into the list. The program should insert the string
        into the list such that the list remains sorted in alphabetic order. The program
        should print the updated list to standard output.

        Example input: [apple -> banana -> cherry] blueberry
        Example output: [apple -> banana -> blueberry -> cherry]
    */

    // read a singly linked list from standard input
    sax::linked_list_node<std::string>* head = nullptr;
    std::cin >> head;
    if(!std::cin){
        std::cerr << "Failed to read list from input" << std::endl;
        sax::linked_list_node<std::string>::cleanup(head);
        return 1;
    }

    //if the list is empty, the head pointer will be nullptr
    // if(head == nullptr){
    //     std::cout << "[]" << std::endl;   // CANNOT JUST RETURN [] LIKE ASSIGNMENT 0 , MUST ALLOCATE A NODE
    //     return 0;
    // }

    //read the string to insert
    std::string to_insert;
    std::cin >> to_insert;

    //if the list is empty, create the first node
    if(head == nullptr){
        head = new sax::linked_list_node<std::string>{to_insert};
        std::cout << *head << std::endl;
        sax::linked_list_node<std::string>::cleanup(head);
        return 0;
    }

    //create a sentinel node
    sax::linked_list_node<std::string> sentinel{""};  //buffer to insert node before head
    sentinel.next = head;  

    //[sentinel] → [apple] → [banana] → [cherry] -> nullptr

    //traverse the list to find insertion point
    sax::linked_list_node<std::string>* prev = &sentinel; 
    sax::linked_list_node<std::string>* current = head; //head is a pointer

    bool inserted = false; 

    while(current != nullptr){
        if(current->data == to_insert){  //if existed
            inserted = true;
            break;
        } else if (current->data > to_insert){  
            //insert new node before current node (in the middle)
            sax::linked_list_node<std::string>* new_node = new sax::linked_list_node<std::string>{to_insert};
            prev->next = new_node; 
            new_node->next = current;
            inserted = true;
            break;
        }
        prev = current;             //keep increasing until found a node to insert
        current = current->next;
    }

    //If we reached the end without inserting, insert at the end (current == NULLptr)
    if(!inserted){
        prev->next = new sax::linked_list_node<std::string>{to_insert}; 
    }
    
    //print the updated list(Skip sentinel)
    std::cout << *sentinel.next << std::endl;  // ? *

    //*sentinel.next is head, but head is apple so print the full list starting from apple  *******
    //AFTER: sentinel → [apple] → [banana] → [blueberry] → [cherry] -> nullptr

    //cleanup dynamically allocated memory
    sax::linked_list_node<std::string>::cleanup(sentinel.next); //cleanupp the whole list

    return 0;
}
