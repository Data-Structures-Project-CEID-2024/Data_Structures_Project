#include "Input.h"
#include "Struct.h"
#include "Sort.h"
#include "Search.h"

using namespace std;

int main()
{
    Input input = Input();
    input.deathsNbirthsbyRegion();
    input.printArray(input.deathsbyRegion);
    // input.printArray(input.birthsbyRegion);

    cout << "---- Merge Sort:Births ----\n";
    Sort sort_Births_Merge =  Sort(input.birthsbyRegion);
    sort_Births_Merge.mergeSort(0, sort_Births_Merge.array.size() - 1);
    input.printArray(sort_Births_Merge.array);

    // cout << "---- Quick Sort:Births ----\n";
    // Sort sort_Births_Quick =  Sort(input.birthsbyRegion);
    // sort_Births_Quick.mergeSort(0, sort_Births_Quick.array.size() - 1);
    // input.printArray(sort_Births_Quick.array);

    cout << "---- Heap Sort:Deaths ----\n";
    Sort sort_Deaths_Heap =  Sort(input.deathsbyRegion);
    sort_Deaths_Heap.Heapsort();
    input.printArray(sort_Deaths_Heap.array);

    cout << "---- Counting Sort:Deaths ----\n";
    Sort sort_Deaths_Counting =  Sort(input.deathsbyRegion);
    sort_Deaths_Counting.CountingSort(input.deathsbyRegion);
    input.printArray(sort_Deaths_Counting.array);

    cout << "---- BinarySearch:Births ----\n";
    Search search_Births = Search(input.birthsbyRegion);
    input.printArray(search_Births.array);
    int index = search_Births.BinarySearch();
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (index != -1)
        cout << "Element: " << search_Births.b1 << " was found in index: " << index << " Element == Array[index]: " << search_Births.b1 << " == " << search_Births.array[index].count << " Region: " << search_Births.array[index].region <<"\n";
    else
        cout << search_Births.b1 << " is not element of the Array\n";


//    cout << "---- BIS:Births ----\n";
//    Search search_Births =  Search(input.birthsbyRegion);
//    input.printArray(search_Births.array);
//    int find = 859365;
//    int index = search_Births.BinaryInterpolationSearch(find);
//    if (index != -1)
//        cout << "Element: " << find << " was found in index: " << index << " Element == Array[index]: " << find << " == " << search_Births.array[index].count << " Region: " << search_Births.array[index].region <<"\n";
//    else
//        cout << find << " is not element of the Array\n";

}