#include "Input.h"
#include "Struct.h"
#include "Sort.h"
#include "Search.h"
#include <chrono>

using namespace std;

int main()
{
    Input input = Input();
    input.deathsNbirthsbyRegion();
    input.printArray(input.deathsbyRegion);
    // input.printArray(input.birthsbyRegion);

    // cout << "---- Merge Sort:Births ----\n";
    // Sort sort_Births_Merge =  Sort(input.birthsbyRegion);
    // sort_Births_Merge.MergeSort(0, sort_Births_Merge.array.size() - 1);
    // input.printArray(sort_Births_Merge.array);

    // cout << "---- Quick Sort:Births ----\n";
    // Sort sort_Births_Quick =  Sort(input.birthsbyRegion);
    // sort_Births_Quick.QuickSort(0, sort_Births_Quick.array.size() - 1);
    // input.printArray(sort_Births_Quick.array);

    cout << "---- Merge Sort:Births ----\n";
    Sort sort_Births_Merge = Sort(input.birthsbyRegion);

    auto start_merge = chrono::high_resolution_clock::now(); // απο εδω 
    sort_Births_Merge.MergeSort(0, sort_Births_Merge.array.size() - 1);
    auto end_merge = chrono::high_resolution_clock::now();
    chrono::duration<double> merge_sort_duration = end_merge - start_merge;//μεχρι εδω μετρα κάνοντας include την βιβλιοθήκη chrono τον χρόνο της mergesort, το ίδιο και της quicksort πιο κάτω

    input.printArray(sort_Births_Merge.array);
    cout << "Merge Sort took " << merge_sort_duration.count() << " seconds.\n" << endl;

  


    cout << "---- Quick Sort:Births ----\n";
    Sort sort_Births_Quick = Sort(input.birthsbyRegion);

    auto start_quick = chrono::high_resolution_clock::now();
    sort_Births_Quick.QuickSort(0, sort_Births_Quick.array.size() - 1);
    auto end_quick = chrono::high_resolution_clock::now();
    chrono::duration<double> quick_sort_duration = end_quick - start_quick;

    input.printArray(sort_Births_Quick.array);
    cout << "Quick Sort took " << quick_sort_duration.count() << " seconds.\n" << endl;



    cout << "---- Heap Sort:Deaths ----\n";
    Sort sort_Deaths_Heap =  Sort(input.deathsbyRegion);

    auto start_heap = chrono::high_resolution_clock::now();
    sort_Deaths_Heap.Heapsort();
    auto end_heap = chrono::high_resolution_clock::now();
    chrono::duration<double> heap_sort_duration = end_heap - start_heap;

    input.printArray(sort_Deaths_Heap.array);
    cout << "Heap Sort took " << heap_sort_duration.count() << " seconds.\n" << endl;



    cout << "---- Counting Sort:Deaths ----\n";
    Sort sort_Deaths_Counting =  Sort(input.deathsbyRegion);

    auto start_count = chrono::high_resolution_clock::now();
    sort_Deaths_Counting.CountingSort();
    auto end_count = chrono::high_resolution_clock::now();
    chrono::duration<double> count_sort_duration = end_count - start_count;


    input.printArray(sort_Deaths_Counting.array);
    cout << "Counting Sort took " << count_sort_duration.count() << " seconds.\n" << endl;




    cout << "---- BinarySearch:Births ----\n";
    Search search_Births = Search(input.birthsbyRegion);
    input.printArray(search_Births.array);
    auto start_binary = chrono::high_resolution_clock::now(); //stopwatch start
    search_Births.BinarySearch(search_Births.b1);
    auto end_binary = chrono::high_resolution_clock::now(); //stopwatch end
    chrono::duration<double> binary_search_duration = end_binary - start_binary;
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (search_Births.findIndex >= 0)
        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
             << search_Births.array[search_Births.findIndex].region << "\n";
    else
        cout << search_Births.b1 << " is not element of the Array\n";
    cout << "Binary Search took " << binary_search_duration.count() << " seconds.\n"<< endl;




    // Measure time for Interpolation Search
    cout << "---- InterpolationSearch:Births ----\n";
    input.printArray(search_Births.array);
    auto start_interpolation = chrono::high_resolution_clock::now(); //stopwatch start
    search_Births.InterpolationSearch(search_Births.b1);
    auto end_interpolation = chrono::high_resolution_clock::now(); //stopwatch end
    chrono::duration<double> interpolation_search_duration = end_interpolation - start_interpolation;
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (search_Births.findIndex >= 0)
        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
             << search_Births.array[search_Births.findIndex].region << "\n";
    else
        cout << search_Births.b1 << " is not element of the Array\n";
    cout << "Interpolation Search took " << interpolation_search_duration.count() << " seconds.\n"<< endl;




    // Measure time for Binary Interpolation Search
    cout << "---- BinaryInterpolationSearch:Births ----\n";
    input.printArray(search_Births.array);
    auto start_binary_interpolation = chrono::high_resolution_clock::now(); //stopwatch start
    search_Births.BinaryInterpolationSearch(search_Births.b1);
    auto end_binary_interpolation = chrono::high_resolution_clock::now(); //stopwatch end
    chrono::duration<double> binary_interpolation_search_duration = end_binary_interpolation - start_binary_interpolation;
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (search_Births.findIndex >= 0)
        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
             << search_Births.array[search_Births.findIndex].region << "\n";
    else
        cout << search_Births.b1 << " is not element of the Array\n";
    cout << "Binary Interpolation Search took " << binary_interpolation_search_duration.count() << " seconds.\n"<< endl;




    // Measure time for Exponential Binary Interpolation Search
    cout << "---- BinaryInterpolationSearch [EXTENDED]:Births ----\n";
    input.printArray(search_Births.array);
    auto start_exponential_binary_interpolation = chrono::high_resolution_clock::now(); //stopwatch start
    search_Births.findIndex = search_Births.Exponential_BinaryInterpolationSearch(search_Births.b1);
    auto end_exponential_binary_interpolation = chrono::high_resolution_clock::now(); //stopwatch end
    chrono::duration<double> exponential_binary_interpolation_search_duration = end_exponential_binary_interpolation - start_exponential_binary_interpolation;
    search_Births.rangeParse();
    input.printArray(search_Births.rangeArray);
    if (search_Births.findIndex >= 0)
        cout << "Element: " << search_Births.b1 << " was found in index: " << search_Births.findIndex << " Element == Array[index]: "
             << search_Births.b1 << " == " << search_Births.array[search_Births.findIndex].count << " Region: "
             << search_Births.array[search_Births.findIndex].region << "\n";
    else
        cout << search_Births.b1 << " is not element of the Array\n";
    cout << "Exponential Binary Interpolation Search took " << exponential_binary_interpolation_search_duration.count() << " seconds.\n" << endl;

}