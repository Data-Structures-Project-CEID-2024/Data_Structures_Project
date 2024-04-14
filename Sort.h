#ifndef SORT_H
#define SORT_H

#include<vector>
#include "Struct.h"

class Sort{
    public:
            std::vector<population> array;

            Sort(std::vector<population> v);
            void swap(population& a, population& b);
            void HeapifyUp(int length, int index);
            void Heapsort();

};

#endif