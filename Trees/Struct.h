#ifndef STRUCT_H
#define STRUCT_H

#include<string>
#include<vector> 

typedef struct population
{
    int period;
    bool alive; // alive -> True (Birth)  || alive -> False (Death)
    std::string region;
    int count;
}population;


typedef struct Node
{
    int height;
    int intKey;
    std::string key;
    std::vector<population> node_data_births;
    std::vector<population> node_data_deaths;

    /*
     * Will be replaced with:
     *
     * For REG:
     * Period indexed contentAVL
     * contentNode data: Counts
     *
     * For COUNT:
     * Region indexed contentAVL
     * contentNode data: Periods
     */
    int data;

    struct Node* node_parent;
    struct Node* left_child;
    struct Node* right_child;
} Node;


#endif