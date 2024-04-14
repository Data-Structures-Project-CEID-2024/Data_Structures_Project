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

