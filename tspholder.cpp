#include "tspholder.h"

TSPHolder::TSPHolder(int populationSize, int numberCities)
    : genomeSize(numberCities)
{
    createPopulation(populationSize);
}

TSPHolder::~TSPHolder()
{

}

void TSPHolder::createPopulation(int populationSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        population.emplace_back(Genome(genomeSize));
    }
}
