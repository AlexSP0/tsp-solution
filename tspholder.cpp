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
    crossoverSimple(dad, mom, baby1, baby2);
}

Genome &TSPHolder::selection()
{
    return tournamentSelection(TOURNAMENT_SLECTION_NUMBER);
}

void TSPHolder::createPopulation(int populationSize, int genomeSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        population.emplace_back(Genome(genomeSize));
    }
}

void TSPHolder::genNextGeneration()
{
    int newSize = population.size() - population.size() * DECREASE_POPULATION_RATE;
    std::vector<Genome> newPopulation;

    for (size_t i = 0; i < newSize / 2; i++)
    {
        Genome dad = selection();
        Genome mum = selection();

        Genome baby1;
        Genome baby2;

        crossover(dad, mum, baby1, baby2);
        mutate(baby1, dad.bits.size());
        mutate(baby2, dad.bits.size());

        newPopulation.push_back(baby1);
        newPopulation.push_back(baby2);
    }
    population.clear();
    population = newPopulation;
}

void TSPHolder::calculateTotalAndBestFitness()
{
    totalFitness = 0.0;
    bestFitness  = 0.0;
    for (Genome genome : population)
    {
        if (bestFitness < genome.fitness)
        {
            bestFitness = genome.fitness;
        }
        totalFitness = totalFitness + genome.fitness;
    }
}

Genome &TSPHolder::getBestGenome()
{
    float bestFit  = 0.0;
    int bestGenome = 0;
    for (size_t i = 0; i < population.size(); i++)
    {
        if (bestFit < population.at(i).fitness)
        {
            bestGenome = i;
            bestFit    = population.at(i).fitness;
        }
    }
    return population.at(bestGenome);
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
    for (size_t i = 0; i < num; i++)
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
