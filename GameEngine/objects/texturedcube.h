#ifndef TEXTUREDCUBE_H
#define TEXTUREDCUBE_H

#include "object.h"
#include "../texture.h"
#include <string>
#include <GL/glut.h>
#include <memory>

class TexturedCube : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
    std::shared_ptr<Texture> texture;
public:
    TexturedCube(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::shared_ptr<Texture> texture);
    void draw();
};

#endif // TEXTUREDCUBE_H
