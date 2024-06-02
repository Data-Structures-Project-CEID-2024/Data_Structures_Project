#include <iostream>
#include <queue>
#include  "Trees.h"


using namespace std;



void BST::InOrder(Node* parent)
{
    if (parent == NULL)
        return;

    InOrder(parent->left_child);
    cout << parent->key << "\n";
    InOrder(parent->right_child);
}

void printArray(vector<population> Array)
{
    cout << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count\t\t" << "Region" << "\n\n";

    for(auto& v : Array)
    {
        cout << v.period << "\t\t" << v.alive << "\t\t\t\t" << v.count << "\t\t" << v.region << "\n";
    }


    cout << "\n";
}    


int BST::height(Node* node)
{
    if(node == NULL)
        return 0;
    
    return node->height;
}

int BST::height_balance(Node* node)
{
    if(node == NULL)
        return 0;
    
    return height(node->right_child) - height(node->left_child);
}


Node* BST::left_rotation(Node* node)
{
    // New Root is the right child of the OLD root
    Node* new_root = node->right_child;

    // New Root's ex left child becomes the OLD root's right child
    Node* new_root_left_child = new_root->left_child;

    
    // New Root's left child is the OLD root
    new_root->left_child = node;
    node->right_child = new_root_left_child;
    
    // Update the height of the nodes
    node->height = 1 + max(height(node->left_child), height(node->right_child));
    new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

    return  new_root;
}

Node* BST::right_rotation(Node* node)
{
    // New Root is the left child of the OLD root
    Node* new_root = node->left_child;

    // New Root's ex right child becomes the OLD root's left child
    Node* new_root_right_child = new_root->right_child;

    // New Root's right child is the OLD root
    new_root->right_child = node;
    node->left_child = new_root_right_child;

    // Update the height of the nodes
    node->height =  1 + max(height(node->left_child), height(node->right_child));
    new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

    return new_root;
}

Node*  BST::left_right_rotation(Node* node)
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

//-----------------------------------------------------------------------------------------------------//REG

void REG::printLevelOrder(Node* root)
{
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


Node* REG::newNode(population data)
{
    Node* newNode = new Node;

    // Key is the Region in REG Trees
    newNode->key = data.region;

    // For Searching because we return the Node that has the Region and we need to have
    // the data_count of the period that we are searching for.
    newNode->intKey = 0;
    newNode->data_count = 0;  

    NumericalAVL period_tree;
    newNode->node_data_births = NULL;
    newNode->node_data_deaths = NULL;

    // Creating Either Births or Deaths AVL
    if (data.alive == 1)
        newNode->node_data_births = period_tree.insert(NULL, data.period , data);
    else
        newNode->node_data_deaths = period_tree.insert(NULL, data.period ,data);

    // Necessary Initializations
    newNode->node_parent = NULL;
    newNode->left_child = NULL;
    newNode->right_child = NULL;

    newNode->height = 1;

    return (newNode);

}


Node* REG::insert(Node* parent, population key)
{
    NumericalAVL period_tree;

    if (parent == NULL)
    {
        Node * node = newNode(key);
        return (node);
    }    
    
    if ( key.region.compare(parent->key) < 0 ) // key.region < parent.
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.region.compare(parent->key) > 0 ) // key.region > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }
    else if (key.alive == 1) //In Case of Births, add to the Births AVL
    {
        parent->node_data_births = period_tree.insert(parent->node_data_births, key.period ,key);
    }   
    else // In Case of Deaths, add to the Deaths AVL
    {
        parent->node_data_deaths = period_tree.insert(parent->node_data_deaths, key.period , key);
    }
   
    
    // Update the height of the parent
    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    // Get the Height Balance of the parent = height(right) - height(left)
    int hb = height_balance(parent);

    // 4 Cases for Rotation

    // Right Left Rotation: The newNode is one the right subtree AND on the left of parents' right subtree 
    if (hb > 1 && key.region.compare(parent->right_child->key) < 0)
        parent = right_left_rotation(parent);

    // Left Right Rotation: The newNode is one the left subtree AND on the right of parents' left subtree
    else if (hb < -1 && key.region.compare(parent->left_child->key) > 0)
        parent = left_right_rotation(parent);

    // Left Rotation: The newNode is on the right subtree AND on the right of parents' right subtree
    else if (hb > 1)
        parent = left_rotation(parent);

    // Right Rotation: The newNode is on the left subtree AND on the left of parents' left subtree
    else if (hb < -1 )
        parent =  right_rotation(parent);

    // Return the pointer to the new Parent
    return (parent);

}

