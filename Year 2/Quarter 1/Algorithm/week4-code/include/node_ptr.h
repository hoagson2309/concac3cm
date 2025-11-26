#ifndef NODE_PTR_H
#define NODE_PTR_H

#include <stack>    // for std::stack
#include "bintree.h"

namespace sax {

template<typename T>
class node_ptr {
    public:
        //constructor: initialize the smallest element
        explicit node_ptr(binary_tree_node<T>* root){
            push_left_path(root);
        }

        //Arrow operator: access current node's data
        binary_tree_node<T>* operator->(){
            return current;
        }

        //Conversion to bool: true if valid
        operator bool() const{
            return current != nullptr;
        }

        //Advance to next (in-order successor)
        void move_next(){
            if(!current) return;
            // If there is a right subtree, go down its leftmost path
            if(current->right){
                push_left_path(current->right);
            } else {
                // Otherwise, backtrack using the stack
                if(!stk.empty()){
                    current = stk.top();  //top() gives you a reference to the element currently at the top of the stack, i.e. the last thing you pushed.
                    stk.pop();      //If you want to remove it, you have to call pop() separately.
                } else {
                    current = nullptr;
                }
            }
        }

    private:
        binary_tree_node<T>* current = nullptr;
        std::stack<binary_tree_node<T>*> stk;

        //Helper: push path of left children,set current
        void push_left_path(binary_tree_node<T>* node){
            while(node){
                stk.push(node);  //put an element on top of the stack. That element will be the first one you get back when you later call pop().
                node = node->left;
            }
            if(!stk.empty()){  
                current = stk.top();
                stk.pop();
            } else {
                current = nullptr;
            }
        }
};

} //namespace sax


#endif // NODE_PTR_H
