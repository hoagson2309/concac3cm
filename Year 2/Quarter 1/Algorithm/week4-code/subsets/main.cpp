#include <iostream>
#include <string>
#include "bintree.h" // for binary_tree_node
#include "node_ptr.h"

bool is_subset(sax::binary_tree_node<int>* A, sax::binary_tree_node<int>* B){
    sax::node_ptr<int> itA(A);
    sax::node_ptr<int> itB(B);

    while (itA){
        if(!itB) return false; //if B is exhauted but A not -> false

        if(itA->data == itB->data){  //match -> advance both
            itA.move_next();
            itB.move_next();
        } else if(itA->data > itB->data){
            itB.move_next();  //B smaller -> advance B
        } else {
            return false; //A smaller but not in B => false  
        }               //cuz both array is sorted thru node_ptr if A is smaller than B there's no chance that A will appear late in B -> cannot be a subset
    }
    return true;
}

int main() {
    /* TODO:
        Write a program that reads two binary search trees from standard input, which represent sets of
        integers (no duplicates within each tree), and checks if the first one is a subset of the second one.

        The program must output "true" if the first tree is a subset of the second one, and "false" otherwise.

        The time complexity of your program must be O(n + m), where n and m are the sizes of the two trees.
    */
    sax::binary_tree_node<int>* A = nullptr;
    sax::binary_tree_node<int>* B = nullptr;

    std::cin >> A >> B;

    bool result = is_subset(A, B);
    std::cout << (result ? "true" : "false") << std::endl;

    sax::binary_tree_node<int>::cleanup(A);
    sax::binary_tree_node<int>::cleanup(B);
    return 0;
}
