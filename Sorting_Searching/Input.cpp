
#include "Input.h"
    
using namespace std;


        
Input::Input()
{
    ifstream inputFile("Input/bd-dec22-births-deaths-by-region.txt");

    if (inputFile.is_open())
    {
        string buffer;
        string line;
        getline(inputFile,line);

        
        // Get Line and Parse CSV File [Period, Alive, Region, Count]
        while(getline(inputFile,line))
        {
            population p;
            istringstream ss(line);
            

            getline(ss,buffer, ',');

            p.period = stoi(buffer);

            getline(ss,buffer, ',');
            p.alive = (buffer == "Births");

            getline(ss,buffer, ',');
            if (buffer == "\"Region not stated or area outside region\"")
                p.region = "0";
            else
                p.region = buffer;

            getline(ss,buffer, ',');
            p.count = stoi(buffer);

            input.push_back(p);
        }

        
    }
    else
    {
        cout << "Error File was NOT FOUND\n";
        exit(0);
    } 
        
}

    // It gets the initial Input and
    // adds up all the deaths and births
    // by region
void Input::deathsNbirthsbyRegion()
{
    
    int count_births = 0;
    for (int region_id = 0; region_id < 17; region_id++)
    {
        for (int i = region_id; i < (int)input.size();  i+= 36)
        {
            count_births += input[i].count;
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

        deathsbyRegion.push_back(byRegion_deaths);
        
    }
}

void Input::printArray(vector<population> Array)
{
    cout << "Count\t\t" << "Region" << "\n\n";

    for(auto& v : Array)
    {
        cout << v.count << "\t\t" << v.region << "\n";
    }


    cout << "\n";
}   



