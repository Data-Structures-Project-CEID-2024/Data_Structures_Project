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
     cout << "--- Node Data Array --- \n";
     cout << "Births: \n";
     printArray(parent->node_data_births);
     cout << "Deaths: \n";
     printArray(parent->node_data_deaths);
    InOrder(parent->right_child, lastVisited);
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

//-----------------------------------------------------------------------------------------------------//REG

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

void REG::printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    int i = 0;
    while (!q.empty()) {
        int nodeCount = q.size();
        cout<< "\n[Level " << i++ << "]\n";
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

//-----------------------------------------------------------------------------------------------------//COUNT

Node* COUNT::newNode(population data){
    Node* newNode = new Node;

    newNode->intKey = data.count;

    REG* reg = new REG();
    newNode->birth_data = reg->newNode(data);
    newNode->death_data = reg->newNode(data);


    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    delete reg;
    return (newNode);

}

Node* COUNT::insert(Node* parent, population key)
{
    REG* reg = new REG();

    if (parent == NULL){
        Node* ptr = newNode(key);
        ptr->node_parent = parent;
        Node* newContent = reg->insert(ptr->birth_data,key);
        newContent->data = key.period;

        delete reg;
        return (ptr);
    }

    if ( key.count < parent->intKey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.count > parent->intKey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }

     else if (key.alive == 1 && parent->birth_data != nullptr){

        parent->birth_data = reg->insert(parent->birth_data, key);
        parent->birth_data->data = key.period;
     }
    else if (key.alive == 0 && parent->birth_data != nullptr){
        parent->birth_data = reg->insert(parent->death_data, key);
        parent->birth_data->data = key.period;
     }

    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key.count < parent->right_child->intKey)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key.count > parent->left_child->intKey)
        parent = left_right_rotation(parent);

    else if (hb > 1)
        parent = left_rotation(parent);

    else if (hb < -1 )
        parent =  right_rotation(parent);

    delete reg;
    return (parent);
}

Node* COUNT::search(Node* parent, int key){ //Births oriented
    cout << "\nSearching...\n";

    while(parent != nullptr)
    {
        //Entry is at right subtree
        if(key > parent->intKey ){ // key > parent->key
            parent = parent->right_child;
        }
            //Entry is at left subtree
        else if( key < parent->intKey ){ // key < parent->key
            parent = parent->left_child;
        }
            //Entry found
        else
            return parent;
    }
    //Entry not found - returning nullptr
    return nullptr;
}

void COUNT::editSelect(Node* node, int counts, string region, int input){
    REG* reg = new REG();
    Node* cptr = search(node, counts);
    Node* rptr = reg->search(cptr->birth_data, region);
    rptr->data = input;
    return;
}

Node* COUNT::deleteNode(Node* parent, int key)
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
            cout << lastVisited->intKey << "\n";
    }

    return deletionNode;
}

void COUNT::printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    int i = 0;
    while (!q.empty()) {
        int nodeCount = q.size();
        cout<< "\n[Level " << i++ << "]\n";
        while (nodeCount > 0) {
            Node* node = q.front();
            std::cout << node->intKey << "\t\t";
            q.pop();
            if (node->left_child != nullptr) q.push(node->left_child);
            if (node->right_child != nullptr) q.push(node->right_child);
            nodeCount--;
        }
        cout << std::endl;
    }
    cout << endl;
}

Node* COUNT::findMin(Node* root) {
    if (root->left_child != nullptr) {
        cout << "\nAGAIN: " << root->intKey;
        return findMin(root->left_child);
    }
    return root;
}

Node* COUNT::findMax(Node* root) {
    if (root->right_child != nullptr) {
        cout << "\nAGAIN: " << root->intKey;
        return findMax(root->right_child);
    }
    return root;
}

void COUNT::show(Node* root){
    if(root->left_child != nullptr && root->right_child != nullptr){
        cout << "\n\t" << root->intKey << "\n" << root->left_child->intKey << "\t\t" << root->right_child->intKey << "\n";
        show(root->left_child);
        show(root->right_child);
    }
    else return;
}

//-----------------------------------------------------------------------------------------------------//PRD

Node* PRD::newNode(population data){
    Node* newNode = new Node;

    newNode->intKey = data.count;

    //Content handling for printf's Erwthma

    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    return (newNode);

}

Node* PRD::insert(Node* parent, population key)
{
    if (parent == NULL)
        return (newNode(key));

    if ( key.count < parent->intKey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.count > parent->intKey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }

    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key.count < parent->right_child->intKey)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key.count > parent->left_child->intKey)
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
        if(key > parent->intKey ){ // key > parent->key
            parent = parent->right_child;
        }
            //Entry is at left subtree
        else if( key < parent->intKey ){ // key < parent->key
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
            cout << lastVisited->intKey << "\n";
    }

    return deletionNode;
}

//void PRD::printArray(vector<population> Array){
//
//}

void PRD::printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    int i = 0;
    while (!q.empty()) {
        int nodeCount = q.size();
        cout<< "\n[Level " << i++ << "]\n";
        while (nodeCount > 0) {
            Node* node = q.front();
            std::cout << node->intKey << "\t\t";
            q.pop();
            if (node->left_child != nullptr) q.push(node->left_child);
            if (node->right_child != nullptr) q.push(node->right_child);
            nodeCount--;
        }
        cout << std::endl;
    }
    cout << endl;
}