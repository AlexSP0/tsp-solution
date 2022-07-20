#ifndef TSPHOLDER_H
#define TSPHOLDER_H

#include "genome.h"

#include <vector>

class TSPHolder
{
public:
    TSPHolder(int, int);

    std::vector<Genome> population;

private:
    int genomeSize; //Numbers of cities

    void createPopulation(int);
};

#endif // TSPHOLDER_H
