#include <iostream>
#include "linked_list.h"
#include "utils.h"   // for reading vectors

using node = sax::linked_list_node<int>;

/// @brief Splits the linked list into two lists: one containing the even values, and one containing the odd values.
/// @param head The head of the original linked list. After the function returns, this list will contain only the odd values.
/// @return The list containing the even values. The original list (pointed to by head) will contain the odd values after the function returns.
node* split_even(node*& head){
    node* even_head = nullptr;
    node* even_tail = nullptr;
    node* current = head;
    node* prev = nullptr;

    while(current != nullptr){
        if(current->data % 2 == 0){
            if(prev != nullptr){
                prev->next = current->next;
            } else {
                head = current->next;
            }
            if(even_head == nullptr){
                even_head = current;
                even_tail = current;
            } else {
                even_tail->next = current;
                even_tail = current;
            }
            node* temp = current->next; //store next node
            current->next = nullptr; //disconnect current node
            current = temp;  //move to next
        } else {
            prev = current;
            current = current->next;
        }
    }
    return even_head;

}

int main() {
    node* head = nullptr;

    // Read the binary search tree from standard input
    std::cin >> head;

    std::cout << "Input Linked List: " << head << std::endl;

    if (std::cin.fail()) {
        std::cerr << "Failed to read linked list from input." << std::endl;
        return 1;
    }

    // TODO: Split the list into odd and even
    node* even_list = split_even(head);

    std::cout << "Even Linked List: " << even_list << std::endl;
    std::cout << "Odd Linked List: " << head << std::endl;
    // Clean up memory (TODO: don't forget to clean up the new list you create as well)
    node::cleanup(head);

    return 0;
}
