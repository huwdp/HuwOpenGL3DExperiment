#ifndef FLOOR_H
#define FLOOR_H

#include "object.h"
#include <string>
#include <memory>
#include <GL/glut.h>
#include "../texture.h"

class Floor : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    std::shared_ptr<Texture> texture;
    void load();
public:
    Floor(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::shared_ptr<Texture> texture);
    void draw();
};

#endif // FLOOR_H
