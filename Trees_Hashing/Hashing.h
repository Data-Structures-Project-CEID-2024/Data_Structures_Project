#ifndef HASHING_H
#define HASHING_H

#include    "Input.h"
#include    "Struct.h"
#include    "Trees.h"
#include    <vector>
#include    <string>
#include    <list>


class Hashing
{
    
    public:
        int m;
        REG AvlTree;
        
        Hashing(int Chains);
        void insertElement(population p, std::vector<Node*>* buckets);
        void searchElement(std::string Region, int Period, std::vector<Node*>* buckets);
        void deleteElement();
        void modifyElement();
     
        
};



#endif