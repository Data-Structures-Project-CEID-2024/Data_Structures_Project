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
    else
        max_index = index;

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
    // We should read the array from the back to the begining,
    // because HeapifyUp is built to make swaps from top to bottom
    // so every time the max element in the array is in the 0 index
    for (int i = length; i >= 0; i--)
        HeapifyUp(length, i);


    for (int i = length - 1; i >= 0; i--)
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
void Sort::MergeSort(int begin, int end)
{
    if (begin >= end)
        return;
    int mid = (begin+end)/ 2;
    MergeSort(begin, mid);
    MergeSort(mid + 1, end);
    merge(Sort::array, begin, mid, end);
}
    

void Sort::CountingSort()
{
    vector<int> freq;
    vector<population> out;

    for( int i=0; i < (int)array.size(); i++ )
    {
        while(array[i].count >= (int)freq.size()) // Fix Complexity Max
        {
            freq.push_back(0);
        }
        freq[array[i].count]++;
    }
    for( int i=1; i < (int)freq.size(); i++ )
    {
        freq[i] = freq[i]+freq[i - 1];
    }

    for( int i=array.size()-1; i >= 0; i-- )
    {
        while(freq[array[i].count - 1] >= (int)out.size()) //Fix Complexity
        {
            population p;
            p.count =0;
            out.push_back(p);
        }
        out[freq[array[i].count] - 1]=array[i];
        freq[array[i].count]--;
    }
    array = out;
}

int Sort::partition(vector<population>& Births, int left, int right) {

    int pivotValue = Births[left].count; // to aristerotero stoixeiokathe sub-array ws pivot

    int storeIndex = left + 1;

    // Partitioning gyrw apo to pivot
    for (int i = left + 1; i <= right; i++) {
        if (Births[i].count < pivotValue) {
            swap(Births[i], Births[storeIndex]);
            storeIndex++; //sto telos kserw mesw tou storeIndex poses allages exw kanei ara h thesh tou pivot sto final array einai sth thesh ish me ton arithmo twn allagwn
        }
    }

    swap(Births[left], Births[storeIndex - 1]);  // sto telos kathe partitioning vazoume to pivot sth thesh tou

    return storeIndex - 1;
}

void Sort::QuickSort( int begin, int end) {
    if (begin < end) {
        int pivotIndex = partition(array, begin, end);

        //sort ta aristera(mikrotera tou pivot) kai deksia(megalytera tou pivot) arrays
        QuickSort(begin, pivotIndex - 1);
        QuickSort(pivotIndex + 1, end);
    }
}