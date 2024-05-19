#include <iostream>
#include <queue>
#include  "Trees.h"

using namespace std;

int BST::height_balance(Node* node)
{
    if(node == NULL)
        return 0;

    return height(node->right_child) - height(node->left_child);
}

Node* BST::left_rotation(Node* node)
{
    Node* new_root = node->right_child;
    Node* new_root_left_child = new_root->left_child;


    new_root->left_child = node;
    node->right_child = new_root_left_child;

    node->height = 1 + max(height(node->left_child), height(node->right_child));
    new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

    return  new_root;
}

Node* BST::right_rotation(Node* node)
{
    Node* new_root = node->left_child;
    Node* new_root_right_child = new_root->right_child;


    new_root->right_child = node;
    node->left_child = new_root_right_child;

    node->height = 1 + max(height(node->left_child), height(node->right_child));
    new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

    return new_root;
}

Node* BST::left_right_rotation(Node* node)
{
    node->left_child = left_rotation(node->left_child);
    node = right_rotation(node);

    return node;
}

Node* BST::right_left_rotation(Node* node)
{
    node->right_child = right_rotation(node->right_child);
    node = left_rotation(node);

    return node;
}

int BST::height(Node* node)
{
    if(node == NULL)
        return 0;

    return node->height;
}

void BST::InOrder(Node* parent, Node*& lastVisited)
{
    if (parent == NULL)
        return;

    InOrder(parent->left_child, lastVisited);
    cout << parent->key << "\n";
    lastVisited = parent;
    // cout << "--- Node Data Array --- \n";
    // cout << "Births: \n";
    // printArray(parent->node_data_births);
    // cout << "Deaths: \n";
    // printArray(parent->node_data_deaths);
    InOrder(parent->right_child, lastVisited);
}

void BST::printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int nodeCount = q.size();
        while (nodeCount > 0) {
            Node* node = q.front();
            std::cout << node->key << "\t \t";
            q.pop();
            if (node->left_child != nullptr) q.push(node->left_child);
            if (node->right_child != nullptr) q.push(node->right_child);
            nodeCount--;
        }
        cout << std::endl;
    }
    cout << endl;
}

//-----------------------------------------------------------------------------------------------------//

Node* REG::newNode(population data){
    Node* newNode = new Node;

    newNode->key = data.region;
    newNode->node_data_births.resize(18);
    newNode->node_data_deaths.resize(18);

    if (data.alive == 1)
        newNode->node_data_births[data.period - 2005] = data;
    else
        newNode->node_data_deaths[data.period - 2005] = data;

    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    return (newNode);

}

Node* REG::insert(Node* parent, population key)
{
    if (parent == NULL)
        return (newNode(key));

    if ( key.region.compare(parent->key) < 0 ) // key.region < parent.
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.region.compare(parent->key) > 0 ) // key.region > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }
    // else if (key.alive == 1)
    //     parent->node_data_births[key.period - 2005] = key;
    // else
    //     parent->node_data_deaths[key.period - 2005] = key;


    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key.region.compare(parent->right_child->key) < 0)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key.region.compare(parent->left_child->key) > 0)
        parent = left_right_rotation(parent);

    else if (hb > 1)
        parent = left_rotation(parent);

    else if (hb < -1 )
        parent =  right_rotation(parent);

    return (parent);
}


Node* REG::search(Node* parent, std::string key){ //Births oriented
    cout << "\nSearching...\n";

    while(parent != nullptr)
    {
        //Entry is at right subtree
        if(key.compare(parent->key) > 0 ){ // key > parent->key
            parent = parent->right_child;
        }
            //Entry is at left subtree
        else if( key.compare(parent->key) < 0 ){ // key < parent->key
            parent = parent->left_child;
        }
            //Entry found
        else
            return parent;
    }
    //Entry not found - returning nullptr
    return nullptr;
}

void REG::editSelect(Node* node, int year, int input){
    int index = year - 2005;
    node->node_data_births[index].count = input;
    cout << "\nReconfigured data:\n" << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count [NEW]\t" << "Region" << "\n\n";
    cout << node->node_data_births[index].period << "\t\t" << node->node_data_births[index].alive << "\t\t\t\t" << node->node_data_births[index].count << "\t\t" << node->node_data_births[index].region << "\n";
}

Node* REG::deleteNode(Node* parent, std::string key)
{
    Node* deletionNode = search(parent, key);

    if (deletionNode == nullptr)
    {
        cout << "Node not found\n";
        return parent;
    }
    else
    {
        Node* lastVisited = nullptr;
        InOrder(deletionNode, lastVisited);
        if (lastVisited != nullptr)
            cout << lastVisited->key << "\n";
    }

    return deletionNode;
}


void REG::printArray(vector<population> Array)
{
    cout << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count\t\t" << "Region" << "\n\n";

    for(auto& v : Array)
    {
        cout << v.period << "\t\t" << v.alive << "\t\t\t\t" << v.count << "\t\t" << v.region << "\n";
    }

    cout << "\n";
}

//-----------------------------------------------------------------------------------------------------//

Node* PRD::newNode(population data){
    Node* newNode = new Node;

    newNode->key = data.period;
    newNode->node_data_births.resize(18);
    newNode->node_data_deaths.resize(18);

    //Here goes Content handling, contentKey: data.region

    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    return (newNode);

}

Node* PRD::insert(Node* parent, population key)
{
    if (parent == NULL)
        return (newNode(key));

    if ( key.period < parent->intkey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.period > parent->intkey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }

    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key.period < parent->right_child->intkey)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key.period > parent->left_child->intkey)
        parent = left_right_rotation(parent);

    else if (hb > 1)
        parent = left_rotation(parent);

    else if (hb < -1 )
        parent =  right_rotation(parent);

    return (parent);
}

Node* PRD::search(Node* parent, int key){ //Births oriented
    cout << "\nSearching...\n";

    while(parent != nullptr)
    {
        //Entry is at right subtree
        if(key > parent->intkey ){ // key > parent->key
            parent = parent->right_child;
        }
            //Entry is at left subtree
        else if( key < parent->intkey ){ // key < parent->key
            parent = parent->left_child;
        }
            //Entry found
        else
            return parent;
    }
    //Entry not found - returning nullptr
    return nullptr;
}

//void PRD::editSelect(Node* node, string region, int input){
//
//}

Node* PRD::deleteNode(Node* parent, int key)
{
    Node* deletionNode = search(parent, key);

    if (deletionNode == nullptr)
    {
        cout << "Node not found\n";
        return parent;
    }
    else
    {
        Node* lastVisited = nullptr;
        InOrder(deletionNode, lastVisited);
        if (lastVisited != nullptr)
            cout << lastVisited->intkey << "\n";
    }

    return deletionNode;
}

//void PRD::printArray(vector<population> Array){
//
//}

