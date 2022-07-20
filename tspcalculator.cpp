#include "tspcalculator.h"

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
