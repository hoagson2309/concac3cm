#include <iostream>
#include "linked_list.h"

sax::linked_list_node<std::string>* reverse_recursive(sax::linked_list_node<std::string>* head){
    //if empty
    if(head == nullptr || head->next == nullptr){
        return head;
    }

    sax::linked_list_node<std::string>* new_head = reverse_recursive(head->next);
    
    //put current head at the end of the reversed list
    head->next->next = head;
    head->next = nullptr;

    return new_head;
}

// AT FIRST JUST LOOP CALLING
// reverse_recursive(1) calls reverse_recursive(2)
// reverse_recursive(2) calls reverse_recursive(3)
// reverse_recursive(3) calls reverse_recursive(4)
// reverse_recursive(4) hits base case → returns 4

// AFTER THAT START TO UNWINDING SINCE HEAD->NEXT is NULLPTR (4->next == nullptr => base case => start) 
// Call head   Action	                Resulting list
// 4	 4	   base case	            4 -> nullptr
// 3	 3	   4->next = 3, 3->next=0	4 -> 3 -> nullptr
// 2	 2	   3->next = 2, 2->next=0	4 -> 3 -> 2 -> nullptr
// 1	 1	   2->next = 1, 1->next=0	4 -> 3 -> 2 -> 1 -> nullptr

int main() {
    /* TODO:
        Write a program that reads a singly linked list of strings from standard input,
        reverses the list using recursion, and prints the reversed list to standard output.

        Example input: [apple -> banana -> cherry -> blueberry]
        Example output: [blueberry -> cherry -> banana -> apple]
    */
    sax::linked_list_node<std::string>* head = nullptr;
    std::cin >> &head;

    head = reverse_recursive(head);
    std::cout << head << std::endl;

    sax::linked_list_node<std::string>::cleanup(head);
    return 0;
}
