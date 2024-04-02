#ifndef STRUCT_H
#define STRUCT_H

typedef struct population
{
    int period;
    bool alive; // alive -> True (Birth)  || alive -> False (Death)
    std::string region;
    int count;
}population;

#endif