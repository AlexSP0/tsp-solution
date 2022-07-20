#ifndef GENOME_H
#define GENOME_H

#include <vector>

class Genome
{
public:
    Genome();
    Genome(const int);

    std::vector<int> bits;
    double fitness;

    bool isValidRoute();

    Genome &operator=(const Genome &);

private:
    void generateRoute(const int);
};

#endif // GENOME_H
