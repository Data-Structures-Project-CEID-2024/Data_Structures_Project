#include "Sort.h"
#include <iostream>

using namespace std;

Sort::Sort(vector<population> v)
{
    array = v;
}

// HeapSort
void Sort::swap(population& a, population& b)
{
    population temp;
    temp = a;
    a = b;
    b = temp;
}

void Sort::HeapifyUp(int length, int index)
{
    int max_index,leftchild,rightchild;

    max_index = index;
    leftchild = 2*index + 1;
    rightchild = 2*index + 2;

    if (leftchild < length && array[max_index].count < array[leftchild].count)
        max_index = leftchild;

    if (rightchild < length && array[max_index].count < array[rightchild].count)
        max_index = rightchild;
    
    if (max_index != index)
    {
        swap(array[index], array[max_index]);
        HeapifyUp(length, max_index);
    }
}

void Sort::Heapsort()
{
    int length = array.size();

    for (int i = 0; i < length; i++)
        HeapifyUp(length, i);


    for (int i = length - 1; i > 0; i--)
    {
        length = length - 1;   
        swap(array[0], array[length]);
        HeapifyUp(length, 0);
       
    }
}

void Sort::merge(vector<population>& Births, int left, int mid, int right) 
{
    int  tempArrayOne = mid - left + 1;
    int  tempArrayTwo = right - mid;

    //make temp population vectors
    vector<population> leftArray;
    vector<population> rightArray;

    for (int i = 0; i < tempArrayOne; i++)
        leftArray.push_back(Births[left + i]);

    for (int i = 0; i < tempArrayTwo; i++)
        rightArray.push_back(Births[mid + 1 + i]);

    int tempIndexOne = 0;
    int tempIndexTwo = 0;
    int indexOfMergedArray = left;

    // Merge
    while (tempIndexOne < tempArrayOne
        && tempIndexTwo < tempArrayTwo) {
        if (leftArray[tempIndexOne].count
            <= rightArray[tempIndexTwo].count) {
            Births[indexOfMergedArray] = leftArray[tempIndexOne];
            tempIndexOne++;
        } else {
            Births[indexOfMergedArray] = rightArray[tempIndexTwo];
            tempIndexTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy Remaining Elements
    while (tempIndexOne < tempArrayOne) {
        Births[indexOfMergedArray] = leftArray[tempIndexOne];
        tempIndexOne++;
        indexOfMergedArray++;
    }

    while (tempIndexTwo < tempArrayTwo) {
        Births[indexOfMergedArray] = rightArray[tempIndexTwo];
        tempIndexTwo++;
        indexOfMergedArray++;
    }

}
void Sort::mergeSort(int begin, int end)
{

    if (begin >= end)
        return;
    int mid = (begin+end)/ 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);
    merge(Sort::array, begin, mid, end);
}
    


