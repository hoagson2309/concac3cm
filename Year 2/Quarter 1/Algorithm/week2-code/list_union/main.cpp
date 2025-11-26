#include <iostream>
#include "linked_list.h"

void appendNode(sax::linked_list_node<int>** head, sax::linked_list_node<int>** tail, sax::linked_list_node<int>* node){
    node->next = nullptr; //no new node, only relink existing ones
    if(*head == nullptr){
        *head = *tail = node;
    } else {
        (*tail)->next = node; //append new node after current last node
        *tail = node;       //move tail pointer to the new last node
    }
}

int main() {
    /* TODO:
        Write a program that reads two singly linked lists of integers from standard input.
        The program should build a new list that forms the union of the two input lists, by
        rearranging the nodes of the input lists (i.e., do not create new nodes).

        The input lists are sorted in ascending order and do not contain duplicates.
        The output list should also be sorted in ascending order and should not contain duplicates.

        The program should print the resulting list to standard output.

        Example input: [1 -> 2 -> 3] [2 -> 3 -> 4]
        Example output: [1 -> 2 -> 3 -> 4]
    */
    sax::linked_list_node<int>* head1 = nullptr;
    sax::linked_list_node<int>* head2 = nullptr;

    std::cin >> head1 >> head2;

    sax::linked_list_node<int>* a = head1;
    sax::linked_list_node<int>* b = head2;

    sax::linked_list_node<int>* head = nullptr;  //head of union list
    sax::linked_list_node<int>* tail = nullptr;  //tail of union list

    while(a && b){
        if(a->data < b->data){
            sax::linked_list_node<int>* next = a->next;
            appendNode(&head, &tail, a);
            a = next;
        } else if (a->data > b->data){
            sax::linked_list_node<int>* next = b->next;
            appendNode(&head, &tail, b);
            b = next;
        } else {
            sax::linked_list_node<int>* nextA = a->next;
            sax::linked_list_node<int>* nextB = b->next;
            appendNode(&head, &tail, a);  // a == b -> only append 1
            sax::linked_list_node<int>* temp = b;
            b = nextB;
            delete temp;      //free memory for the duplicate node
            a = nextA;
        }
    }

    //if a longer
    while(a){
        sax::linked_list_node<int>* next = a->next;
        appendNode(&head, &tail, a);
        a = next;
    }
    //if b longer
    while(b){
        sax::linked_list_node<int>* next = b->next;
        appendNode(&head, &tail, b);
        b = next;
    }

    std::cout << head << std::endl;
    sax::linked_list_node<int>::cleanup(head);

    return 0;
}
