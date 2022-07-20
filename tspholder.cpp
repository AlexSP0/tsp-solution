#include "tspholder.h"

TSPHolder::TSPHolder(int populationSize, int numberCities, std::vector<CityCoordinates> *m)
    : genomeSize(numberCities)
    , map(m)
{
    createPopulation(populationSize);
    calc = new TSPCalculator(population, 0, 50, map);
}

TSPHolder::~TSPHolder()
{
    delete calc;
}

void TSPHolder::createPopulation(int populationSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        population.emplace_back(Genome(genomeSize));
    }
}
