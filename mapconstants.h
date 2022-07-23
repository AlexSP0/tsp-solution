#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H

const int MAP_HEIGHT_IN_PIXELS = 400;
const int MAP_WIDTH_IN_PIXELS  = 400;

const int MAX_X_CITY_COORDINATE = 400;
const int MAX_Y_CITY_COORDINATE = 400;

const float MUTATION_RATE               = 0.01;
const int MUTATE_NUM_GENES_PER_MUTATION = 2;
const double CROSSOVER_RATE             = 0.7;
const int TOURNAMENT_SLECTION_NUMBER    = 2;
const float DECREASE_POPULATION_RATE    = 0.01;

struct Route
{
    double fromCity;
    double toCity;
    Route()
        : fromCity(0.0)
        , toCity(0.0)
    {}
    Route(int from, int to)
        : fromCity(from)
        , toCity(to)
    {}
};

#endif //MAPCONSTANTS_H
