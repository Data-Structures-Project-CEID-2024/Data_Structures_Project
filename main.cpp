#include "Input.h"
#include "Struct.h"

using namespace std;



Input::Input()
{
    ifstream inputFile("bd-dec22-births-deaths-by-region.txt");

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


    }else{cout<<"Couldn't open file.";}

}

// It gets the initial Input and
// adds up all the deaths and births
// by region
vector<population> Input::deathsNbirthsbyRegion(bool birth_death)
{

    int count_births = 0;
    for (int region_id = 0; region_id < 17; region_id++)
    {
        for (int i = region_id; i < (int)Input::input.size();  i+= 36)
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

        deathssbyRegion.push_back(byRegion_deaths);

    }
    if (birth_death == true)
        return (birthsbyRegion);

    return (deathssbyRegion);
}

void Input::printArray(vector<population> Array)
{
    cout << "Count\t\t" << "Region" << "\n\n";

    for(auto& v : Array)
    {
        if (v.alive) {
            cout << v.count << "\t\t" << v.region << "\n";

        }
        else {
            cout << v.count << "\t\t" << v.region << "\n";
        }
    }


    cout << "\n";
}
void quick(vector<population>& Births, int left, int mid, int right) {

    int  tempLeftArr = mid - left + 1;
    int  tempRightArr = right - mid;
    vector<population> LeftArray;
    vector<population> RightArray;

    for (int i = 0; i < tempLeftArr; i++)
        LeftArray.push_back(Births[left + i]);

    for (int i = 0; i < tempRightArr; i++)
        RightArray.push_back(Births[mid + 1 + i]);

    int tempIndexOne = 0;
    int tempIndexTwo = 0;
    int indexOfMergedArray = left;

    while (tempIndexOne < tempLeftArr && tempIndexTwo < tempRightArr) {
        if (LeftArray[tempIndexOne].count <= RightArray[tempIndexTwo].count) {
            Births[indexOfMergedArray] = LeftArray[tempIndexOne];
            tempIndexOne++;
        } else {
            Births[indexOfMergedArray] = RightArray[tempIndexTwo];
            tempIndexTwo++;
        }
        indexOfMergedArray++;
    }

    while (tempIndexOne < tempLeftArr) {
        Births[indexOfMergedArray] = LeftArray[tempIndexOne];
        tempIndexOne++;
        indexOfMergedArray++;
    }

    while (tempIndexTwo < tempRightArr) {
        Births[indexOfMergedArray] = RightArray[tempIndexTwo];
        tempIndexTwo++;
        indexOfMergedArray++;
    }


}
void quickSort(vector<population>& Births, int begin, int end) {
    if (begin < end) {
        int pivotIndex = begin;
        int pivot = Births[pivotIndex].count;
        int mid = (begin+end)/2;
        int i = begin + 1;
        int j = end;

        while (i <= j) {
            while (i <= j && Births[i].count <= pivot) {
                i++;
            }
            while (j >= i && Births[j].count > pivot) {
                j--;
            }
            if (i < j) {
                swap(Births[i], Births[j]);
            }
        }
        swap(Births[pivotIndex], Births[j]);
        pivotIndex = j;

        quickSort(Births, begin, pivotIndex - 1);
        quickSort(Births, pivotIndex + 1, end);
        quick(Births, begin, mid, end);
    }
}




int main() {
    Input input = Input();
    vector<population> birth  = input.deathsNbirthsbyRegion(true);
    vector<population> death = input.deathsNbirthsbyRegion(false);

    vector<population> Births;
    vector<population> Deaths;
    cout << "Region\n";
    for (const auto& result : birth)
    {
        cout << result.region;
            cout << " Births: " << result.count<<endl;
            Births.push_back(result);

    }
    cout<<"\n";
    for (const auto& result : death)
    {
        cout << result.region;
            cout <<" Deaths: " << result.count<<endl;
            Deaths.push_back(result);
    }

    quickSort(Births,0, 17);
    quickSort(Deaths, 0, 17);
    cout << endl <<"\nSorted with Qucksort by Births with pivot being the first element:\n\n";
    for (const auto& result : Births)
    {
        cout << result.region <<":"<<result.count;
        cout << endl;
    }
    cout << endl <<"Sorted with Qucksort by Deaths with pivot being the first element:\n\n";
    for (const auto& result : Deaths)
    {
        cout << result.region <<":"<<result.count;
        cout << endl;
    }
    cout<<"\nDeaths by region\n";
    input.printArray(Deaths);
    cout<<"Births by region\n";
    input.printArray(Births);
}
