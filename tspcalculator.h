#ifndef TSPCALCULATOR_H
#define TSPCALCULATOR_H

#include "citycoordinates.h"
#include "genome.h"

#include <vector>

class TSPCalculator
{
public:
    TSPCalculator(std::vector<Genome> &, int, int, std::vector<CityCoordinates> *);

    void showRoutes(int &, int &, int &);

public:
    std::vector<Genome> populationPart;
    void calculateGenomeFitness(int &, Genome &);

private:
    std::vector<CityCoordinates> *map;

    double TotalFitness;

    int currentGenome;
    int currentGen;

    double calcDistanceBetweenCities(int, int);
    void calculateGenomeFitness(int, int &, int &);
};

#endif // TSPCALCULATOR_H
