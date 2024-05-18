#include "Input.h"
#include "Struct.h"
#include "Sort.h"
#include "Search.h"

using namespace std;

int main() {
    Input input = Input();
    input.deathsNbirthsbyRegion();
    input.printArray(input.deathsbyRegion);
    // input.printArray(input.birthsbyRegion);

    cout << "---- Merge Sort:Births ----\n";
    Sort sort_Births_Merge = Sort(input.birthsbyRegion);
    sort_Births_Merge.mergeSort(0, sort_Births_Merge.array.size() - 1);
    input.printArray(sort_Births_Merge.array);

     cout << "---- Quick Sort:Births ----\n";
     Sort sort_Births_Quick =  Sort(input.birthsbyRegion);
     sort_Births_Quick.mergeSort(0, sort_Births_Quick.array.size() - 1);
     input.printArray(sort_Births_Quick.array);

    cout << "---- Heap Sort:Deaths ----\n";
    Sort sort_Deaths_Heap = Sort(input.deathsbyRegion);
    sort_Deaths_Heap.Heapsort();
    input.printArray(sort_Deaths_Heap.array);

    cout << "---- Counting Sort:Deaths ----\n";
    Sort sort_Deaths_Counting = Sort(input.deathsbyRegion);
    sort_Deaths_Counting.CountingSort(input.deathsbyRegion);
    input.printArray(sort_Deaths_Counting.array);



//    cout << "---- BinarySearch:Births ----\n";
//    Search search_Births = Search(input.birthsbyRegion);
//    input.printArray(search_Births.array);
//    search_Births.BinarySearch(search_Births.b1);
//    search_Births.rangeParse();
//    input.printArray(search_Births.rangeArray);
//    if (search_Births.findIndex >= 0)
//        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
//             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
//             << search_Births.array[search_Births.findIndex].region << "\n";
//    else {
//        cout << search_Births.b1 << " is not element of the Array\n";
//    }

//    cout << "---- InterpolationSearch:Births ----\n";
//    Search search_Births = Search(input.birthsbyRegion);
//    input.printArray(search_Births.array);
//    search_Births.InterpolationSearch(search_Births.b1);
//    search_Births.rangeParse();
//    input.printArray(search_Births.rangeArray);
//    if (search_Births.findIndex >= 0)
//        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
//             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
//             << search_Births.array[search_Births.findIndex].region << "\n";
//    else {
//        cout << search_Births.b1 << " is not element of the Array\n";
//    }

//    cout << "---- BinaryInterpolationSearch:Births ----\n";
//    Search search_Births = Search(input.birthsbyRegion);
//    input.printArray(search_Births.array);
//    search_Births.BinaryInterpolationSearch(search_Births.b1);
//    search_Births.rangeParse();
//    input.printArray(search_Births.rangeArray);
//    if (search_Births.findIndex >= 0)
//        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
//             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
//             << search_Births.array[search_Births.findIndex].region << "\n";
//    else {
//        cout << search_Births.b1 << " is not element of the Array\n";
//    }

    cout << "---- BinaryInterpolationSearch [EXTENDED]:Births ----\n";
    Search search_Births = Search(input.birthsbyRegion);
    input.printArray(search_Births.array);
    search_Births.findIndex = search_Births.Exponential_BinaryInterpolationSearch(search_Births.b1);
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (search_Births.findIndex >= 0)
        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
             << search_Births.array[search_Births.findIndex].region << "\n";
    else {
        cout << search_Births.b1 << " is not element of the Array\n";
    }

}