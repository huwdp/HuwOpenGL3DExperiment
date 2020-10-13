#ifndef NPC_H
#define NPC_H


#include "object.h"
#include <string>
#include <memory>
#include <GL/glut.h>

class NPC : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
public:
    NPC(float x, float y, float z, float s, float r, float g, float b);
    void draw();
};

#endif // NPC_H
