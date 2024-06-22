[next - index * sqrt(size) + 1].count)
                index = index + 1;

            right = next - (index - 1 ) * sqrt(size);
            left = next - index * sqrt(size);
        }

    }while(x != array[next].count);
    return (next);

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

int Search::BinarySearch_Span(vector <population> array, int l, int r, int x, int step){
    int m = 0;
    if (l < 0)
        l = 0;

    if (r > (int)array.size())
        r = array.size() - 1;

    while (l <= r) {

        if (step != 1)
        {
            m = floor((r - l + 1) / 