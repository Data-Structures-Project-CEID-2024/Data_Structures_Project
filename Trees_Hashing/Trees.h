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
    void InOrder( Node* parent);


    // virtual Node* newNode(population data) = 0;
    // virtual Node* insert(Node* parent, population key) = 0;
//    virtual Node* search(Node* parent, std::string key) = 0;
//    virtual Node* deleteNode(Node* parent, std::string key) = 0;
//    virtual void editSelect(Node* node, int year, int input) = 0;
//
//    virtual void printArray(std::vector<population> Array) = 0;
    // virtual void printLevelOrder(Node* root) = 0;

};

class REG: public BST{
    public:
        // Constructors 
        REG()
        {
            // cout << "REG Constructor\n";
        }

        ~REG()
        {
            // cout << "REG Destructor\n";
        }
        Node* newNode(population data);
        Node* insert(Node* parent, population key);
        Node* searchSingular(Node* parent, std::string key);
        Node* search(Node* parent, std::string RegionKey, int PeriodKey);
        Node* deleteNode(Node* parent, std::string key);
        void  editSelect(Node* parent, std::string RegionKey, int PeriodKey, int newCount);
        void  printLevelOrder(Node* root);
        

};

class NumericalAVL: public BST
{

    public:
        Node* newNode(const population data);
        Node* insert(Node* parent, int key, population data);
        Node* search(Node* parent, int key);
        Node* deleteNode(Node* parent, int key);
        void delelteTree(Node* root);
        void editSelect(Node* parent, int key, int newCount);
        void printLevelOrder(Node* root);
        Node* findMin(Node* root);
        Node* findMax(Node* root);
};



#endif