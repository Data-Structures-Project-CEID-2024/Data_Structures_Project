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

//void Sort::CountingSort(vector<population>& input){
//    vector<int> freq;
//    vector<population> out;
//
////---//
//    int maxV = 0;
//    for(auto & i : input){
//        if( i.count > (int)maxV ){
//            maxV = i.count;
//        }
//    }
//    for( int i=0; i <= (int)maxV; i++){
//        freq.push_back(0);
//    }
////---//
//
//    for( int i=0; i < (int)input.size(); i++ ){
//        freq[input[i].count]++;
//    }
//    for( int i=1; i < (int)freq.size(); i++ ){
//        freq[i] = freq[i]+freq[i-1];
//    }
//
////---//
//    int maxF = 0;
//    for(int i : freq){
//        if( i > (int)maxF ){
//            maxF = i;
//        }
//    }
//    for( int i=0; i < (int)maxF; i++){
//        population p;
//        p.count =0;
//        out.push_back(p);
//    }
////---//
//
//    for( int i=input.size()-1; i >= 0; i-- ){
//        out[freq[input[i].count]-1]=input[i];
//        freq[input[i].count]--;
//    }
//    array = out;
//}

void Sort::CountingSort(vector<population>& input){
    vector<int> freq; //Frequency array των τιμών του input
    vector<population> out; //sort-αρισμένο output  του array input

    //Αρχικοποίηση του frequency array υπολογίζοντας το max value των τιμών εισόδου
    int maxV = 0;
    for(auto & i : input){
        if( i.count > maxV ){
            maxV = i.count;
        }
    }
    freq.resize(maxV + 1, 0);

    //Κατάθεση τιμών που αντιπροσωπεύουν το πλήθος επαναλήψεων του index αριθμού στο freq array
    for(const auto& i : input){
        freq[i.count]++;
    }
    //Υπολογισμός και κατάθεση των προηγούμενα εμφανιζόμενων στοιχείων βάσει των τιμών του freq array ανα index
    for(int i = 1; i < (int)freq.size(); i++){
        freq[i] += freq[i - 1];
    }

    //Αρχικοποίηση του array εξόδου για να ταιριάζει με το μέγεθος του array εισόδου
    out.resize(input.size());

    //Κατάθεση των τιμών του input σε κατάλληλες θέσεις του output βάσει του frequency array
    for(int i = input.size() - 1; i >= 0; i--){
        out[freq[input[i].count] - 1] = input[i];
        freq[input[i].count]--;
    }

    //Ανάθεση της εξόδου στο μέλος της κλάσης Sort, array
    array = out;
}


// void Sort::MakeQuick(int left, int mid, int right) 
// {
//     int  tempLeftArr = mid - left + 1;
//     int  tempRightArr = right - mid;
//     vector<population> LeftArray;
//     vector<population> RightArray;

//     int tempIndexOne = 0;
//     int tempIndexTwo = 0;
//     int indexOfMergedArray = left;

//     while (tempIndexOne < tempLeftArr && tempIndexTwo < tempRightArr) 
//     {
//         if (LeftArray[tempIndexOne].count <= RightArray[tempIndexTwo].count) 
//         {
//             array[indexOfMergedArray] = LeftArray[tempIndexOne];
//             tempIndexOne++;
//         } else {
//             array[indexOfMergedArray] = RightArray[tempIndexTwo];
//             tempIndexTwo++;
//         }
//         indexOfMergedArray++;
//     }

//     while (tempIndexOne < tempLeftArr) 
//     {
//         array[indexOfMergedArray] = LeftArray[tempIndexOne];
//         tempIndexOne++;
//         indexOfMergedArray++;
//     }

//     while (tempIndexTwo < tempRightArr) 
//     {
//         array[indexOfMergedArray] = RightArray[tempIndexTwo];
//         tempIndexTwo++;
//         indexOfMergedArray++;
//     }


// }

// void Sort::quickSort(int begin, int end) 
// {
//     if (begin < end) 
//     {
//         int pivotIndex = begin;
//         int pivot = array[pivotIndex].count;
//         int middle = (begin+end)/2;
//         int i = begin + 1;
//         int j = end;

//         while (i <= j) {
//             while (i <= j && array[i].count <= pivot) 
//             {
//                 i++;
//             }
//             while (j >= i && array[j].count > pivot) 
//             {
//                 j--;
//             }
//             if (i < j) {
//                 swap(array[i], array[j]);
//             }
//         }
//         swap(array[pivotIndex], array[j]);
//         pivotIndex = j;

//         quickSort( begin, pivotIndex - 1);
//         quickSort( pivotIndex + 1, end);
//         MakeQuick(begin, middle, end);
//     }
// }
