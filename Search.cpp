#include "Search.h"
#include <iostream>

using namespace std;


Search::Search(vector<population> v)
{   
    array = v;
}

int Search::LinearSearch(int x)
{
    for (int i = 0 ; i <= 3; i++)
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
        next    = int(size * ((x - array[left].count ) / (array[right].count - array[left].count))) + left ;
        
        if (size <= 3)
            return(LinearSearch(x));
        
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

