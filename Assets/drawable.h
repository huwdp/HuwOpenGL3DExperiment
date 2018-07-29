#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>

#include "GameEngine/coord.h"

class Drawable : public Coord
{
protected:
    float x, y, z;
public:
    Drawable(float x, float y, float z);
    virtual void draw() = 0;
};

#endif // DRAWABLE_H
