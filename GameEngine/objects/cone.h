#ifndef CONE_H
#define CONE_H


#include "object.h"
#include <string>
#include <memory>
#include <GL/glut.h>

class Cone : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
public:
    Cone(float x, float y, float z, float s, float r, float g, float b);
    void draw();
};


#endif // CONE_H
