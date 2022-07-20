#ifndef TSPCALCULATOR_H
#define TSPCALCULATOR_H

#include "citycoordinates.h"
#include "genome.h"

#include <vector>

class TSPCalculator
{
public:
    TSPCalculator(std::vector<Genome> &, int, int, std::vector<CityCoordinates> *);

private:
    std::vector<Genome> populationPart;
    std::vector<CityCoordinates> *map;
};

#endif // TSPCALCULATOR_H
