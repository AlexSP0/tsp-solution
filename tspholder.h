#ifndef TSPHOLDER_H
#define TSPHOLDER_H

#include "genome.h"

#include <vector>

class TSPHolder
{
public:
    TSPHolder();
    ~TSPHolder();

    std::vector<Genome> population;

    float bestFitness;
    float totalFitness;

public:
    void mutate(Genome &, int);
    void crossover(Genome &, Genome &, Genome &, Genome &);
    Genome &selection();
    void createPopulation(int, int);
    void genNextGeneration();

private:
    void scrambleMutation(Genome &, int);
    void crossoverSimple(Genome &, Genome &, Genome &, Genome &);
    Genome &tournamentSelection(int num);
};

#endif // TSPHOLDER_H
