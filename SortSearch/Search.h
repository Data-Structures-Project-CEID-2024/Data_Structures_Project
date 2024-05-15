#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <math.h>
#include "Struct.h"

class Search{
    public:
            std::vector<population> array; //Sorted array for search
            std::vector<population> rangeArray; //Array after range shrink for [b1, b2]

            int findIndex;  //Index of key if found | Index bigger than and close to key for next best range [bx, b2]
            void rangeParse();  //Function of serial range printing to b2
            Search(std::vector<population> v);
            int BinaryInterpolationSearch(int x);
            int LinearSearch(int start, int end, int x);
            int BinarySearch(int key);
            int InterpolationSearch(int key);

            int b1, b2; //Class member range limits of [b1,b2] rangeArray
};

#endif