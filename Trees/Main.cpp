#include "Input.h"
#include "Struct.h"
#include "Trees.h"

using namespace std;

int main()
{
    Input input = Input();
    // input.printArray(input.input);
    
    int size = input.input.size();
    int input_median = size / 2;
    
    BST   bst;
    Node* root = bst.insert(NULL, input.input[input_median]);

    for (int i = 0; i < size; i++)
    {
        bst.insert(root ,input.input[i]);
    }

    Node* find = bst.Search(root,"Waikato region");
    bst.printSelect(find, 2009);
    bst.editSelect(find, 2009, 5);
//    bst.InOrder(root);

}