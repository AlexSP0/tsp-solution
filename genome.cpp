#include "genome.h"

#include <set>
#include <QRandomGenerator>

Genome::Genome()
    : fitness(0.0)
{}

Genome::Genome(const int numCitites)
    : fitness(0.0)
{
    generateRoute(numCitites);
}

bool Genome::isValidRoute()
{
    if (bits.size() == 0)
    {
        return false;
    }
    std::set<int> vectorSet(bits.begin(), bits.end());
    return vectorSet.size() == bits.size();
}

Genome &Genome::operator=(const Genome &in)
{
    if (this == &in)
    {
        return *this;
    }
    fitness = in.fitness;
    std::copy(in.bits.begin(), in.bits.end(), bits.begin());
    return *this;
}

void Genome::generateRoute(const int numCities)
{
    while (!isValidRoute())
    {
        bits.clear();
        do
        {
            int gen = QRandomGenerator::global()->bounded(numCities);
            if (std::find(bits.begin(), bits.end(), gen) == bits.end())
            {
                bits.push_back(gen);
            }
        } while (bits.size() < numCities);
    }
}
