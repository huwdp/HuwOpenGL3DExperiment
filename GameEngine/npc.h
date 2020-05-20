#ifndef NPC_H
#define NPC_H

#include "objects/object.h"

#include "texture.h"
#include <string>
#include <GL/glut.h>
#include <memory>

class NPC : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
    std::shared_ptr<Texture> texture;
public:
    NPC(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::shared_ptr<Texture> texture);
    void draw();
};

#endif // NPC_H
