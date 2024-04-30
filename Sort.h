#ifndef SORT_H
#define SORT_H

#include<vector>
#include "Struct.h"

class Sort{
    public:
            std::vector<population> array;

            Sort(std::vector<population> v);
            void swap(population& a, population& b);

            // Heap Sort
            void HeapifyUp(int length, int index);
            void Heapsort();

            // Merge Sort
            void merge(std::vector<population>& Births, int left, int mid, int right);
            void mergeSort(int begin, int end);
            
            // Counting Sort
            void CountingSort();

            // Quick Sort
            // void Sort::quickSort(int begin, int end); 
            // void Sort::MakeQuick(int left, int mid, int right); 
};

#endif