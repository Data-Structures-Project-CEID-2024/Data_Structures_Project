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
    Sort sort_Births =  Sort(input.birthsbyRegion);
    sort_Births.mergeSort(0, sort_Births.array.size() - 1);
    input.printArray(sort_Births.array);

    cout << "---- Heap Sort:Deaths ----\n";
    Sort sort_Deaths =  Sort(input.deathsbyRegion);
    sort_Deaths.Heapsort();
    input.printArray(sort_Deaths.array);


    cout << "---- BIS:Births ----\n";
    Search search_Births =  Search(input.birthsbyRegion);
    int find = 859365;
    int index = search_Births.BinaryInterpolationSearch(find);
    if (index != -1)
        cout << "Element: " << find << " was found in index: " << index << " Element == Array[index]: " << find << " == " << input.birthsbyRegion[index].count << " Region: " << input.birthsbyRegion[index].region <<"\n";
    else    
        cout << find << " is not element of the Array\n";
}