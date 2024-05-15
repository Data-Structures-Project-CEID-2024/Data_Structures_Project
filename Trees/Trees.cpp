#include <iostream>
#include  "Trees.h"

using namespace std;

Node* BST::newNode(population data)
{
    Node* newNode = new Node;

    (newNode->key) = data.region;
    (newNode->node_data_births).resize(18);
    (newNode->node_data_deaths).resize(18);
    
    if (data.alive == 1)
        (newNode->node_data_births)[data.period - 2005] = data;
    else
        (newNode->node_data_deaths)[data.period - 2005] = data;

    (newNode->left_child) = NULL;
    (newNode->right_child) = NULL;

    return (newNode);

}

Node* BST::insert(Node* parent, population key)
{
    if (parent == NULL)
        return (newNode(key));
    
    if ( key.region.compare(parent->key) < 0 ) // key.region <= parent.
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.region.compare(parent->key) > 0 ) // key.region > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }
    else if (key.alive == 1)
        parent->node_data_births[key.period - 2005] = key;
    else
        parent->node_data_births[key.period - 2005] = key;
    

    return (parent);
}



void BST::InOrder( Node* parent )
{
   if ( parent == NULL )
        return;
    
    InOrder(parent->left_child);
    cout << parent->key << "\n";
    cout << "--- Node Data Array --- \n";
    cout << "Births: \n";
    printArray(parent->node_data_births);
    cout << "Deaths: \n";
    printArray(parent->node_data_deaths);
    InOrder(parent->right_child);
}

void BST::printArray(vector<population> Array)
{
    cout << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count\t\t" << "Region" << "\n\n";

    for(auto& v : Array)
    {
        cout << v.period << "\t\t" << v.alive << "\t\t\t\t" << v.count << "\t\t" << v.region << "\n";
    }


    cout << "\n";
}    



