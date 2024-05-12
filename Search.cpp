#include "Search.h"
#include <iostream>

using namespace std;


Search::Search(vector<population> v)
{

    try
    {
        array = v;
        //User input range definition:
        cout << "[b1,b2] " << "b1: ";
        cin >> b1;
        cout << "b2: ";
        cin >> b2;

        //Hardcoded range change if needed to be variable for user input:
        b1 = 432085;
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
    int i;
    if ( findIndex<0){
        i = -findIndex;
    }
    else{
        i = findIndex;
    }
    cout << "\n" << "Result index is: " << i << "\n";
    while(array[i].count <= b2){
        rangeArray.push_back(array[i]);
        i++;
    }
}

int Search::BinaryInterpolationSearch(int x) //Adjust to return correct estimated index if key not found - YANE -> PRINTF
{
    int next; int index;

    int size = array.size();
    int left = 1;
    int right = size - 1;

    do
    {
        index   = 0;
        size    = right - left + 1;

        // Note -1 was added lately because there was a problem
        // when the x was the item in the most right part !
        next    = int(size * ((x - array[left].count ) / (array[right].count - array[left].count))) + left - 1 ;

        if (size <= 3) {
            findIndex = LinearSearch(left, right, x);
            return (LinearSearch(left, right, x));
        }
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
    findIndex = -next;
    return (-next);

}

int Search::InterpolationSearch(int key){
    int low = 0;
    int high = array.size() - 1;
    int closestIndex = 1;
    int pos;

    while (low <= high && key >= array[low].count && key <= array[high].count) {
        pos = low + (((double)(high - low) / (array[high].count - array[low].count)) * (key - array[low].count));
        if (array[pos].count == key) {
            findIndex = pos;
            return pos;
        } else if (array[pos].count < key) {
            closestIndex = pos+1;
            low = pos + 1;
        } else {
            closestIndex = pos;
            high = pos - 1;
        }
    }
    findIndex = -closestIndex;
    return -closestIndex;
}

int Search::BinarySearch(int key){
    int lower = 0;
    int upper = array.size() - 1;
    int mid = 0;
    while( lower <= upper ){
        mid  = floor((lower + upper) / 2);
        //Case where key is in  the rightmost subarray:
        if( array[mid].count < key ){
            lower = mid + 1;
        }
        //Case where key is in the leftmost subarray:
        else if(array[mid].count > key){
            upper = mid - 1;
        }
        //Case where key is found:
        else{
            findIndex = mid;
            return mid;
        }
    }
    //Cases of not existent key returning the correct pointer for rangeParse() :
    if( array[mid].count < key){
        findIndex = - ( mid + 1 );
        return findIndex;
    }
    else{
        findIndex = -mid;
        return findIndex;
    }
}

