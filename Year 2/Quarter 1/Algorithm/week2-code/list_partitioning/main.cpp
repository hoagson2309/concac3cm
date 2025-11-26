#include <iostream>
#include "linked_list.h"

int main() {
    /* TODO:
        Write a program that reads a singly linked list of strings from standard input,
        followed two antegers i and n. The program should move the first n nodes starting from index i (index 0 is the first node)
        to the front of the list. The program should print the updated list to standard output. 

        Example input: [apple -> banana -> cherry] 1 2
        Example output: [banana -> cherry -> apple]
    */
   sax::linked_list_node<std::string>* head;
   size_t low, count;    //low -> start of sublist, count -> number of ele in sublist
   std::cin >> head >> low >> count;

    if(count == 0 || head == nullptr){
        std::cout << head << std::endl;
        sax::linked_list_node<std::string>::cleanup(head);
        return 0;
    }

    if(low == 0){
        //already at the front
        std::cout << head << std::endl;
        sax::linked_list_node<std::string>::cleanup(head);
        return 0;
    }

    //find the node b4 sublist
    sax::linked_list_node<std::string>* before_sublist = head;
    for(size_t i = 0; i < low - 1; i++){  //loop until seeing the first node before sublist
        before_sublist = before_sublist->next;  //ex: low = 2 => 1 iteration => b4_sub = 1
    }

    sax::linked_list_node<std::string>* sublist_start = before_sublist->next;
    sax::linked_list_node<std::string>* sublist_end = sublist_start;
    for(size_t i = 1; i < count; i++){  //loop until the last node of sublist
        sublist_end = sublist_end->next; 
    }

    //detach sublist
    before_sublist->next = sublist_end->next;   //example: [ham -> egg -> spam -> bacon] low = 1, count = 2
                                                // => [egg->spam], [ham->bacon] => ham->next = bacon
    //move sublist to the front 
    sublist_end->next = head;   //spam->next = head, connect the end of sublist(spam) to the old head(ham)
    head = sublist_start;       //head = egg (new head)

    std::cout << head << std::endl;  //=> [egg -> spam -> ham -> bacon]

    sax::linked_list_node<std::string>::cleanup(head);

    return 0;
}
