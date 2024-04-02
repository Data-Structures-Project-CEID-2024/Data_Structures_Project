#include<iostream>
#include<fstream>
#include<sstream> 

#include "Struct.h"

using namespace std;



class Input
{
    public:
        Input()
        {
            ifstream inputFile("bd-dec22-births-deaths-by-region.csv");

            if (inputFile.is_open())
            {
                string buffer;
                inputFile >> buffer ; 
                string line;
                
                while(inputFile >> line)
                {
                    population input;
                    istringstream ss(line);

                    getline(ss,buffer, ',');
                    input.period = stoi(buffer);
                    cout << input.period << " ";

                    getline(ss,buffer, ',');
                    if(buffer == "Births")
                        input.alive = true;
                    else
                        input.alive = false;
                    cout << input.alive << " ";

                    getline(ss,buffer, ',');
                    input.region = buffer;
                    cout << input.region<< " ";

                    getline(ss,buffer, ',');
                    input.count = stoi(buffer);
                    cout << input.count << " ";

                    cout << "\n";
                    
                }

                cout<< buffer;
                
            } 
            
        }
};

int main()
{
    Input input = Input();
}