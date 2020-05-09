#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
public:
    Cube(float x, float y, float z, float s, float r, float g, float b);
    void draw();
};

#endif // CUBE_H
