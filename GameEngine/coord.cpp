#include "coord.h"

Coord::Coord()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->x = 0;
}

Coord::Coord(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->x = x;
}

float Coord::getX()
{
    return x;
}

void Coord::setX(float x)
{
    this->x = x;
}

float Coord::getY()
{
    return y;
}

void Coord::setY(float y)
{
    this->y = y;
}

float Coord::getZ()
{
    return z;
}
void Coord::setZ(float z)
{
    this->z = z;
}

float Coord::getW()
{
    return w;
}
void Coord::setW(float w)
{
    this->w = w;
}
