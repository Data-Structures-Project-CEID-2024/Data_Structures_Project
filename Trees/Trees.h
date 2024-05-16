#ifndef TREES_H
#define TREES_H

#include    <vector>
#include    "Struct.h"
#include    <string>


class BST{
    public:

        Node* newNode(population data);
        Node* insert(Node* parent, population key);
        Node* Search(Node* parent, std::string key);
        void printSelect(Node* node, int year);
        void editSelect(Node* node, int year, int input);
        void InOrder( Node* parent );
        void printArray(std::vector<population> Array);
};

#endif