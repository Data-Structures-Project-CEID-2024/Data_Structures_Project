#include<iostream>
#include<fstream>
#include<sstream> 
#include <algorithm> // Required for std::remove_if
#include <cctype> 
#include<vector>
#include "Struct.h"
#include <math.h>
#include <list>
#include <queue>
#include <windows.h>

using namespace std;

population Answer[17];
const int m = 11; //prime number of buckets

class BST{
    public:

        Node* newNode(population data)
        {
            Node* newNode = new Node;

            newNode->key = data.region;
            newNode->node_data_births.resize(18);
            newNode->node_data_deaths.resize(18);
            
            if (data.alive == 1)
                newNode->node_data_births[data.period - 2005] = data;
            else
                newNode->node_data_deaths[data.period - 2005] = data;

            newNode->left_child = NULL;
            newNode->right_child = NULL;
            newNode->height = 1;

            return (newNode);

        }

        int height(Node* node)
        {
            if(node == NULL)
                return 0;
            
            return node->height;
        }

        int height_balance(Node* node)
        {
            if(node == NULL)
                return 0;
            
            return height(node->right_child) - height(node->left_child);
        }


        Node* left_rotation(Node* node)
        {
            Node* new_root = node->right_child;
            Node* new_root_left_child = new_root->left_child;

            
            new_root->left_child = node;
            node->right_child = new_root_left_child;
            
            node->height = 1 + max(height(node->left_child), height(node->right_child));
            new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

            return  new_root;
        }

        Node* right_rotation(Node* node)
        {
            Node* new_root = node->left_child;
            Node* new_root_right_child = new_root->right_child;

            
            new_root->right_child = node;
            node->left_child = new_root_right_child;

            node->height = 1 + max(height(node->left_child), height(node->right_child));
            new_root->height = 1 + max(height(new_root->left_child), height(new_root->right_child));

            return new_root;
        }

        Node*  left_right_rotation(Node* node)
        {
            node->left_child = left_rotation(node->left_child);
            node = right_rotation(node);

            return node;
        }

        Node* right_left_rotation(Node* node)
        {
            node->right_child = right_rotation(node->right_child);
            node = left_rotation(node);

            return node;
        }

        Node* insert(Node* parent, population key)
        {
            if (parent == NULL)
                return (newNode(key));
            
            if ( key.region.compare(parent->key) < 0 ) // key.region < parent.
            {
                parent->left_child = insert(parent->left_child, key);
            }
            else if ( key.region.compare(parent->key) > 0 ) // key.region > parent
            {
                parent->right_child = insert(parent->right_child, key);
            }
            // else if (key.alive == 1)
            //     parent->node_data_births[key.period - 2005] = key;
            // else
            //     parent->node_data_deaths[key.period - 2005] = key;

            
            parent->height = 1 + std::max(height(parent->left_child), height(parent->right_child));

            int hb = height_balance(parent);

            
            if (hb > 1 && key.region.compare(parent->right_child->key) < 0)
                parent = right_left_rotation(parent);

            else if (hb < -1 && key.region.compare(parent->left_child->key) > 0)
                parent = left_right_rotation(parent);

            else if (hb > 1)
                parent = left_rotation(parent);

            else if (hb < -1 )
                parent =  right_rotation(parent);

            return (parent);
        }


        Node* search(Node* parent, std::string key){ //Births oriented

            cout << "\nSearching...\n";
        
        
            while(parent != nullptr)
            {
                //Entry is at right subtree
                if(key.compare(parent->key) > 0 ){ // key > parent->key
                    parent = parent->right_child;
                }
                //Entry is at left subtree
                else if( key.compare(parent->key) < 0 ){ // key < parent->key
                    parent = parent->left_child;
                }
                //Entry found
                else
                    return parent;
            }
            //Entry not found - returning nullptr
            return nullptr;
        }

        void editSelect(Node* node, int year, int input){
            int index = year - 2005;
            node->node_data_births[index].count = input;
            cout << "\nReconfigured data:\n" << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count [NEW]\t" << "Region" << "\n\n";
            cout << node->node_data_births[index].period << "\t\t\t" << node->node_data_births[index].alive << "\t\t\t\t" << node->node_data_births[index].count << "\t\t" << node->node_data_births[index].region << "\n";
        }



        void InOrder(Node* parent, Node*& lastVisited)
        {
            if (parent == NULL)
                return;

            InOrder(parent->left_child, lastVisited);
            cout << parent->key << "\n";
            lastVisited = parent;
            // cout << "--- Node Data Array --- \n";
            // cout << "Births: \n";
            // printArray(parent->node_data_births);
            // cout << "Deaths: \n";
            // printArray(parent->node_data_deaths);
            InOrder(parent->right_child, lastVisited);
        }

        Node* deleteNode(Node* parent, std::string key)
        {
            Node* deletionNode = search(parent, key);

            if (deletionNode == nullptr)
            {
                cout << "Node not found\n";
                return parent;
            }
            else
            {
                Node* lastVisited = nullptr;
                InOrder(deletionNode, lastVisited);
                if (lastVisited != nullptr)
                    cout << lastVisited->key << "\n";
            }

            return deletionNode;
        }


        void printArray(vector<population> Array)
        {
            cout << "Period\t\t" << "Birth or Deaths (1 or 0)\t" << "Count\t\t" << "Region" << "\n\n";

            for(auto& v : Array)
            {
                cout << v.period << "\t\t" << v.alive << "\t\t\t\t" << v.count << "\t\t" << v.region << "\n";
            }


            cout << "\n";
        }    


        void printLevelOrder(Node* root) {
            if (root == nullptr) return;

            queue<Node*> q;
            q.push(root);

            while (!q.empty()) {
                int nodeCount = q.size();
                while (nodeCount > 0) {
                    Node* node = q.front();
                    std::cout << node->key << "\t \t";
                    q.pop();
                    if (node->left_child != nullptr) q.push(node->left_child);
                    if (node->right_child != nullptr) q.push(node->right_child);
                    nodeCount--;
                }
                cout << std::endl;
            }
            cout << endl;
        }
};
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

  
}
void searchElement(){

}
void deleteElement(){

}
void modifyElement(){

}
int main()
{
    
    list< vector <population>> buckets[m];
    Input input = Input();
    vector<population> results = input.deathsNbirthsbyRegion();
    

    for (const auto& result : results)
    {
        cout << "Region: " << result.region <<  "\t\t\tPeriod:  "  << result.period;
        if(result.alive==true) cout << "\tBirths: " << result.count << endl;
        else cout << " \tDeaths: "<<  result.count << endl;
        insertElement(result, buckets);
    }
    
    cout << endl << endl;
    
    for (int i=0; i <m; i++){
        cout <<"Vectors in chain "<< i <<": " << (buckets[i]).size() << endl;
        list<vector<population>> temp = buckets[i];
        for (const auto& vec : temp){
            cout <<"Region: " << vec[0].region << "\tSize: " <<vec.size() << endl;
        }
        // for (const auto& item : buckets[i]) {
        //     cout << item.region << " "; // Assuming 'region' is a member of population struct
        // }
        //     cout << endl;
    }
} 
