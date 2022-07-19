#include "citycoordinates.h"

CityCoordinates::CityCoordinates()
    : xCoord(0.0)
    , yCoord(0.0)
{}

CityCoordinates::CityCoordinates(float x, float y)
{
    xCoord = x;
    yCoord = y;
}

bool CityCoordinates::operator==(CityCoordinates const &c1) const
{
    if (this->xCoord == c1.xCoord && this->yCoord == c1.yCoord)
    {
        return true;
    }
    else
    {
        return false;
    }
}
