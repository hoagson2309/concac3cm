#include <iostream>
#include "utils.h"
#include "bintree.h"
#include "node_ptr.h"

int main() {
    /* TODO:
        Write a program that reads two binary search trees from standard input, which represent sets of
        integers (no duplicates within each tree), and builds a vector containing the intersection of the two sets.

        The program must write the resulting vector to standard output.

        The time complexity of your program must be O(n + m), where n and m are the sizes of the two trees.

        Example input:
            ((2 3 4) 5 (6 7 8)) (3 5 10)
        Example output:
            [3, 5]
    */
    sax::binary_tree_node<int>* A = nullptr;
    sax::binary_tree_node<int>* B = nullptr;

    std::cin >> A >> B;

    sax::node_ptr<int> itA(A);
    sax::node_ptr<int> itB(B);

    std::vector<int> intersection;

    while(itA && itB){
        if(itA->data == itB->data){
            intersection.push_back(itA->data);
            itA.move_next();
            itB.move_next();
        } else if (itA->data < itB->data){
            itA.move_next();
        } else {
            itB.move_next();
        }
    }
    
    std::cout << "[";
    for (size_t i = 0; i < intersection.size(); i++){
        std::cout << intersection[i];
        if(i + 1 < intersection.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    sax::binary_tree_node<int>::cleanup(A);
    sax::binary_tree_node<int>::cleanup(B);
    return 0;
}
