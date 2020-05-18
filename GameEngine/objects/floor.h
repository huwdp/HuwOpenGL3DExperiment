#ifndef FLOOR_H
#define FLOOR_H

#include "object.h"
#include <string>
#include <GL/glut.h>

class Floor : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    GLuint tex;
    unsigned char texDat[512];
    std::string textureFileLocation;
    void load();
public:
    Floor(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::string textureFileLocation);
    ~Floor();
    void draw();
};

#endif // FLOOR_H
