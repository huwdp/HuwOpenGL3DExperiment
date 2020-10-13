#ifndef CIRCLE_H
#define CIRCLE_H


#include "object.h"
#include <string>
#include <memory>
#include <GL/glut.h>

class Sphere : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
public:
    Sphere(float x, float y, float z, float s, float r, float g, float b);
    void draw();
};

#endif // CIRCLE_H
