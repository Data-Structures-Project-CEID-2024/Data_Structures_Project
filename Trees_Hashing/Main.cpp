#include "Input.h"
#include "Struct.h"
#include "Trees.h"
#include "Hashing.h"
#include "Menu.h"
#include <list>

using namespace std;

int main()
{

    // Menu* menu = new Menu();
    // delete menu;

    Input input = Input();
    // input.printArray(input.input);
    
    // int size = input.input.size();

    NumericalAVL* counts = new NumericalAVL();
    Node* root0 = counts->insert(NULL, input.input[0].count , input.input[0]);
    for (int i = 1; i < 20 /* temporary */; i++)
    {
        if(input.input[i].alive == 1){
            root0 = counts->insert(root0, input.input[i].count ,input.input[i]);
        }
    }
    cout << endl;

    Node* cptr = counts->findMin(root0);
    cout << "\nmin key is" << cptr->intKey;
    for (population it : cptr->dataVector) {
        std::cout << it.region << " ";
    }
    std::cout << std::endl;

    // // 1. Insertion with AVL Rotation and InOrder//

    // REG   reg;
    // Node* root = reg.insert(NULL, input.input[0]);

    // for (int i = 1; i < size; i++)
    // {
    //     root = reg.insert(root ,input.input[i]);
    // }
    // reg.InOrder(root);
    // reg.printLevelOrder(root);

    // cout << endl;
    // // 2. Search with Region and Year of Births //

    // PRD prd;
    // prd.printLevelOrder(root->node_data_births);
    // Node* node_search = NULL;
    
    // for (int i = 0; i < int(input.input.size()); i++)
    // {
    //     node_search = reg.search(root, input.input[i].region, input.input[i].period);

    //     if (node_search == NULL)
    //     {
    //         cout << "Node not found\n";
    //     }
    //     else
    //     {
    //         cout << "i: "<< i << " YES\n";
    //         // cout << "Node found\n";
    //         // cout << "Region: " << node_search->key << endl;
    //         // cout << "Period: " << node_search->intKey << endl;
    //         // cout << "Count: " << node_search->data_count << endl;
    //     }
    // }
    // cout << endl;
    // // 3. Edit Select //
    
    // reg.editSelect(root, "Bay of Plenty region", 2005, 1000);
    // node_search = reg.search(root, "Bay of Plenty region", 2005);

    // if (node_search == NULL)
    // {
    //     cout << "Node not found\n";
    // }
    // else
    // {
    //     cout << "Node found\n";
    //     cout << "Region: " << node_search->key << endl;
    //     cout << "Period: " << node_search->intKey << endl;
    //     cout << "Count: " << node_search->data_count << endl;
    // }
    // cout << endl;
    // // 4. Deletion //

    // root = reg.deleteNode(root, "0");
    // root = reg.deleteNode(root, "Marlborough region");
    // root = reg.deleteNode(root, "New Zealand");
    // root = reg.deleteNode(root, "Auckland region");
    // root = reg.deleteNode(root, "Canterbury region");
    // root = reg.deleteNode(root, "Hawke's Bay region");
    // root = reg.deleteNode(root, "Nelson region");
    
    // reg.InOrder(root);
    // cout << endl;
    // reg.printLevelOrder(root);


    // //------ Hashing --------//
    
    // Hashing hash = Hashing(11);

    // vector <Node*> buckets[hash.m];
    // vector<population> array = input.input;


    // for (const auto& population : array)
    // {
    //     cout << "Region: " << population.region <<  "\t\t\tPeriod:  "  << population.period;
    //     hash.insertElement(population, buckets);
    // }



    // cout << endl << endl;

    // PRD prd;
    // for (int i=0; i < hash.m; i++)
    // {
    //     cout <<"Avl Trees in chain "<< i <<": " << (buckets[i]).size() << endl;
        
    //     for (const auto& Node: buckets[i])
    //     {
    //         cout << Node->key<<endl;
    //         prd.printLevelOrder(Node->node_data_births);
    //     }
    //     // for (const auto& item : buckets[i]) {
    //     //     cout << item->key << " "; // Assuming 'region' is a member of population struct
    //     // }
    //         cout << endl;
    // }

    // hash.searchElement("Auckland region", 2006, buckets);
    // hash.modifyElement("Auckland region", 2006, buckets, 666);
    // hash.searchElement("Auckland region", 2006, buckets);
    // hash.deleteElement("Auckland region", buckets);
    // hash.searchElement("Auckland region", 2006, buckets);
    // free(root);


    // // AVL Insertion Test
    // BST test;
    // population test0 = {2005, 1, "0", 1};
    // population testA = {2005, 1, "A", 1};
    // population testB = {2006, 1, "B", 1};
    // population testC = {2007, 1, "C", 1};
    // population testD = {2008, 1, "D", 1};
    // population testE = {2009, 1, "E", 1};
    // population testF = {2010, 1, "F", 1};
    // population testG = {2011, 1, "G", 1};
    // population testH = {2012, 1, "H", 1};

    // // Left Rotation Test
    // Node* rootAVL1 = test.newNode(testA);
    // rootAVL1 = test.insert(rootAVL1, testB);
    // rootAVL1 = test.insert(rootAVL1, testC);

    // test.printLevelOrder(rootAVL1);

    // // Right Rotation Test
    // Node* rootAVL2 = test.newNode(testC);
    // rootAVL2 = test.insert(rootAVL2, testB);
    // rootAVL2 = test.insert(rootAVL2, testA);

    // test.printLevelOrder(rootAVL2);

    // // Left Right Rotation Test
    // Node* rootAVL3 = test.newNode(testA);
    // rootAVL3 = test.insert(rootAVL3, testC);
    // rootAVL3 = test.insert(rootAVL3, testB);

    // test.printLevelOrder(rootAVL3);

    // // Right Left Rotation Test
    // Node* rootAVL4 = test.newNode(testC);
    // rootAVL4 = test.insert(rootAVL4, testA);
    // rootAVL4 = test.insert(rootAVL4, testB);

    // test.printLevelOrder(rootAVL4);


    // AVL Deletion Test
    // Node* rootAVL = test.newNode(testA);
    // rootAVL = test.insert(rootAVL, testC);
    // rootAVL = test.insert(rootAVL, testB);
    // rootAVL = test.insert(rootAVL, testD);

    // // rootAVL = test.insert(rootAVL, test0);
    // rootAVL = test.insert(rootAVL, testE);
    // // rootAVL = test.insert(rootAVL, testF);

    // test.printLevelOrder(rootAVL);
    
    // rootAVL = test.deleteNode(rootAVL, "A");
    // test.printLevelOrder(rootAVL);

    // free(rootAVL);

    // rootAVL = test.newNode(testA);
    // rootAVL = test.insert(rootAVL, testC);
    // rootAVL = test.insert(rootAVL, testB);
    // rootAVL = test.insert(rootAVL, testD);

    // // rootAVL = test.insert(rootAVL, test0);
    // rootAVL = test.insert(rootAVL, testE);
    // rootAVL = test.insert(rootAVL, testF);
    // rootAVL = test.insert(rootAVL, testG);
    // rootAVL = test.insert(rootAVL, testH);

    // test.printLevelOrder(rootAVL);
    
    
    // rootAVL = test.deleteNode(rootAVL, "A");
    // rootAVL = test.deleteNode(rootAVL, "C");
    // test.printLevelOrder(rootAVL);


    // free(rootAVL);

    // rootAVL = test.newNode(testA);
    // rootAVL = test.insert(rootAVL, testC);
    // rootAVL = test.insert(rootAVL, testB);
    // rootAVL = test.insert(rootAVL, testD);

    // // rootAVL = test.insert(rootAVL, test0);
    // rootAVL = test.insert(rootAVL, testE);
    // rootAVL = test.insert(rootAVL, testG);
    // rootAVL = test.insert(rootAVL, testH);
    // rootAVL = test.insert(rootAVL, testF);

    // test.printLevelOrder(rootAVL);
    
    
    // rootAVL = test.deleteNode(rootAVL, "A");
    // rootAVL = test.deleteNode(rootAVL, "C");
    // test.printLevelOrder(rootAVL);
    // free(root);
    // free(rootAVL); 


    //   A          A                   C
    //      B   ->     C     - >    A       B
    //   C                B
 
    return 0;

}