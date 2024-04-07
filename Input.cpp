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
        vector<population> input;
        
        Input()
        {
            ifstream inputFile("Input/bd-dec22-births-deaths-by-region.txt");

            if (inputFile.is_open())
            {
                string buffer;
                string line;
                getline(inputFile,line);

                
                while(getline(inputFile,line))
                {
                    population p;
                    istringstream ss(line);
                    

                    getline(ss,buffer, ',');

                    p.period = stoi(buffer);
                    // cout << p.period << " ";

                    getline(ss,buffer, ',');
                    p.alive = (buffer == "Births");
                    // cout << p.alive << " ";

                    getline(ss,buffer, ',');
                    if (buffer == "\"Region not stated or area outside region\"")
                        p.region = "0";
                    else
                        p.region = buffer;
                    // cout << p.region<< " ";

                    getline(ss,buffer, ',');
                    p.count = stoi(buffer);
                    // cout << p.count << " ";

                    // cout << "\n";
                    input.push_back(p);
                }

                
            } 
            
        }

        // It gets the initial Input and
        // adds up all the deaths and births
        // by region
        vector<population> deathsNbirthsbyRegion(bool birth_death)
        {
            vector<population> deathssbyRegion;
            vector<population> birthsbyRegion;
            int count_births = 0;
            for (int region_id = 0; region_id < 17; region_id++)
            {
                for (int i = region_id; i < (int)input.size();  i+= 36)
                {
                    count_births += input[i].count;
                    // cout << input[i].count << "\t";
                }    
                population byRegion_births;
                byRegion_births.alive = true;
                byRegion_births.region = input[region_id].region;
                byRegion_births.count = count_births;

                birthsbyRegion.push_back(byRegion_births);

                int count_deaths = 0;           
                for (int i = region_id + 18; i < (int)input.size();  i+= 36)
                {
                    count_deaths += input[i].count;
                }
                population byRegion_deaths;
                byRegion_deaths.alive = false;
                byRegion_deaths.region = input[region_id].region;
                byRegion_deaths.count = count_deaths;
                deathssbyRegion.push_back(byRegion_deaths);
                
                // cout << "\n";
            }
            if (birth_death == true)
                return (birthsbyRegion);
            
            return (deathssbyRegion);
        }
};

int main()
{
    Input input = Input();
    vector<population> birth  = input.deathsNbirthsbyRegion(true);
    vector<population> death = input.deathsNbirthsbyRegion(false);
}