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
int partition(vector<population>& Births, int left, int right) {

    int pivotValue = Births[left].count; // to aristerotero stoixeiokathe sub-array ws pivot

    int storeIndex = left + 1;

    // Partitioning gyrw apo to pivot
    for (int i = left + 1; i <= right; i++) {
        if (Births[i].count < pivotValue) {
            swap(Births[i], Births[storeIndex]);
            storeIndex++; //sto telos kserw mesw tou storeIndex poses allages exw kanei ara h thesh tou pivot sto final array einai sth thesh ish me ton arithmo twn allagwn
        }
    }

    swap(Births[left], Births[storeIndex - 1]);  // sto telos kathe partitioning vazoume to pivot sth thesh tou

    return storeIndex - 1;
}

void quickSort(vector<population>& Births, int begin, int end) {
    if (begin < end) {
        int pivotIndex = partition(Births, begin, end);

        //sort ta aristera(mikrotera tou pivot) kai deksia(megalytera tou pivot) arrays
        quickSort(Births, begin, pivotIndex - 1);
        quickSort(Births, pivotIndex + 1, end);
    }
}





int main() {
    Input input = Input();
    vector<population> birth  = input.deathsNbirthsbyRegion(true);

    vector<population> Births;
    cout << "Region\n";
    for (const auto& result : birth)
    {
        cout << result.region;
            cout << " Births: " << result.count<<endl;
            Births.push_back(result);

    }
    cout<<"\n";

    quickSort(Births,0, 16);
    cout << endl <<"\nSorted with Qucksort by Births with pivot being the first element:\n\n";
    for (const auto& result : Births)
    {
        cout << result.region <<":"<<result.count;
        cout << endl;
    }

}
