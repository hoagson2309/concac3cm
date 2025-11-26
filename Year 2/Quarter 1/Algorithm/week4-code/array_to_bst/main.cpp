#include <iostream>
#include "utils.h"   // for reading vectors
#include "bintree.h" // for binary_tree_node
#include "string"
#include <vector>

sax::binary_tree_node<std::string>* build_balanced_bst(const std::vector<std::string>& arr, int left, int right){
    if(left > right) return nullptr;

    int mid = left + (right - left) / 2;  //Mathematically equivalent to (left + right)/2, but safer. won't overflow.
    sax::binary_tree_node<std::string>* node = new sax::binary_tree_node<std::string>{arr[mid], nullptr, nullptr};

    //recursivelybuild left and right subtrees
    node->left = build_balanced_bst(arr, left, mid - 1);
    node->right = build_balanced_bst(arr, mid + 1, right);

    return node;
}

int main(){
    /* TODO:
        Write a program that reads a sorted array of strings from standard input,
        constructs a balanced binary search tree containing the strings, and
        prints the tree to standard output.

        Example input:
            [apple, banana, cherry, date, elderberry, fig, grape]
        Example output:
            ((apple banana cherry) date (elderberry fig grape))
    */
    std::vector<std::string> arr;
    std::cin >> arr;

    sax::binary_tree_node<std::string>* root = build_balanced_bst(arr, 0, arr.size() - 1);

    std::cout << root << std::endl;
    sax::binary_tree_node<std::string>::cleanup(root);
    return 0;
}
