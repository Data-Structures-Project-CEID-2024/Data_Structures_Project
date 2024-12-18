#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <vector>


typedef struct population {
    int period;
    bool alive; // alive -> True (Birth)  || alive -> False (Death)
    std::string region;
    int count;
} population;

typedef struct Node {
    int height;
    int intKey;
    std::string key;
    std::vector<population> dataVector;
    int data_count;
    
    struct Node* node_data_births;
    struct Node* node_data_deaths;

    struct Node* node_parent;
    struct Node* left_child;
    struct Node* right_child;


} Node;


#endif