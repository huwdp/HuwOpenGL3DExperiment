#ifndef TEXTUREDCUBE_H
#define TEXTUREDCUBE_H

#include "object.h"
#include <string>
#include <GL/glut.h>

class TexturedCube : public Object
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
    TexturedCube(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::string textureFileLocation);
    void draw();
};

#endif // TEXTUREDCUBE_H
