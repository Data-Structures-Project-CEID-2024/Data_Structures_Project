#include "Hashing.h"
using namespace std;

Hashing::Hashing(int Chains)
{
    this->m = Chains; //prime number of buckets
    this->AvlTree = REG();
}

void Hashing::insertElement(population p, vector<Node*>* buckets)
{


    int sum=0;
    for(char c : p.region) 
    {
        sum += static_cast<int>(c); // Convert char to ASCII value and add to sum
    }

    int index  = sum % m;
    bool found = false;
    //bucket[index] -> chain
    for (auto& node : buckets[index])
    {
        //linear search to find the avl tree with the right region
        if (node->key == p.region)
        {
                node = AvlTree.insert(node, p);
                found = true;
                break;
        }
    }
    //if not found create a new vector with only the population struct and push it back to the chain
    if (found==false)
    {
        Node * newRegion = AvlTree.insert(NULL, p);
        buckets[index].push_back(newRegion);
    }


}
void Hashing::searchElement(string Region, int Period, vector<Node*>* buckets)
{   
    NumericalAVL prd =  NumericalAVL();
    int index = hashFunction(Region);
    bool found = false;
    // bucket[index] -> chain
    for (auto& node : buckets[index])
    {
        //linear search to find the avl tree with the right region
        if (node->key == Region)
        {
            Node* tempNode = node->node_data_births;
            tempNode = prd.search(tempNode, Period);
            if (tempNode == NULL)
            {
                cout << "Period not found" << endl;
            }
            else
            {
                cout << "Region: " << node->key << endl;
                cout << "Period: " << tempNode->intKey << endl;
                cout << "Count: " << tempNode->data_count << endl;
            }

            found = true;
            break;
        }
    }
    //if not found create a new vector with only the population struct and push it back to the chain
    if (found==false)
    {
        cout << "Region not found" << endl;
    }
}
void Hashing::deleteElement(string Region, vector<Node*>* buckets)
{
    REG reg;
    NumericalAVL prd;
    int index = hashFunction(Region);
     bool found = false;
     // bucket[index] -> chain
     for (auto& node : buckets[index])
     {
         //linear search to find the avl tree with the right region
         if (node->key == Region)
         {
                Node* tempNode = node->node_data_births;
                prd.delelteTree(tempNode);
                reg.deleteNode(node, Region);
                found = true;
                break;
        }
    }
    //if not found create a new vector with only the population struct and push it back to the chain
    if (found == false)
    {
        cout << "Region not found" << endl;
    }
}
void Hashing::modifyElement(string Region, int  Period, vector<Node*>* buckets, int newCount)
{
    NumericalAVL prd;
     int index = hashFunction(Region);
     bool found = false;
     // bucket[index] -> chain
     for (auto& node : buckets[index])
     {
         //linear search to find the avl tree with the right region
         if (node->key == Region)
         {
                Node* tempNode = node->node_data_births;
                prd.editSelect(tempNode, Period, newCount);

                if (tempNode == NULL)
                {
                    cout << "Period not found" << endl;
                }
                
                found = true;
                break;
        }
    }
    //if not found create a new vector with only the population struct and push it back to the chain
    if (found==false)
    {
        cout << "Region not found" << endl;
    }
}
int Hashing::hashFunction(string Region){
    int sum=0;
     for(char c : Region) 
     {
         sum += static_cast<int>(c); // Convert char to ASCII value and add to sum
     }
     int index  = sum % m;
    return index;
}