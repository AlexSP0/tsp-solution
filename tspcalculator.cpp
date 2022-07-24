#include "tspcalculator.h"

#include <math.h>

TSPCalculator::TSPCalculator(std::vector<Genome> &population,
                             int begin,
                             int end,
                             std::vector<CityCoordinates> *m)
    : map(m)
    , TotalFitness(0.0)
    , currentGenome(0)
    , currentGen(0)
{
    std::copy(population.begin() + begin,
              population.begin() + begin + end,
              std::back_inserter(populationPart));
}

void TSPCalculator::showRoutes(int &fromCity, int &toCity, int &curGenome)
{
    if (currentGenome < populationPart.size())
    {
        calculateGenomeFitness(currentGenome, fromCity, toCity);
        curGenome = currentGenome;
    }
    else
    {
        //Закончили расчеты и показ
        curGenome = -1;
    }
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

void TSPCalculator::calculateGenomeFitness(int currentGenome, int &fromCity, int &toCity)
{
    if (currentGen < populationPart[currentGenome].bits.size())
    {
        if (currentGen != 0)
        {
            double currentDistance
                = calcDistanceBetweenCities(populationPart[currentGenome].bits[currentGen - 1],
                                            populationPart[currentGenome].bits[currentGen]);

            populationPart[currentGenome].fitness = populationPart[currentGenome].fitness
                                                    + currentDistance;

            TotalFitness = TotalFitness + currentDistance;

            fromCity = populationPart[currentGenome].bits[currentGen - 1];
            toCity   = populationPart[currentGenome].bits[currentGen];
        }
        currentGen++;
    }
    else
    {
        currentGen = 0;
        this->currentGenome++;
    }
}

void TSPCalculator::calculateGenomeFitness(int &curGenome, Genome &gen)
{
    if (currentGenome < populationPart.size())
    {
        for (size_t i = 0; i < populationPart.at(currentGenome).bits.size(); i++)
        {
            if (i == 0)
            {
                continue;
            }
            double currentDistance
                = calcDistanceBetweenCities(populationPart[currentGenome].bits[i - 1],
                                            populationPart[currentGenome].bits[i]);

            populationPart[currentGenome].fitness = populationPart[currentGenome].fitness
                                                    + currentDistance;

            TotalFitness = TotalFitness + currentDistance;
        }
        curGenome = currentGenome;
        gen       = populationPart[currentGenome];
        currentGenome++;
    }
    else
    {
        curGenome     = -1;
        currentGenome = 0;
    }
}
