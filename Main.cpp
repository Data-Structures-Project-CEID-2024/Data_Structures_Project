#include "Input.h"
#include "Struct.h"
#include "Sort.h"

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

}