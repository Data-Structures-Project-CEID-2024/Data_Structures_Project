#include "Search.h"
#include <iostream>

using namespace std;


Search::Search(vector<population> v)
{

    try
    {
        array = v;
        cout << "[b1,b2] " << "b1: ";
        cin >> b1;
        cout << "b2: ";
        cin >> b2;

        b1 = 432084;
        b2 = 859365;

    }
    catch (runtime_error& e)
    {
        array = v;
    }

}

int Search::LinearSearch( int start, int end, int x)
{
    for (int i = 0 + start; i <= 3 + end; i++)
    {
        if (array[i].count == x)
            return i;
    }
    return (-1);
}

void Search::rangeParse()
{
    int i = findIndex;
    cout << "\n" << " index is: " << i << "\n";
    while(array[i].count <= b2){
        rangeArray.push_back(array[i]);
        i++;
    }
}

int Search::BinaryInterpolationSearch(int x)
{
    int next; int index;

    int size = array.size();
    int left = 0;
    int right = size - 1;
    
    do
    {
        index   = 0;
        size    = right - left + 1;

        // Note -1 was added lately because there was a problem
        // when the x was the item in the most right part !
        next    = int(size * ((x - array[left].count ) / (array[right].count - array[left].count))) + left - 1 ;
        
        if (size <= 3)
            return(LinearSearch(left,right,x));
        
        if (x > array[next].count)
        {
            while( x > array[next + index * sqrt(size) - 1].count)
                index = index + 1;
            
            right = next + index * sqrt(size);
            left = next + (index - 1) * sqrt(size);
        }
        else if ( x < array[next].count)
        {
            while( x < array[next - index * sqrt(size) + 1].count)
                index = index + 1;
            
            right = next - (index - 1 ) * sqrt(size);
            left = next - index * sqrt(size);
        }            
        
    }while(x != array[next].count);
    return (next);

}

// No region of operation
int Search::BinarySearch(){
    int key = b1;
    int lower = 0;
    int upper = array.size() - 1;
    int mid = 0;
    while( lower <= upper ){
        mid  = floor((lower + upper) / 2);
        if( array[mid].count < key ){
            lower = mid + 1;
        }
        else if(array[mid].count > key){
            upper = mid - 1;
        }
        else{
            findIndex = mid;
            return mid;
        }
    }
    findIndex = -1;
    return -1;
}

