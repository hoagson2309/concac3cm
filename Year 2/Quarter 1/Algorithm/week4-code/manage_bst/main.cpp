#include <iostream>
#include <string>
#include "bintree.h"

sax::binary_tree_node<int>* insert(sax::binary_tree_node<int>* node, int x){
    if(!node){
        return new sax::binary_tree_node<int>{x, nullptr, nullptr};
    }

    if(x < node->data){
        node->left = insert(node->left, x);
    } else if (x > node->data){
        node->right = insert(node->right, x);
    }
    //if x == node->data
    return node;
}

//remove smallest node from subtree
//return updated subtree root, and sets min_val to removed value
sax::binary_tree_node<int>* remove_min(sax::binary_tree_node<int>* node, int &min_val){
    if(node->left == nullptr){
        //this node is a minimum
        min_val = node->data;
        sax::binary_tree_node<int>* right_subtree = node->right;
        delete node;
        return right_subtree;
    }
    node->left = remove_min(node->left, min_val);
    return node;
}

//remove x from BST
sax::binary_tree_node<int>* remove(sax::binary_tree_node<int>* node, int x){
    if(!node) return nullptr;

    if(x < node->data){
        node->left = remove(node->left, x);
    } else if (x > node->data){
        node->right = remove(node->right, x);
    } else {
        //found node to remove

        //leaf node(no children) -> delete
        if(!node->left && !node->right){
            delete node;
            return nullptr;
            //only right child
        } else if (!node->left){
            sax::binary_tree_node<int>* tmp = node->right;
            delete node;
            return tmp;
            //only left child
        } else if (!node->right){
            sax::binary_tree_node<int>* tmp = node->left;
            delete node; 
            return tmp;
        } else {
            //2 children -> replace with inorder successor
            int successor_val;  //Find the inorder successor (smallest value in right subtree).
            node->right = remove_min(node->right, successor_val); 
            node->data = successor_val;
        }
    }
    return node;
}

int main() {
    /* TODO:
    Write a program that reads a binary search tree with integers from the standard input,
    followed by a command to either insert or delete an integer from the tree.
    The program should then perform the specified operation and print the resulting tree.
    */
   sax::binary_tree_node<int>* root = nullptr;
   std::string op;
   int x;

   std::cin >> root;
   std::cin >> op >> x;

   if(op == "insert"){ 
    root = insert(root, x);
   } else if (op == "remove"){
        root = remove(root, x);
   }

   std::cout << root << std::endl;
   sax::binary_tree_node<int>::cleanup(root);
    return 0;
}
