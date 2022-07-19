#ifndef CITYCOORDINATES_H
#define CITYCOORDINATES_H

class CityCoordinates
{
public:
    CityCoordinates();
    CityCoordinates(float x, float y);

    float xCoord;
    float yCoord;

    bool operator==(CityCoordinates const &c1) const;
};

#endif // CITYCOORDINATES_H
