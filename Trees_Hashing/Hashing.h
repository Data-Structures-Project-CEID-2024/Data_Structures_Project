#ifndef HASHING_H
#define HASHING_H

#include "Input.h"
#include "Struct.h"
#include "Trees.h"
#include <vector>
#include <string>
#include <list>  // Include the list header

class Hashing
{
    public:
      int m;
      REG AvlTree;

    Hashing()
    {

    };
    
    Hashing(int Chains);
    void insertElement(population p, std::vector<std::list<Node*>>& buckets);
    void searchElement(std::string Region, int Period, std::vector<std::list<Node*>>& buckets);
    void deleteElement(std::string Region, std::vector<std::list<Node*>>& buckets);
    void modifyElement(std::string Region, int Period, std::vector<std::list<Node*>>& buckets, int newCount);
    int hashFunction(std::string Region);
   
};

#endif
