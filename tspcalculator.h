#ifndef TSPCALCULATOR_H
#define TSPCALCULATOR_H

#include "citycoordinates.h"
#include "genome.h"
#include "tspwindow.h"

#include <vector>

class TSPCalculator
{
public:
    TSPCalculator(std::vector<Genome> &, int, int, std::vector<CityCoordinates> *);

private:
    std::vector<Genome> populationPart;

    std::vector<CityCoordinates> *map;

    double TotalFitness;

    int currentGenome;
    int currentGen;

    void showRoutes(int &, int &);

    double calcDistanceBetweenCities(int, int);
    void calculateGenomeFitness(int, int &, int &);
};

#endif // TSPCALCULATOR_H
