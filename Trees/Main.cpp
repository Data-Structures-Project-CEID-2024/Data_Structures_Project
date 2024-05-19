#include "Input.h"
#include "Struct.h"
#include "Trees.h"

using namespace std;

int main()
{
    Input input = Input();
    // input.printArray(input.input);

    int size = input.input.size();


    BST* bst = new REG();
    Node* root = bst->insert(NULL, input.input[0]);

    for (int i = 1; i < size; i++)
    {
        root = bst->insert(root ,input.input[i]);
    }

    Node* lastVisited = nullptr;
    bst->InOrder(root, lastVisited);
    cout << endl;
    bst->printLevelOrder(root);


    // // AVL Insertion Test
//    BST test;
//    population testA = {2005, 1, "A", 1};
//    population testB = {2006, 1, "B", 1};
//    population testC = {2007, 1, "C", 1};
//    population testD = {2008, 1, "D", 1};

    // // Left Rotation Test
    // Node* rootAVL1 = test.newNode_REG(testA);
    // rootAVL1 = test.insert(rootAVL1, testB);
    // rootAVL1 = test.insert(rootAVL1, testC);

    // test.printLevelOrder(rootAVL1);

    // // Right Rotation Test
    // Node* rootAVL2 = test.newNode_REG(testC);
    // rootAVL2 = test.insert(rootAVL2, testB);
    // rootAVL2 = test.insert(rootAVL2, testA);

    // test.printLevelOrder(rootAVL2);

    // // Left Right Rotation Test
    // Node* rootAVL3 = test.newNode_REG(testA);
    // rootAVL3 = test.insert(rootAVL3, testC);
    // rootAVL3 = test.insert(rootAVL3, testB);

    // test.printLevelOrder(rootAVL3);

    // // Right Left Rotation Test
    // Node* rootAVL4 = test.newNode_REG(testC);
    // rootAVL4 = test.insert(rootAVL4, testA);
    // rootAVL4 = test.insert(rootAVL4, testB);

    // test.printLevelOrder(rootAVL4);


    // AVL Deletion Test
//    Node* rootAVL = test.newNode(testA);
//    rootAVL = test.insert(rootAVL, testC);
//    rootAVL = test.insert(rootAVL, testB);
//    rootAVL = test.insert(rootAVL, testD);



//    test.printLevelOrder(rootAVL);
//    test.deleteNode(rootAVL, "C");
//    test.printLevelOrder(rootAVL);

    return 0;

}