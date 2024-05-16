#ifndef INPUT_H
#define INPUT_H

#include    <iostream>
#include    <fstream>
#include    <sstream> 
#include    <algorithm> // Required for std::remove_if
#include    <cctype> 
#include    <vector>
#include    "Struct.h"

class Input{
    public:
        std::vector<population> input;
        std::vector<population> deathsbyRegion;
        std::vector<population> birthsbyRegion;

        Input();
        void deathsNbirthsbyRegion();

        void printArray(std::vector<population> Array);
};

#endif