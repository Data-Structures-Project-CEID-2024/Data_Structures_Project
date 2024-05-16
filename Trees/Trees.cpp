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
        parent->node_data_deaths[key.period - 2005] = key;
    

    return (parent);
}

Node* BST::Search(Node* parent, string key){ //Births oriented
    cout << "\nSearching...\n";
    Node* current = parent;
    while(current->left_child != nullptr || current->right_child != nullptr){
        //Entry is at right subtree
        if(key.compare(current->key) > 0 ){
            current = current->right_child;
        }
        //Entry is at left subtree
        else if( key.compare(current->key) < 0 ){
            current = current->left_child;
        }
        //Entry found
        else{
            return current;
        }

    }
    //Entry not found - returning nullptr
    return nullptr;
}

void BST::printSelect(Node* node, int year){
    int index = year - 2005;
    cout << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count\t\t" << "Region" << "\n\n";
    cout << node->node_data_births[index].period << "\t\t" << node->node_data_births[index].alive << "\t\t\t\t" << node->node_data_births[index].count << "\t\t" << node->node_data_births[index].region << "\n";
}

void BST::editSelect(Node* node, int year, int input){
    int index = year - 2005;
    node->node_data_births[index].count = input;
    cout << "\nReconfigured data:\n" << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count [NEW]\t" << "Region" << "\n\n";
    cout << node->node_data_births[index].period << "\t\t" << node->node_data_births[index].alive << "\t\t\t\t" << node->node_data_births[index].count << "\t\t" << node->node_data_births[index].region << "\n";
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



