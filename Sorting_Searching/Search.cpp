#include "Search.h"
#include <iostream>

using namespace std;


Search::Search(vector<population> v)
{   
    int i;
    int b1,b2;

    try
    {
        // We could but an if statement because for
        // small values of b1,b2 there is a segmentation fault
        cout << "[b1,b2] " << "b1: ";
        cin >> b1;
        cout << "b2: ";
        cin >> b2;

        b1 = 432084;
        b2 = 859365;
        
        i = 0;
        while (v[i].count < b1)
            i++;
        
        while (v[i].count <= b2)
        {
            array.push_back(v[i]);
            i ++;
        }
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

