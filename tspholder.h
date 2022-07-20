#ifndef TSPHOLDER_H
#define TSPHOLDER_H

#include "citycoordinates.h"
#include "genome.h"
#include "tspcalculator.h"

#include <vector>

class TSPHolder
{
public:
    TSPHolder(int, int, std::vector<CityCoordinates> *);
    ~TSPHolder();

    TSPCalculator *calc;

    std::vector<Genome> population;

private:
    int genomeSize; //Numbers of cities

    std::vector<CityCoordinates> *map;

    void createPopulation(int);
};

#endif // TSPHOLDER_H
