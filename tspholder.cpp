#include "tspholder.h"
#include "mapconstants.h"
#include <QRandomGenerator>

TSPHolder::TSPHolder()
    : bestFitness(0.0)
    , totalFitness(0.0)
{}

TSPHolder::~TSPHolder() {}

void TSPHolder::mutate(Genome &genome, int numCities)
{
    scrambleMutation(genome, numCities);
}

void TSPHolder::crossover(Genome &dad, Genome &mom, Genome &baby1, Genome &baby2)
{
    void crossoverSimple(Genome & dad, Genome & mom, Genome & baby1, Genome & baby2);
}

Genome &TSPHolder::selection()
{
    return tournamentSelection(TOURNAMENT_SLECTION_NUMBER);
}

void TSPHolder::scrambleMutation(Genome &genome, int numCities)
{
    for (size_t i = 0; i < genome.bits.size(); i++)
    {
        float random = static_cast<float>(QRandomGenerator::global()->generateDouble());
        if (random < MUTATION_RATE)
        {
            for (size_t j = 0; j < MUTATE_NUM_GENES_PER_MUTATION; j++)
            {
                int gen1 = QRandomGenerator::global()->bounded(numCities);
                int gen2 = QRandomGenerator::global()->bounded(numCities);
                std::swap(genome.bits[gen1], genome.bits[gen2]);
            }
        }
    }
}

void TSPHolder::crossoverSimple(Genome &dad, Genome &mom, Genome &baby1, Genome &baby2)
{
    float random = QRandomGenerator::global()->generateDouble();

    if (random > CROSSOVER_RATE && mom == dad)
    {
        baby1 = mom;
        baby2 = dad;
        return;
    }

    int position = QRandomGenerator::global()->bounded((int) dad.bits.size());

    for (size_t i = 0; i < position; i++)
    {
        baby1.bits.push_back(mom.bits.at(i));
        baby2.bits.push_back(dad.bits.at(i));
    }

    for (size_t i = position; i < dad.bits.size(); i++)
    {
        baby1.bits.push_back(dad.bits.at(i));
        baby2.bits.push_back(mom.bits.at(i));
    }
}

Genome &TSPHolder::tournamentSelection(int num)
{
    double bestFitnessLocal = 0;
    int choosenGenome       = -1;
    for (size_t i = 0; i < population.size(); i++)
    {
        int rand = QRandomGenerator::global()->bounded((int) population.size());
        if (bestFitnessLocal < population.at(rand).fitness)
        {
            choosenGenome    = i;
            bestFitnessLocal = population.at(rand).fitness;
        }
    }
    return population.at(choosenGenome);
}

void TSPHolder::createPopulation(int populationSize, int genomeSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        population.emplace_back(Genome(genomeSize));
    }
}
