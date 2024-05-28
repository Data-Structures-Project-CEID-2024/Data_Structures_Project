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
    // cout << "--- Node Data Array --- \n";
    // cout << "Births: \n";
    // printArray(parent->node_data_births);
    // cout << "Deaths: \n";
    // printArray(parent->node_data_deaths);
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


Node* REG::newNode(population data)
{
    Node* newNode = new Node;

    newNode->key = data.region;

    // For Searching because we return the Node that has the Region and we need to have
    // the data_count of the period that we are searching for.
    newNode->intKey = 0;
    newNode->data_count = 0;  

    PRD period_tree;
    newNode->node_data_births = NULL;
    newNode->node_data_deaths = NULL;

    if (data.alive == 1)
        newNode->node_data_births = period_tree.insert(NULL,  data);
    else
        newNode->node_data_deaths = period_tree.insert(NULL, data);

    newNode->node_parent = NULL;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    return (newNode);

}


Node* REG::insert(Node* parent, population key)
{
    PRD period_tree;

    if (parent == NULL)
    {
        Node * node = newNode(key);
        node->node_parent = parent;
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
    // else if (key.alive == 1 && parent->node_data_births == NULL)
    // {
    //     parent->node_data_births = period_tree.insert(parent->node_data_births, key);
    // }
    // else if (key.alive == 0 && parent->node_data_deaths == NULL)
    // {
        
    // }
    else if (key.alive == 1) 
    {
        parent->node_data_births = period_tree.insert(parent->node_data_births, key);
        
    } 
    else 
    {
        parent->node_data_deaths = period_tree.insert(parent->node_data_deaths, key);
        // parent->node_data_deaths[key.period - 2005] = key;
    }
   
    
    
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

Node* nextInOrderNode(Node* node)
{
    if (node == NULL)
        return NULL;
    
    nextInOrderNode(node->left_child);

    if (node->left_child != NULL)
        return node->left_child;
    
    return node;
}


Node* REG::deleteNode(Node* parent, string key)
{
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
    else {
        
        if (parent->left_child == nullptr) 
        {
            Node* temp = parent->right_child;
            delete parent;
            return temp;
        }
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
        parent->right_child = deleteNode(parent->right_child, temp->key);
        
    }
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
            PRD period;
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
            PRD period;
            period.editSelect(parent->node_data_births, PeriodKey, newCount);
            
            return;
        }
    }
    cout << "Region: " << RegionKey << " not found\n";
}

//-----------------------------------------------------------------------------------------------------//PRD

Node* PRD::newNode(population data)
{
    Node* newNode = new Node;

    newNode->intKey = data.period;
    newNode->data_count = data.count;

    //Content handling for printf's Erwthma A
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;
    return (newNode);

}

Node* PRD::insert(Node* parent, population key)
{
    if (parent == NULL)
        return (newNode(key));

    if ( key.period < parent->intKey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.period > parent->intKey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }

    parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

    int hb = height_balance(parent);


    if (hb > 1 && key.period < parent->right_child->intKey)
        parent = right_left_rotation(parent);

    else if (hb < -1 && key.period > parent->left_child->intKey)
        parent = left_right_rotation(parent);

    else if (hb > 1)
        parent = left_rotation(parent);

    else if (hb < -1 )
        parent =  right_rotation(parent);

    return (parent);
}

Node* PRD::search(Node* parent, int key)
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

void PRD::editSelect(Node* parent, int key, int newCount)
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
        InOrder(deletionNode);
        if (lastVisited != nullptr)
            cout << lastVisited->intKey << "\n";
    }

    return deletionNode;
}

//void PRD::printArray(vector<population> Array){
//
//}

void PRD::printLevelOrder(Node* root) 
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



//-----------------------------------------------------------------------------------------------------//COUNT

Node* COUNT::newNode(population data)
{

    Node* newNode = new Node;

    newNode->intKey = data.count;

    REG reg;
  
     if (data.alive == 1)
        newNode->node_data_births = reg.insert(NULL,  data);
    else
        newNode->node_data_deaths = reg.insert(NULL, data);

    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->height = 1;

    return (newNode);

}

Node* COUNT::insert(Node* parent, population key)
{
    REG region_tree ;

    if (parent == NULL)
    {
        Node * node = newNode(key);
        node->node_parent = parent;
        return (node);
    }

    if ( key.count < parent->intKey) // key.period < parent
    {
        parent->left_child = insert(parent->left_child, key);
    }
    else if ( key.count > parent->intKey  ) // key.period > parent
    {
        parent->right_child = insert(parent->right_child, key);
    }

    else if (key.alive == 1 )
    {
        parent->node_data_births = region_tree.insert(parent->node_data_births, key);
        
    } 
    else 
    {
        parent->node_data_deaths = region_tree.insert(parent->node_data_deaths, key);
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

Node* COUNT::search(Node* parent, int key)
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

// void COUNT::editSelect(Node* node, int counts, string region, int input){
//     REG* reg = new REG();
//     Node* cptr = search(node, counts);
//     Node* rptr = reg->search(cptr->birth_data, region);
//     rptr->data = input;
//     return;
// }

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
        InOrder(deletionNode);
        if (lastVisited != nullptr)
            cout << lastVisited->intKey << "\n";
    }

    return deletionNode;
}

void COUNT::printLevelOrder(Node* root) 
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

Node* COUNT::findMin(Node* root) 
{
    if (root->left_child != nullptr) {
        cout << "\nAGAIN: " << root->intKey;
        return findMin(root->left_child);
    }
    return root;
}

Node* COUNT::findMax(Node* root)
{
    if (root->right_child != nullptr) {
        cout << "\nAGAIN: " << root->intKey;
        return findMin(root->right_child);
    }
    return root;
}











