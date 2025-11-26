#include <iostream>
#include "bintree.h"
#include "node_ptr.h"

int main()
{
    /* TODO:
        Write a program that reads a binary search tree from the standard input,
        and prints the values in the tree in reverse sorted order.

        Example input: ((1 3 4) 5 (7 8 ()))
        Example output: 8 7 5 4 3 1

        Use the binary_tree_node struct from bintree.h to represent the tree. This structure already
        contains input and output operators that you can use to read (and write) trees.
    */
    sax::binary_tree_node<int>* root = nullptr;
    int k;

    //read tree and k 
    std::cin >> root;
    std::cin >> k;

    //iterate with node_ptr
    sax::node_ptr<int> it(root);
    while (it && it->data <= k){
        std::cout << it->data << " ";
        it.move_next();
    }
    std::cout << std::endl;

    sax::binary_tree_node<int>::cleanup(root);
    return 0;
}
