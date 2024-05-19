#ifndef TREES_H
#define TREES_H

#include    <vector>
#include    "Struct.h"
#include    <string>


class BST{

public:
    int height(Node* node);
    int height_balance(Node* node);
    Node* left_rotation(Node* node);
    Node* right_rotation(Node* node);
    Node* left_right_rotation(Node* node);
    Node* right_left_rotation(Node* node);
    void InOrder( Node* parent, Node*& lastVisited);
    void printLevelOrder(Node* root);

    virtual Node* newNode(population data) = 0;
    virtual Node* insert(Node* parent, population key) = 0;
//    virtual Node* search(Node* parent, std::string key) = 0;
//    virtual Node* deleteNode(Node* parent, std::string key) = 0;
//    virtual void editSelect(Node* node, int year, int input) = 0;
//
//    virtual void printArray(std::vector<population> Array) = 0;

};

class REG: public BST{

public:
    Node* newNode(population data);
    Node* insert(Node* parent, population key);
    Node* search(Node* parent, std::string key);
    Node* deleteNode(Node* parent, std::string key);
    void editSelect(Node* node, int year, int input);

    void printArray(std::vector<population> Array);

};

class PRD: public BST{

public:
    Node* newNode(population data);
    Node* insert(Node* parent, population key);
    Node* search(Node* parent, int key);
    Node* deleteNode(Node* parent, int key);
//    void editSelect(Node* node, std::string region, int input);

//    void printArray(std::vector<population> Array);


};


#endif