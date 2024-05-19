#include<iostream>
#include<fstream>
#include<sstream> 
#include <algorithm> // Required for std::remove_if
#include <cctype> 
#include<vector>
#include "Struct.h"
#include <math.h>
#include <list>

using namespace std;

population Answer[17];
const int m = 11; //prime number of buckets


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
            vector<population> entries;

            //int count_births = 0;
            for (int i=0;i<(int)input.size();i++){
                population entry;
                entry.alive=input[i].alive;
                entry.count=input[i].count;
                entry.period=input[i].period;
                entry.region=input[i].region;
                entries.push_back(entry);
            }
            //old code for total diths and births by region!
            // for (int region_id = 0; region_id < 17; region_id++) //2022-2005=17 years of data (for each year)
            // {
            //     for (int i = region_id; i < (int)input.size();  i+= 36) //36 are the rows that each years takes (for each region)
            //     {
            //         count_births += input[i].count;
            //         // cout << input[i].count << "\t";
            //     }    
            //     population byRegion_births;
            //     byRegion_births.alive = true;
            //     byRegion_births.region = input[region_id].region;
            //     byRegion_births.count = count_births;

            //     deathsNbirthsbyRegion.push_back(byRegion_births);

            //     int count_deaths = 0;           
            //     for (int i = region_id + 18; i < (int)input.size();  i+= 36)
            //     {
            //         count_deaths += input[i].count;
            //     }
            //     population byRegion_deaths;
            //     byRegion_deaths.alive = false;
            //     byRegion_deaths.region = input[region_id].region;
            //     byRegion_deaths.count = count_deaths;

            //     deathsNbirthsbyRegion.push_back(byRegion_deaths);
            //     cout << "\n";
            // }
            // return deathsNbirthsbyRegion 
            return (entries);
        }
};

int binarySearch(vector <population> array, int l, int r, int x, int step)
{
     
    while (l <= r) {
        int m = floor((l + r - l) / 2*step);
        // Check if x is present at mid
        if (x > array[m].count && x < array[m+step].count){
            if (step !=0) {
                l =m;
                r = m+step;
                step = sqrt(step);
            }
            //binarySearch(array, m, m + step, x, sqrt(step));
            else if (x==array[m].count) return m;
            else return -1;
        }
        // If x greater, ignore left half
        else if (x > array[m].count)
            l = m + step;

        // If x is smaller, ignore right half
        else
            r = m - step;
    }
    // If we reach here, then element was not present
    return -1;
}
int BinaryInterpolationSearch(int x, vector<population> array)
{
    int next; int index;
    int size = array.size();
    int left = 1;
    int right = size - 1;
    
    do
    {
        index   = 0;
        size    = right - left + 1;

        next    = int(size * ((x - array[left].count ) / (array[right].count - array[left].count))) + left - 1 ;
        
        if ((x > array[next + pow(2,index)*sqrt(size)].count)&&(x <= array[next + pow(2,index+1)*sqrt(size)].count)) // if (array[next +2^i<x<array[nex+2^i+1]])
           {
            int step = ceil( size / sqrt(size));
            cout << "\nhello"; 
            return(binarySearch(array, left, right, x, step));}
            
        if (x > array[next].count)
        {
            while( x > array[next + pow(2, index)* sqrt(size) - 1].count)
                index = index + 1;
            
            right = next + pow(index, 2) * sqrt(size);
            //left = next + pow(index-1, 2) * sqrt(size);
        }
        else if ( x < array[next].count)
        {
            while( x < array[next - pow(2, index)* sqrt(size) + 1].count)
                index = index + 1;
            
           //right = next + pow(index-1, 2) * sqrt(size);
            left = next + pow(index, 2) * sqrt(size);
        }            
      
    }while(x!=array[next].count);
    
    return (next);

}
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

void insertElement(population p, list<vector<population>>* buckets){

    
    int sum=0;
    for(char c : p.region) {
        sum += static_cast<int>(c); // Convert char to ASCII value and add to sum
    }

    int index = sum%m;
    bool found=false;
    //bucket[index] -> chain
    for (auto& RegionVector : buckets[index]){
        //linear search to find the vector with the right region
        if (RegionVector[0].region==p.region){
                RegionVector.push_back(p);
                found = true;
        }
    }
    //if not found create a new vector with only the population struct and push it back to the chain
    if (found==false){
            vector <population> temp;
            temp.push_back(p); 
            buckets[index].push_back(temp);
    }

   // buckets[index].push_back(p);
  //cout <<"Result: " << buckets[index].front().region << endl;
  
}
void searchElement(){

}
void deleteElement(){

}
void modifyElement(){

}

int main()
{
    Input input = Input();
    vector<population> results = input.deathsNbirthsbyRegion();
    
     list< vector <population>> buckets[m];
    for (const auto& result : results)
    {
        cout << "Region: " << result.region <<  "\t\tPeriod:  "  << result.period;
        if(result.alive==true) cout << "\tBirths: " << result.count << endl;
        else cout << " \tDeaths: "<<  result.count << endl;
        insertElement(result, buckets);
    }
    
    
    for (int i=0; i <m; i++){
        cout <<"Vectors in chain" << (buckets[i]).size() << endl;
        list<vector<population>> temp = buckets[i];
        cout << "Size of each Vector: " << endl;
        for (const auto& vec : temp){
            cout <<"Region: " << vec[0].region << " Size: " <<vec.size() << endl;
        }
        // for (const auto& item : buckets[i]) {
        //     cout << item.region << " "; // Assuming 'region' is a member of population struct
        // }
        //     cout << endl;
    }
} 
