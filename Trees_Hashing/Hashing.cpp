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
     PRD prd;
     int sum=0;
     for(char c : Region) 
     {
         sum += static_cast<int>(c); // Convert char to ASCII value and add to sum
     }

     int index  = sum % m;
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
                    cout << "Period found" << endl;
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
void Hashing::deleteElement()
{
//indexforDeletion = AvlTree.search(root, element)
}
void Hashing::modifyElement()
{

}
