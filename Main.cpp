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


    cout << "---- Heap Sort:Deaths ----\n";
    Sort sort =  Sort(input.deathsbyRegion);
    sort.Heapsort();
    input.printArray(sort.array);

}