Node* nextInOrderNode(Node* node)
{
    if (node == NULL)
        return NULL;
    
    nextInOrderNode(node->left_child);

    if (node->left_child != NULL)
        return node->left_child;
    
    return node;
}

Node* REG::searchSingular(Node* parent, string key){
    while(parent != nullptr)
    {
        //Entry is at right subtree
        if(key.compare(parent->key) > 0 ){ // key > parent->key
            parent = parent->right_child;
        }
            //Entry is at left subtree
        else if(key.compare(parent->key) < 0 ){ // key < parent->key
            parent = parent->left_child;
        }
            //Entry found
        else
            return parent;
    }
    //Entry not found - returning nullptr
    return nullptr;
}

Node* REG::deleteNode(Node* parent, string key)
{

    NumericalAVL period_tree;

    if (parent == nullptr) {
        return parent;
    }

    
    if (key.compare(parent->key) < 0 ) {
        parent->left_child = deleteNode(parent->left_child, key);
        // parent->left_child->node_parent = parent;
    }
    
    else if (key.compare(parent->key) > 0) {
        parent->right_child = deleteNode(parent->right_child, key);
    }
    // Key is Equal to parent->key
    else 
    {
        // Parent has Only Right Child   
        if (parent->left_child == nullptr) 
        {
            // Delete the Births AVL
            if (parent->node_data_births != NULL)
                period_tree.delelteTree(parent->node_data_births);

            // Delete the Deaths AVL
            if (parent->node_data_deaths != NULL)
                period_tree.delelteTree(parent->node_data_deaths);

            Node* temp = parent->right_child;
            delete parent;
            return temp;
        }
        // Parent has Only Left Child
        else if (parent->right_child == nullptr)
        {   
            // Delete the Births AVL
            if (parent->node_data_births != NULL)
                period_tree.delelteTree(parent->node_data_births);
                
            // Delete the Deaths AVL
            if (parent->node_data_deaths != NULL)
                period_tree.delelteTree(parent->node_data_deaths);

            Node* temp = parent->left_child;
            delete parent;
            return temp;
        }

        // Delete the Births AVL
        if (parent->node_data_births != NULL)
            period_tree.delelteTree(parent->node_data_births);
        
        // Delete the Deaths AVL
        if (parent->node_data_deaths != NULL)
            period_tree.delelteTree(parent->node_data_deaths);

        // Node with two children, get the in-order successor
        Node* temp = nextInOrderNode(parent->right_child);

        parent->key = temp->key;
        parent->height = temp->height;
        // Delete the in-order successor
        parent->right_child = deleteNode(parent->right_child, temp->key);
        
    }
    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    // Rebalance the tree
    int hb = height_balance(parent);

    if (hb > 1 && height_balance(parent->right_child) >= 0)
        parent = left_rotation(parent);

    else if (hb < -1 && height_balance(parent->left_child) <= 0)
        parent = right_rotation(parent);


    else if (hb > 1 && height_balance(parent->right_child) < 0)
    {
        parent = right_left_rotation(parent);
    }
    else if (hb < -1 && height_balance(parent->left_child) > 0)
    {
        parent = left_right_rotation(parent);
    }

    return parent;
}




Node* REG::search(Node* parent, std::string RegionKey, int PeriodKey)
{ 
    //Births oriented
    
    while(parent != nullptr)
    {
        if(RegionKey.compare(parent->key) > 0 ){ // key > parent->key
            parent = parent->right_child;
        }
        else if( RegionKey.compare(parent->key) < 0 ){ // key < parent->key
            parent = parent->left_child;
        }
        else
        {
            NumericalAVL period;
            Node* count_births = period.search(parent->node_data_births, PeriodKey);
            
            if (count_births == NULL)
            {
                cout << "Data was not Found in that Period \n";
                return nullptr;
            }

            parent->intKey = count_births->intKey;
            parent->data_count = count_births->data_count;
            return parent;
        }
            
    }
    //Entry not found - returning nullptr
    return nullptr;
}

