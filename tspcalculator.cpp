#include "tspcalculator.h"

#include <math.h>

TSPCalculator::TSPCalculator(std::vector<Genome> &population,
                             int begin,
                             int end,
                             std::vector<CityCoordinates> *m)
    : map(m)
{
    std::copy(population.begin() + begin,
              population.begin() + begin + end,
              std::back_inserter(populationPart));
}

double TSPCalculator::calcDistanceBetweenCities(int firstCity, int secondCity)
{
    float xFirstCity = map->at(firstCity).xCoord;
    float yFirstCity = map->at(firstCity).yCoord;

    float xSecondCity = map->at(secondCity).xCoord;
    float ySecondCity = map->at(secondCity).yCoord;

    float xCathetus = abs(xFirstCity - xSecondCity);
    float yCathetus = abs(yFirstCity - ySecondCity);

    return sqrt(pow(xCathetus, 2) + pow(yCathetus, 2));
}

void TSPCalculator::calculateGenomeFitness(int currentGenome)
{
    for (size_t i = 0; i < populationPart[currentGenome].bits.size(); i++)
    {
        if (i == 0)
        {
            continue;
        }
        populationPart[currentGenome].fitness
            = populationPart[currentGenome].fitness
              + calcDistanceBetweenCities(populationPart[currentGenome].bits[i - 1],
                                          populationPart[currentGenome].bits[i]);
    }
}
