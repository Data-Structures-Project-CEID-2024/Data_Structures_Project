#include "Input.h"
#include "Struct.h"


using namespace std;

int main()
{
    Input input = Input();
    vector<population> birth  = input.deathsNbirthsbyRegion(true);
    vector<population> death = input.deathsNbirthsbyRegion(false);

    input.printArray(input.deathssbyRegion);
    input.printArray(input.birthsbyRegion);
}