void REG::editSelect(Node* parent, std::string RegionKey, int PeriodKey, int newCount)
{
    
    while(parent != nullptr)
    {
        if(RegionKey.compare(parent->key) > 0 ){ // key > parent->key
            parent = parent->right_child;
        }
        else if( RegionKey.compare(parent->key) < 0 ){ // key < parent->key
            parent = parent->left_child;
        }
        else
        {
            NumericalAVL period;
            period.editSelect(parent->node_data_births, PeriodKey, newCount);
            
            return;
        }
    }
    cout << "Region: " << RegionKey << " not found\n";
}

//-----------------------------------------------------------------------------------------------------//NumericalAVL

Node* NumericalAVL::newNode(population data) {
    Node* newNode = new Node;

    newNode->intKey = data.period;
    newNode->data_count = data.count;
    newNode->dataVector.push_back(data);

    newNode->left_child = nullptr;
    newNode->right_child = nullptr;
    newNode->height = 1;

    return newNode;
}

Node* NumericalAVL::insert(Node* parent, int key, population data)
{
   

    if (parent == NULL)
        return (newNode(data));

    if ( key < parent->intKey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key, data);
    }
    else if ( key > parent->intKey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key, data);
    }

    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key < parent->right_child->intKey)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key > parent->left_child->intKey)
        parent = left_right_rotation(parent);

    else if (hb > 1)
        parent = left_rotation(parent);

    else if (hb < -1 )
        parent =  right_rotation(parent);

    return (parent);
}

Node* NumericalAVL::search(Node* parent, int key)
{ 
    //Births oriented

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

void NumericalAVL::editSelect(Node* parent, int key, int newCount)
{

    while(parent != nullptr)
    {
        if(key > parent->intKey ){ // key > parent->key
            parent = parent->right_child;
        }
        else if( key < parent->intKey ){ // key < parent->key
            parent = parent->left_child;
        }
        else
        {
            parent->data_count = newCount;
            return;
        }    
    }

    cout << "Period: " << key << " not found\n";
}

void NumericalAVL::delelteTree(Node* root)
{

    Node* nextInOrder = nextInOrderNode(root);
    while (nextInOrder != NULL)
    {
        root = deleteNode(root, nextInOrder->intKey);
        nextInOrder = nextInOrderNode(root);
    }

}

Node* NumericalAVL::deleteNode(Node* parent, int key)
{
    if (parent == nullptr) {
        return parent;
    }

    
    if ( key < parent->intKey )
    {
        parent->left_child = deleteNode(parent->left_child, key);
    }
    
    else if ( key > parent->intKey ) {
        parent->right_child = deleteNode(parent->right_child, key);
    }
    // Key is Equal to parent->key
    else {
        // Parent has Only Right Child
        if (parent->left_child == nullptr) 
        {
            Node* temp = parent->right_child;
            delete parent;
            return temp;
        }
        // Parent has Only Left Child
        else if (parent->right_child == nullptr)
        {   
            Node* temp = parent->left_child;
            delete parent;
            return temp;
        }

        // Node with two children, get the in-order successor
        Node* temp = nextInOrderNode(parent->right_child);

        parent->key = temp->key;
        parent->height = temp->height;

        // Delete the in-order successor
        parent->right_child = deleteNode(parent->right_child, temp->intKey);
        
    }
    // Update the height of the parent
    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);

    if (hb > 1 && height_balance(parent->right_child) >= 0)
        parent = left_rotation(parent);

    else if (hb < -1 && height_balance(parent->left_child) <= 0)
        parent = right_rotation(parent);


    else if (hb > 1 && height_balance(parent->right_child) < 0)
    {
        parent = right_left_rotation(parent);
    }
    else if (hb < -1 && height_balance(parent->left_child) > 0)
    {
        parent = left_right_rotation(parent);
    }

    return parent;
}

void NumericalAVL::printLevelOrder(Node* root) 
{
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

Node* NumericalAVL::findMin(Node* root) {
    if (root->left_child != nullptr) {
        return findMin(root->left_child);
    }
    return root;
}

Node* NumericalAVL::findMax(Node* root) {
    if (root->right_child != nullptr) {
        return findMax(root->right_child);
    }
    return root;
}














