#include<iostream>
#include<fstream>
#include<sstream> 
#include <algorithm> // Required for std::remove_if
#include <cctype> 
#include<vector>
#include "Struct.h"

using namespace std;



class Input
{
    public:
        Input()
        {
            ifstream inputFile("bd-dec22-births-deaths-by-region.txt");

            if (inputFile.is_open())
            {
                string buffer;
                string line;
                getline(inputFile,line);

                vector<population> Input;
                while(getline(inputFile,line))
                {
                    population input;
                    istringstream ss(line);
                    

                    getline(ss,buffer, ',');

                    input.period = stoi(buffer);
                    cout << input.period << " ";

                    getline(ss,buffer, ',');
                    input.alive = (buffer == "Births");
                    cout << input.alive << " ";

                    getline(ss,buffer, ',');
                    input.region = buffer;
                    cout << input.region<< " ";

                    getline(ss,buffer, ',');
                    input.count = stoi(buffer);
                    cout << input.count << " ";

                    cout << "\n";
                    Input.push_back(input);
                }

                
            } 
            
        }
};

int main()
{
    Input input = Input();
}