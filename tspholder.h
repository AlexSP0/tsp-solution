#ifndef TSPHOLDER_H
#define TSPHOLDER_H

#include "genome.h"

#include <vector>

class TSPHolder
{
public:
    TSPHolder();
    ~TSPHolder();

public:
    void mutate(Genome &, int);
    void crossover(Genome &, Genome &, Genome &, Genome &);

private:
    void scrambleMutation(Genome &, int);
    void crossoverSimple(Genome &, Genome &, Genome &, Genome &);
};

#endif // TSPHOLDER_H
