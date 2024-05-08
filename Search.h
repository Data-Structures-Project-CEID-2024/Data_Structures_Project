#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <math.h>
#include "Struct.h"

class Search{
    public:
            std::vector<population> array;
            std::vector<population> rangeArray;

            int findIndex;
            void rangeParse();
            Search(std::vector<population> v); 
            int BinaryInterpolationSearch(int x);
            int LinearSearch(int start, int end, int x);
            int BinarySearch();

            int b1, b2;
};

#endif