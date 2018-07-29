#ifndef COORD_H
#define COORD_H


class Coord
{
private:
    float x;
    float y;
    float z;
    float w;
public:
    Coord();
    Coord(float x, float y, float z);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    float getZ();
    void setZ(float z);
    float getW();
    void setW(float w);
};

#endif // COORD_H
