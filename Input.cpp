#include<iostream>
#include<fstream>
#include<sstream> 
#include <algorithm> // Required for std::remove_if
#include <cctype> 
#include<vector>
#include "Struct.h"

using namespace std;

population Answer[17];

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
        vector<population> deathsNbirthsbyRegion()
        {
            vector<population> deathsNbirthsbyRegion;

            int count_births = 0;
            for (int region_id = 0; region_id < 17; region_id++) //2022-2005=17 years of data (for each year)
            {
                for (int i = region_id; i < input.size();  i+= 36) //36 are the rows that each years takes (for each region)
                {
                    count_births += input[i].count;
                    // cout << input[i].count << "\t";
                }    
                population byRegion_births;
                byRegion_births.alive = true;
                byRegion_births.region = input[region_id].region;
                byRegion_births.count = count_births;

                deathsNbirthsbyRegion.push_back(byRegion_births);

                int count_deaths = 0;           
                for (int i = region_id + 18; i < input.size();  i+= 36)
                {
                    count_deaths += input[i].count;
                }
                population byRegion_deaths;
                byRegion_deaths.alive = false;
                byRegion_deaths.region = input[region_id].region;
                byRegion_deaths.count = count_deaths;

                deathsNbirthsbyRegion.push_back(byRegion_deaths);
                cout << "\n";
            }

            return (deathsNbirthsbyRegion);
        }
};
void merge(vector<population>& Births, int left, int mid, int right) {
    int  tempArrayOne = mid - left + 1;
    int  tempArrayTwo = right - mid;

    //make temp population vectors
    vector<population> leftArray;
    vector<population> rightArray;

    for (int i = 0; i < tempArrayOne; i++)
        leftArray.push_back(Births[left + i]);

    for (int i = 0; i < tempArrayTwo; i++)
        rightArray.push_back(Births[mid + 1 + i]);

    int tempIndexOne = 0;
    int tempIndexTwo = 0;
    int indexOfMergedArray = left;

    // Merge
    while (tempIndexOne < tempArrayOne
           && tempIndexTwo < tempArrayTwo) {
        if (leftArray[tempIndexOne].count
            <= rightArray[tempIndexTwo].count) {
            Births[indexOfMergedArray] = leftArray[tempIndexOne];
            tempIndexOne++;
        } else {
            Births[indexOfMergedArray] = rightArray[tempIndexTwo];
            tempIndexTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy Remaining Elements
    while (tempIndexOne < tempArrayOne) {
        Births[indexOfMergedArray] = leftArray[tempIndexOne];
        tempIndexOne++;
        indexOfMergedArray++;
    }

    while (tempIndexTwo < tempArrayTwo) {
        Births[indexOfMergedArray] = rightArray[tempIndexTwo];
        tempIndexTwo++;
        indexOfMergedArray++;
    }

}
void mergeSort(vector<population>& Births, int begin, int end){
    if (begin >= end)
        return;
    int mid = (begin+end)/ 2;
    mergeSort(Births, begin, mid);
    mergeSort(Births, mid + 1, end);
    merge(Births, begin, mid, end);
}

    int main()
{
    Input input = Input();
    vector<population> results = input.deathsNbirthsbyRegion();

    vector<population> Births;
    cout << "Region" << endl;
    int j=0;
    for (const auto& result : results)
    {
        j++;
        cout << result.region;
        if (result.alive) {
            cout << " Births: " << result.count;
            Births.push_back(result);

        }
        else{
            cout <<" Deaths: " << result.count;

            }
        cout << endl;
    }
    cout << Births.size();
    mergeSort(Births,0,17);
    cout << endl <<"Sorted with Mergesort by Births:"<< endl;
    for (const auto& result : Births)
    {
        cout << result.region;
        cout << ": "<<result.count;
        cout << endl;
    }

}