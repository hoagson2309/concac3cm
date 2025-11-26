#include <iostream>
#include "bintree.h"
#include <stack> // for std::stack
#include <utility> //std::pair

int main() {
    /* TODO:
        Write a program that reads a binary tree from standard input, and prints its height to standard output.
        Your program must not use recursion.

        Example input: ((2 3 4) 5 (6 7 8))
        Example output: 3
    */
    sax::binary_tree_node<int>* root = nullptr;
    std::cin >> root;

    if(!root){
        std::cout << 0 << std::endl; //empty tree has height 0
        return 0;
    }

    std::stack<std::pair<sax::binary_tree_node<int>*, int>> stk;
    stk.push({root, 1});// root is at depth 1
    int max_height = 0;

    while(!stk.empty()){
        auto [node, depth] = stk.top();
        stk.pop();

        if(node){
            //update max height
            if (depth > max_height) max_height = depth;

            //push children  with incrmented height
            if(node->left) stk.push({node->left, depth + 1});
            if(node->right) stk.push({node->right, depth + 1});
        }
    }
    std::cout << max_height<< std::endl;
    sax::binary_tree_node<int>::cleanup(root);
    return 0;
}
